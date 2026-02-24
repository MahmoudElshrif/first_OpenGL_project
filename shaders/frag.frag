#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D TEXTURE;
uniform vec4 objectColor;
uniform vec4 lightColor;
uniform int TIME;

void main() {
	vec4 clr = texture(TEXTURE, TexCoord);
	FragColor = objectColor * lightColor;
}
