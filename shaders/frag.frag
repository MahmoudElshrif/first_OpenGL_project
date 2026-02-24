#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 objectColor;
uniform vec4 lightColor;
uniform int TIME;

void main() {
	FragColor = objectColor * lightColor;
}
