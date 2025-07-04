#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

static void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == true) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    // your OpenGL setup will go here later
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Faliled to create GLF Window" << std::endl;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {     //initializing GLAD manages function pointers for OpenGL
        std::cout << "Failed To initialize Glad" << std::endl;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);  //There are many Call back function which can be used to call user functions

    //Vertex Input
    float vertices[] = {
        //postions       colors
        -0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f,             //top right
        0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,            //bottom right
        0.0f,0.5,0.0f, 0.0f,0.0f,1.0f            //bottom left
    };

    //Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;   //vertex buffer objects can store a large number of vertices in the GPU’s memory
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binds buffer can accept multiple different types of buffers 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copy user-defined data into the currently bound buffer.

    //Element Buffer Objects
    //OpenGL works with traingles so to draw a rectangle instead of having 6 coordinates of vertices of 2 triangles we can have only 4 so that
    //managing high poly objects become easier.EBO tells openGL to draw 1st traingle using which vertex indexes using the EBO with the help of
    //indices Array
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    Shader shader("E:/ENGG/OpenGl/Codes/first/RGB_Triangle/RGB_Triangle/Shaders/vertex_shader.vs", "E:/ENGG/OpenGl/Codes/first/RGB_Triangle/RGB_Triangle/Shaders/fragment_shader.fs");
    shader.use();
    //Linking vertex attributes:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   //position attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   //color attributes
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))  //checks at the start of each loop iteration if GLFW has been instructed to close.
    {
        //input
        processInput(window);

        //rendering
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);    //(a large 2D buffer that contains color values for each pixel in GLFW’s window) that is used to render
        glfwPollEvents();   //checks if any events are triggered(like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions(which we can register via callback methods)
    }

    glfwTerminate();
    return 0;
}
