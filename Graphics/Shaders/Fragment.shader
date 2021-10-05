#version 410

in vec4 fColor;
in vec3 fNormal;

uniform vec3 lightDirection;

out vec4 color;


void main()
{
	vec3 surfaceNormal = normalize(fNormal);
	vec3 lightNormal = normalize(lightDirection);
	lightNormal = normalize(vec3(-1.0f, -1.0f, -1.0f));
	vec4 lightColor = vec4(1.0f, 1.0f, 0.6f, 1.0f);

	// color = ambientColor + diffuseColor + specularColor
	// Calculate diffuse color
	float lambertTerm = dot(-lightNormal, surfaceNormal);
	float lambertTerm = max(0, min(1, lambertTerm));
	vec4 diffuseColor = fColor * lambertTerm * lightColor;


	color = diffuseColor;
}