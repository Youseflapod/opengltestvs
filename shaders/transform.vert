#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 mvp;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	ourColor = aPos;
//	float rand1 = rand(vec2(aPos.x, aPos.y));
//	float rand2 = rand(vec2(aPos.y, aPos.x));
//	ourColor = vec3(rand1, rand2, rand1*rand2);
	gl_Position = mvp * vec4(aPos, 1.0);
	TexCoord = aTexCord;
}