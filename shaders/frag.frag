#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D TEXTURE;
uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform int TIME;

void main() {
	float ambientstrength = 0.1;
	vec4 ambientcolor = lightColor * ambientstrength;

	vec3 lightdir = normalize(lightPos - FragPos);

	float diff = max(dot(Normal, lightdir), 0.);

	vec4 diffcolor = lightColor * diff;

	FragColor = objectColor * (ambientcolor + diffcolor);
}
