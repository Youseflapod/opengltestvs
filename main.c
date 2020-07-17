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
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

GLFWwindow* window;
int width = 1600, height = 1200;

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // don't give mipmap option!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    printf("Hello once more C! \n");

    // TEXTURES
    unsigned int texture1, texture2;
    texture1 = loadTexture("container.jpg");
    texture2 = loadTexture("awesomeface.png");

    unsigned int shaderProgram = buildShaderProgram("texture.vert", "texture.frag");
    glUseProgram(shaderProgram); // REALLY don't forget to activate the shader before setting the uniforms of it!
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // set uniform to 0
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1); // set uniform to 1 for activate

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // STEP 4 (in render loop)
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

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
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}