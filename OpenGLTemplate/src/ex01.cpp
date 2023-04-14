// 本练习的主要内容：
// 1、尝试了同事定义两个片段着色器
// 2、同时绘制两个三角形

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>  

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 0.5f);\n"
    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5f, 0.2f, 1.0f, 1.0f);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader and fragment shader
    unsigned int vertexShader, fragmentShader1, fragmentShader2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource, nullptr);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader1);
    glCompileShader(fragmentShader2);

    // check for shaders' compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader1, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned int shaderPrograms[2];
    shaderPrograms[0] = glCreateProgram();
    shaderPrograms[1] = glCreateProgram();
    
    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShader1);
    glLinkProgram(shaderPrograms[0]);
    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShader2);
    glLinkProgram(shaderPrograms[1]);

    // check for program compile errors
    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderPrograms[0], 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete unused shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    //-----------------------------------------------------
    float firstTriangle[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    float secondTriangle[] = {
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,
    };

    unsigned int VBOs[2], VAOs[2];

    glGenBuffers(2, VBOs);
    glGenVertexArrays(2, VAOs);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(shaderPrograms[0]);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(shaderPrograms[1]);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Optional: de-allocate all resources once they've outlived their purpose:
    // --------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderPrograms[0]);
    glDeleteProgram(shaderPrograms[1]);


    glfwTerminate();
    return 0;
}