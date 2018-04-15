#version 130

in vec2 ex_TexCoord;

uniform sampler2D textureSampler;

out vec4 out_Color;

void main(void)
{
    out_Color = texture(textureSampler, ex_TexCoord);
}