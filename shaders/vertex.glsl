#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

uniform int TIME;

void main() {

	float ang = TIME / 100.;
	mat2 rot = mat2(cos(ang), sin(ang), -sin(ang), cos(ang));
	vec2 newpos = vec2(aPos.x, aPos.y) * rot;
	gl_Position = vec4(newpos.x, newpos.y, aPos.x, 1.0);
	vertexColor = aColor;
	TexCoord = aTexCoord;
}
