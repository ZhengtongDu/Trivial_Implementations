// 本练习对应Material一节的练习，说明如下
// 1. 尝试改变光源的颜色，根据光源发出不同颜色的光，物体的颜色也随之变化。

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
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,

        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,   0.0f,   0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,   0.0f,   0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // set shaders
    // object shader
    Shader lightingShader("../shaders/ex07.material.vs", "../shaders/ex07.material.fs");
    lightingShader.use();

    // lamp shader
    Shader lampShader("../shaders/ex07.lamp_cube.vs", "../shaders/ex07.lamp_cube.fs");

    // start rendering!
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        //---------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        //-------------
        processInput(window);

        // render
        //-------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set MVP matrices
        glBindVertexArray(VAO);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);

        // set object material attributes
        glm::vec3 objectColor(0.8f, 0.5f, 0.8f);
        glm::vec3 lightColor(0.8f + 0.2f * sin(glm::radians(40.0f * glfwGetTime())), 1.0f - 0.2f * sin(glm::radians(40.0f * glfwGetTime())), 0.8f + 0.2f * cos(glm::radians(40.0f * glfwGetTime())));
        lightingShader.setVec3("material.ambient", 0.3f * objectColor.x, 0.3f * objectColor.y, 0.3f * objectColor.z);
        lightingShader.setVec3("material.diffuse", 0.6f * objectColor.x, 0.6f * objectColor.y, 0.6f * objectColor.z);
        lightingShader.setVec3("material.specular", 0.8f * lightColor.x, 0.8f * lightColor.y, 0.8f * lightColor.z);
        lightingShader.setFloat("material.shininess", 32.0f);
        lightingShader.setVec3("light.ambient", 0.2f * lightColor.x, 0.2f * lightColor.y, 0.2f * lightColor.z);
        lightingShader.setVec3("light.diffuse", 0.5f * lightColor.x, 0.5f * lightColor.y, 0.5f * lightColor.z);
        lightingShader.setVec3("light.specular", lightColor.x, lightColor.y,lightColor.z);

        // set lamp
        lampShader.use();
        glm::vec3 lightPos(2.2f, 2.2f, 2.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.3f));

        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lampShader.setMat4("model", model);
        lampShader.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // set object
        lightingShader.use();

        // render container
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 1.2f, 0.0f));
        lightingShader.setMat4("model", model);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);
        lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
        lightingShader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose:
    // --------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
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