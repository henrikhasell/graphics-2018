#version 140

struct Light
{
    vec3 position;
    vec3 colour;
};

in vec3 ex_Position;
in vec3 ex_Normal;
in vec2 ex_TexCoord;
in vec3 ex_ViewPosition;

out vec4 out_Colour;

uniform sampler2D material_Ambient;
uniform sampler2D material_Diffuse;
uniform sampler2D material_Specular;

uniform Light lights[10];

uniform vec3 light_Ambient = vec3(0.5, 0.5, 0.5);
uniform vec3 light_Diffuse = vec3(1, 1, 1);
uniform vec3 light_Specular = vec3(1, 1, 1);
uniform vec3 light_Position = vec3(4, 4, 4);

uniform vec3 camera_Normal;

void main(void)
{
    vec3 light_Direction = normalize(light_Position - ex_Position);
    float light_DotProduct = max(0, dot(ex_Normal, light_Direction));

    vec3 light_ToCamera = normalize(ex_ViewPosition - ex_Position);
    vec3 light_Reflection = reflect(-light_Direction, light_ToCamera);
    float light_ReflectionAngle = max(0, dot(light_ToCamera, light_Reflection));

    vec3 ambient = light_Ambient * texture(material_Ambient, ex_TexCoord).rgb;
    vec3 diffuse = light_Diffuse * texture(material_Diffuse, ex_TexCoord).rgb * light_DotProduct;
    vec3 specular = light_Specular * texture(material_Specular, ex_TexCoord).rgb * pow(light_ReflectionAngle, 256);

    out_Colour = vec4(ambient, 1) + vec4(diffuse, 1) + vec4(specular, 1);
}