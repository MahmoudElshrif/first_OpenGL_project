#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D TEXTURE;
uniform sampler2D OTHERTEXTURE;
uniform int TIME;

void main() {
	FragColor = texture(TEXTURE, TexCoord);
}
