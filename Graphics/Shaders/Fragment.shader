#version 410

in vec4 fPosition;
in vec4 fColor;
in vec3 fNormal;

uniform vec3 lightDirection;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform float specularPower;

uniform vec4 cameraPosition;

out vec4 color;

void main()
{
	vec3 surfaceNormal = normalize(fNormal);
	vec3 lightNormal = normalize(lightDirection);
	//lightNormal = normalize(vec3(-1.0f, -1.0f, -1.0f));
	vec4 lightColor = vec4(1.0f, 1.0f, 0.6f, 1.0f);

	// Calculate ambient color
	vec4 ambientColor = fColor * lightAmbient;

	// Calculate diffuse color
	float lambertTerm = dot(-lightNormal, surfaceNormal);
	lambertTerm = max(0, min(1, lambertTerm));
	vec4 diffuseColor = fColor * lambertTerm * lightDiffuse;

	// Calculate specular color
	vec3 surfaceToView = normalize(cameraPosition.xyz - fPosition.xyz);
	vec3 reflectionNormal = reflect(lightNormal, surfaceNormal);
	float specularTerm = dot(surfaceToView, reflectionNormal);
	specularTerm = max(0, specularTerm);
	specularTerm = pow(specularTerm, specularPower);
	vec4 specularColor = fColor * lightSpecular * specularTerm;


	color = ambientColor + diffuseColor + specularColor;
}