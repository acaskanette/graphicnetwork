#version 330 core
in vec3 Normal;
in vec3 FragmentPosition;

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main()
{    

	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;


	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragmentPosition);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * lightColor;


	// Specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(viewPosition - FragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow (max(dot(viewDirection, reflectDirection), 0.0), 16);
	vec3 specular = specularStrength * spec * lightColor;

	// Final Calculation
	vec3 result = (ambient + diffuse + specular) * objectColor;

    color = vec4(result, 1.0);
}