#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "misc.h"
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#ifndef M_PI
# define M_PI 3.141592653
#endif

static void error_callback(int error, const char* description);

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

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


    // TEXTURES
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // makes 'texture' the currently bound texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // don't give mipmap option!
    int imwidth, imheight, nrChannels;
    unsigned char *data = stbi_load("assets/container.jpg", &imwidth, &imheight, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imwidth, imheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { printf("Bad news, the texture failed to load"); }
    stbi_image_free(data);


    printf("Hello once more C! \n");
    
    unsigned int shaderProgram = buildShaderProgram("texture.vert", "texture.frag");

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


    // STEP 3
    // loc 0, size vec3, floats, don't normalize, stride length 3*size of float, idk
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    printf("workiing \n"); 

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // STEP 4 (in render loop)
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
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
