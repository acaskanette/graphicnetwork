#version 330
in vec3 vertNormal;
in vec3 lightDir;
in vec3 cameraDir;

//in vec2 texcoords;

//layout (location = 0) uniform sampler2D diffuseTexture;

out vec4 fragColor;


void main() { 
	
	// Light parameters
	const vec4 specularIntensity = vec4(0.5, 0.5, 0.5, 0.0);
	const vec4 diffuseIntensity = vec4(1.0, 0.0, 0.0, 0.0); 
	const vec4 ambientIntensity = 0.4* diffuseIntensity;
	
	vec3 light = normalize(lightDir);
	vec3 camera = normalize(cameraDir);		
	vec3 normal = normalize(vertNormal);

	// Reflection Vector using Blinn-Phong
	vec3 reflection = normalize (light + camera);
	
	// Diffuse
	float kDiffuse = max(dot(normal,light), 0.0);
	
	// Specular	 
	float kSpecular = max (0.0, dot(normal, reflection));

	if (kDiffuse > 0) {
			
		kSpecular = pow (kSpecular, 16.0);
	
	}

	fragColor = ambientIntensity + (kDiffuse * diffuseIntensity) + (kSpecular * specularIntensity);	
	
} 
