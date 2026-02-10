#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D TEXTURE;

void main() {
	FragColor = texture(TEXTURE, TexCoord);
	// FragColor.rb = TexCoord;
}
