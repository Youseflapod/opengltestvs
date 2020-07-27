#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	vec4 preRandFrag = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) + vec4(ourColor,1.0)*0.3;
	float aRand = rand(vec2(preRandFrag.x, preRandFrag.y));
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), aRand) + vec4(ourColor,1.0)*0.3;
}