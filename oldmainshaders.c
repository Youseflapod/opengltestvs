#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <stdbool.h>
#include "misc.h"
#include <cglm/cglm.h>

#ifndef M_PI
# define M_PI 3.141592653
#endif

static void error_callback(int error, const char* description);

float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left
        1.0f, 1.0f, 1.0f // way top right
};
unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 4    // second triangle
};
/*float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};*/
/*float vertices[] = {
        // first triangle
        0.7f,  0.7f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left
        // second triangle
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.7f,  0.7f, 0.0f   // top left
};*/

GLFWwindow* window;
int width = 1600, height = 900;

int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Hello World! 🌎", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    //gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //glfwSwapInterval(1); //set to 0 for infinite fps

    mat4 m = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
        };

    glm_translate(m, (vec3) { 1.0f, 0.0f, 0.0f });

    printf("Hello once more C! \n");

    
    unsigned int shaderProgram = buildShaderProgram("vert2.glsl", "frag2.glsl");


    unsigned int VAO;
    unsigned int VBO; // id for opengl vertex buffer
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // generate 1 buffer, and save the address to the vbo var pointer
    glGenBuffers(1, &EBO);

    // STEP 1
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // STEP 2
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // for sending an array of vertices to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send vertices data into VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // STEP 3
    // loc 0, size vec3, floats, don't normalize, stride length 3*size of float, idk
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // STEP 4 (in render loop)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}


static void error_callback(int error, const char* description) {fprintf(stderr, "Error: %s\n", description);}
