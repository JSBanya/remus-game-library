#version 430 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
	vec4 Position;
	vec4 Color;

	float AttenuationConstant;
	float AttenuationLinear;
	float AttenuationQuadratic;

	bool Active;
};

struct DirectionalLight {
	vec4 Direction;
	vec4 Color;

	bool Active;
};

struct SpotLight {
	vec4 Position;
	vec4 Direction;
	vec4 Color;

	float Cutoff;
	float OuterCutoff;

	float AttenuationConstant;
	float AttenuationLinear;
	float AttenuationQuadratic;

	bool Active;
};

layout(std430, binding = 0) buffer PointLights
{
    PointLight lights[];
} pointLights;

layout(std430, binding = 1) buffer DirectionalLights
{
    DirectionalLight lights[];
} directionalLights;

layout(std430, binding = 2) buffer SpotLights
{
    SpotLight lights[];
} spotLights;


uniform vec3 cameraPosition;
uniform vec3 ambient;
uniform Material material;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;  

out vec4 FragColor;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main() {
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(cameraPosition - FragPos);

	vec3 result = ambient * vec3(texture(material.diffuse, TexCoords));

	// Calculate point light contribution
	for(int i = 0; i < pointLights.lights.length(); i++) {
		result += CalcPointLight(pointLights.lights[i], norm, viewDir);
	}

	// Calculate directional light contribution
	for(int i = 0; i < directionalLights.lights.length(); i++) {
		result += CalcDirectionalLight(directionalLights.lights[i], norm, viewDir);
	}

	// Calculate spot light contribution
	for(int i = 0; i < spotLights.lights.length(); i++) {
		result += CalcSpotLight(spotLights.lights[i], norm, viewDir);
	}

	FragColor = vec4(result, 1.0);   
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
	if(!light.Active)
		return vec3(0, 0, 0);

	vec3 lightPosition = vec3(light.Position);
	vec3 lightColor = vec3(light.Color);
	float lightColorAlpha = light.Color.a;

    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);

	float dist = length(lightPosition - FragPos);
	float attenuation = 1.0 / (light.AttenuationConstant + light.AttenuationLinear * dist + light.AttenuationQuadratic * (dist * dist)); 

	// Diffuse
	vec3 diffuse = attenuation * lightColor * lightColorAlpha * diff * vec3(texture(material.diffuse, TexCoords));

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = attenuation * lightColor * lightColorAlpha * spec * vec3(texture(material.specular, TexCoords));

    return (diffuse + specular);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	if(!light.Active)
		return vec3(0, 0, 0);

	vec3 lightDirection = vec3(light.Direction);
	vec3 lightColor = vec3(light.Color);
	float lightColorAlpha = light.Color.a;

	vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 diffuse = lightColor * lightColorAlpha * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = lightColor * lightColorAlpha * spec * vec3(texture(material.specular, TexCoords));
    return (diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir) {
	if(!light.Active)
		return vec3(0, 0, 0);

	vec3 lightPosition = vec3(light.Position);
	vec3 lightDirection = vec3(light.Direction);
	vec3 lightColor = vec3(light.Color);
	float lightColorAlpha = light.Color.a;

    vec3 lightDir = normalize(lightPosition - FragPos);

    // Attenuation
    float dist = length(lightPosition - FragPos);
    float attenuation = 1.0 / (light.AttenuationConstant + light.AttenuationLinear * dist + light.AttenuationQuadratic * (dist * dist)); 

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-lightDirection));
	float intensity = smoothstep(light.OuterCutoff, light.Cutoff, theta);

	// Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = attenuation * intensity * lightColor * lightColorAlpha * diff * vec3(texture(material.diffuse, TexCoords));

	// Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = attenuation * intensity * lightColor * lightColorAlpha * spec * vec3(texture(material.specular, TexCoords));

    return (diffuse + specular);
}