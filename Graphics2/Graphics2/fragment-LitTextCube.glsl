#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragmentPosition;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{    

	// Ambient	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));


	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(-light.direction);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));


	// Specular
	vec3 viewDirection = normalize(viewPosition - FragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	// Final Calculation
	vec3 result = ambient + diffuse + specular;

    color = vec4(result, 1.0f);
}