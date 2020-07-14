//
// Created by yabde on 1/15/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#pragma warning( disable : 4090 )

char *concatenate(char* str1, char* str2) {
    char *str3 = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
    strcpy(str3, str1);
    strcat(str3, str2);
    return str3;
}

const char *load_shader_source(char *filename) {
    FILE *file = fopen(filename, "r");             // open
    fseek(file, 0L, SEEK_END);                     // find the end
    size_t size = ftell(file);                     // get the size in bytes
    const char *shaderSource = calloc(1, size);        // allocate enough bytes
    rewind(file);                                  // go back to file beginning
    fread(shaderSource, size, sizeof(char), file); // read each char into ourblock
    fclose(file);                                  // close the stream
    return shaderSource;
}

unsigned int buildShaderProgram(char *vsFileName, char *fsFileName) {
    const char *shaderFolderLoc = "shaders/";
    unsigned int vertexShader;
    int success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = load_shader_source(concatenate(shaderFolderLoc, vsFileName));
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED \n%s \n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = load_shader_source(concatenate(shaderFolderLoc, fsFileName));
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED \n%s \n", infoLog);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED \n%s \n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}