#version 130

in vec2 in_Position;
in vec2 in_TexCoord;

out vec2 ex_TexCoord;

uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 0, 1);
    ex_TexCoord = in_TexCoord;
}