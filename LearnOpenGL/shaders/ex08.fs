#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emit;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform float timeSine;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient light
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // emit light
    vec3 emitLight = max(timeSine, 0.0f) * light.specular * texture(material.emit, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular + emitLight;
    FragColor = vec4(result, 1.0f);
}
