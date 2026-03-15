#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D TEXTURE;
uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int TIME;

void main() {
	float ambientstrength = 0.1;
	vec4 ambientcolor = lightColor * ambientstrength;

	vec3 lightdir = normalize(lightPos - FragPos);

	float diff = max(dot(Normal, lightdir), 0.);

	vec4 diffcolor = lightColor * diff;

	float specstrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightdir, Normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.), 32.);
	vec4 specular = specstrength * spec * lightColor;

	FragColor = objectColor * (ambientcolor + diffcolor + specular);
}
