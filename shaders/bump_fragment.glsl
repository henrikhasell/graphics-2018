#version 130

in vec3 ex_Position;
in vec3 ex_Normal;
in vec2 ex_TexCoord;

out vec4 out_Color;

uniform sampler2D textureSampler;

uniform vec3 lightPosition = vec3(4, 4, 4);
uniform vec3 lightColour = vec3(1, 1, 1);
uniform float lightRadius = 20.0f;
uniform float lightAmbient = 0.2f;

void main(void)
{
    vec3 lightDirection = lightPosition - ex_Position;
    float lightDistance = length(ex_Position - lightPosition);
    float lightParallel =  clamp(dot(ex_Normal, lightDirection), 0, 1);
    float lightAmount = lightRadius * lightParallel / (lightDistance * lightDistance);
	vec3 materialColour = vec3(texture(textureSampler, ex_TexCoord)) * clamp(lightAmount + lightAmbient, 0, 1);
    out_Color = vec4(materialColour, 1);
}