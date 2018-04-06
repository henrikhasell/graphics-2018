#version 140

struct Light
{
    vec3 position;
    vec3 colour;
};

in vec3 ex_Position;
in vec3 ex_Normal;
in vec3 ex_Tangent;
in vec3 ex_Bitangent;
in vec2 ex_TexCoord;
in vec3 ex_ViewPosition;

out vec4 out_Colour;

uniform sampler2D material_Ambient;
uniform sampler2D material_Diffuse;
uniform sampler2D material_Specular;
uniform sampler2D material_Normal;

uniform Light lights[10];

uniform vec3 light_Ambient = vec3(0.0, 0.0, 0.0);
uniform vec3 light_Diffuse = vec3(0.7, 0.7, 0.7);
uniform vec3 light_Specular = vec3(2.4, 2.4, 2.4);
uniform vec3 light_Position = vec3(4, 4, 4);

uniform vec3 camera_Normal;

void main(void)
{
    mat3 TBN = transpose(mat3(
        ex_Tangent,
        ex_Bitangent,
        ex_Normal
    ));

    vec3 normal = normalize(texture(material_Normal, ex_TexCoord).rbg * 2 - 1);
    vec3 light_Direction = normalize(TBN * normalize(light_Position - ex_Position));
    float light_DotProduct = max(0, dot(normal, light_Direction));

    vec3 light_ToCamera = normalize(TBN * normalize(ex_ViewPosition - ex_Position));
    vec3 light_Reflection = reflect(-light_Direction, normal );
    float light_ReflectionAngle = max(0, dot(light_ToCamera, light_Reflection));

    vec3 ambient = light_Ambient * texture(material_Ambient, ex_TexCoord).rgb;
    vec3 diffuse = light_Diffuse * texture(material_Diffuse, ex_TexCoord).rgb * light_DotProduct;
    vec3 specular = light_Specular * texture(material_Specular, ex_TexCoord).rgb * pow(light_ReflectionAngle, 16);

    float light_Radius = 15.0f;
    float light_Distance = length(light_Position - ex_Position);
    float light_Attenuation = max(0, light_Radius - light_Distance) / light_Radius;

    out_Colour = vec4(ambient, 1) + (vec4(diffuse, 1) + vec4(specular, 1)) * light_Attenuation;
}