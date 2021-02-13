#version 330 core
out vec4 FragColor;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec2 texCoord;
in vec3 viewNormal;
in vec3 viewPos;
in vec3 viewLightPos;



uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform Material material;
uniform Light light;


void main()
{
	vec3 color = mix(texture(texture1, texCoord),texture(texture2, texCoord),0.2).rgb;

	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(viewNormal);
	vec3 lightDir = normalize( viewLightPos - viewPos );
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = light.diffuse * ( diff * material.diffuse );

	vec3 viewDir = normalize(viewPos);
	vec3 reflectDir = reflect( -lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (  spec *  material.specular);

	vec3 result =  ( ambient + diffuse + specular) * color;

    FragColor = vec4(result,1.0);
}