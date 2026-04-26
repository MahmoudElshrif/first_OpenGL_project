#version 330 core

out vec4 FragColor;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D TEXTURE;
uniform vec4 objectColor;
uniform vec3 viewPos;
uniform int TIME;

void main() {
	//ambient

	vec3 norm = normalize(Normal);
	//diffuse
	vec3 lightdir = normalize(light.pos - FragPos);
	float diff = max(dot(norm, lightdir), 0.);

	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightdir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);

	vec3 diffcolor = light.diffuse * diff * material.diffuse;
	vec3 ambientcolor = light.ambient * material.ambient;
	vec3 specular = material.specular * (spec * light.specular);

	FragColor = vec4(ambientcolor + diffcolor + specular, 1.);
}
