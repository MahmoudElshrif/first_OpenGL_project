#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D TEXTURE;
uniform sampler2D OTHERTEXTURE;
uniform int TIME;

void main() {
	FragColor = mix(texture(TEXTURE, TexCoord), texture(OTHERTEXTURE, TexCoord), 0.3);
	// FragColor.rb = TexCoord;
}
