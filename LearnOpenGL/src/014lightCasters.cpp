#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader_s.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned int loadTexture(char const *path);

// setting
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;
float responseTime = 0.0f;

// light caster type
int casterType = 1;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    //-----------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,   0.0f),
        glm::vec3( 2.0f,  5.0f,  -15.0f),
        glm::vec3(-1.5f, -2.2f,  -2.5f),
        glm::vec3(-3.8f, -2.0f,  -12.3f),
        glm::vec3( 2.4f, -0.4f,  -3.5f),
        glm::vec3(-1.7f,  3.0f,  -7.5f),
        glm::vec3( 1.3f, -2.0f,  -2.5f),
        glm::vec3( 1.5f,  2.0f,  -2.5f),
        glm::vec3( 1.5f,  0.2f,  -1.5f),
        glm::vec3(-1.3f,  1.0f,  -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // load and create a texture
    unsigned int diffuseMap = loadTexture("../resources/textures/container2.png");
    unsigned int specularMap = loadTexture("../resources/textures/container2_specular.png");

    // set shaders
    // object shader
    Shader lightingShader("../shaders/014.light_casters.vs", "../shaders/014.light_casters.fs");
    lightingShader.use();
    // set object material attributes
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setFloat("material.shininess", 32.0f);
    lightingShader.setVec3("light.lightDirection", -0.2f, -1.0f, -0.3f);
    lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("light.constant", 1.0f);
    lightingShader.setFloat("light.linear", 0.09f);
    lightingShader.setFloat("light.quadratic", 0.032f);

    // lamp shader
    Shader lampShader("../shaders/014.lamp_cube.vs", "../shaders/014.lamp_cube.fs");

    // start rendering!
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        //---------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        responseTime += deltaTime * 1000.0f;
        lastFrame = currentFrame;

        // input
        //-------------
        processInput(window);

        // render
        //-------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set MVP matrices
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);

        // set lamp
        lampShader.use();
        glm::vec3 lightPos(1.2f, 1.0f, 4.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.3f));

        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // set object
        lightingShader.use();
        lightingShader.setInt("casterType", casterType);
        // render container
        for(int i = 0; i < 10; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);
            lightingShader.setMat4("view", view);
            lightingShader.setMat4("projection", projection);
            lightingShader.setVec3("light.lightPosition", lightPos);
            lightingShader.setVec3("light.flashlightPosition", camera.Position);
            lightingShader.setVec3("light.flashlightDirection", camera.Front);
            lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
            lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
            lightingShader.setVec3("viewPos", camera.Position);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);            
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose:
    // --------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (responseTime > 500.0f && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        casterType = (casterType == 3 ? 1 : (casterType + 1));
        if(casterType == 1)
            std::cout << "point light mode" << std::endl;
        if(casterType == 2)
            std::cout << "parallel light mode" << std::endl;
        if(casterType == 3)
            std::cout << "flash light mode" << std::endl;
        responseTime = 0.0f;
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const *path) {
    unsigned textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data) {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4) {
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
        std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);

    return textureID;
}
