//
// Created by yabde on 1/15/2020.
//

#ifndef OPENGLTEST_MISC_H
#define OPENGLTEST_MISC_H
#endif 

const char *load_shader_source(char *filename);
unsigned int buildShaderProgram(char *vsFileName, char *fsFileName);
unsigned int loadTexture(char* textureFileName);