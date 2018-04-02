#version 140

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

out vec3 ex_Position;
out vec3 ex_Normal;
out vec2 ex_TexCoord;
out vec3 ex_ViewPosition;

uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 shadowMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);

void main()
{
    ex_Position = (modelMatrix * in_Position).xyz;
    ex_Normal = normalize(mat3(modelMatrix) * in_Normal);
	ex_TexCoord = in_TexCoord;
	ex_ViewPosition = (inverse(viewMatrix) * vec4(0, 0, 0, 1)).xyz;

    gl_Position = projectionMatrix * viewMatrix * vec4(ex_Position, 1);
}
