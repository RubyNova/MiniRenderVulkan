#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 3) uniform lightPosData {
    vec3 lightPos;
};
layout(location = 0) in vec3 fragColour;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 fragPos;

layout(location = 0) out vec4 outColour;

const vec3 lightColour = vec3(1.0, 1.0, 1.0);
const float lightStrength = 1600.0;

const vec3 diffuseColour = vec3(1.0, 1.0, 1.0);

const vec3 specularColour = vec3(1.0, 1.0, 1.0);
const float specularStrength = 8.0;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = lightPos - fragPos;
    float distance = length(lightDir);

    distance = distance * distance;
    lightDir = normalize(lightDir);

    vec4 textureSample = texture(texSampler, fragTexCoord);

    //ambient
    vec3 ambient = vec3(0, 0, 0);

    //diffuse
    float lambertian = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diffuseColour * lambertian * lightColour * 50.0 / distance;

    //specular
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    vec3 specular = specularColour * pow(specAngle, specularStrength / 4.0) * lightColour * lightStrength / distance;

    outColour = vec4(specular + ambient + diffuse, 1) * textureSample;
}