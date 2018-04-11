#version 140

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

uniform vec3 light_Ambient = vec3(0.2, 0.2, 0.2);
uniform vec3 light_Diffuse = vec3(0.4, 0.4, 0.4);
uniform vec3 light_Specular = vec3(0.4, 0.4, 0.4);
uniform vec3 light_Position = vec3(0, 3, 0);

uniform vec3 camera_Normal;

void main(void)
{
    mat3 TBN = mat3(
        ex_Tangent,
        ex_Bitangent,
        ex_Normal
    );

    vec3 normal;

    normal = texture(material_Normal, ex_TexCoord).rgb * 2 - 1;
    normal = normalize(normal);
    normal = normalize(TBN * normal);

    vec3 light_Direction = normalize(normalize(light_Position - ex_Position));
    float light_DotProduct = max(0, dot(normal, light_Direction));

    vec3 light_ToCamera = normalize(normalize(ex_ViewPosition - ex_Position));
    vec3 light_Reflection = reflect(-light_Direction, normal);
    float light_ReflectionAngle = max(0, dot(light_ToCamera, light_Reflection));

    vec3 ambient = light_Ambient * texture(material_Diffuse, ex_TexCoord).rgb;
    vec3 diffuse = light_Diffuse * texture(material_Diffuse, ex_TexCoord).rgb * light_DotProduct;
    vec3 specular = light_Specular * texture(material_Specular, ex_TexCoord).rgb * pow(light_ReflectionAngle, 128);

    out_Colour = vec4(pow(ambient + specular + diffuse, vec3(1/2.2)), 1);
}