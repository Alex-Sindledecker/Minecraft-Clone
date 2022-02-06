#version 330 core

in vec3 normal;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vec3(1, 1, 1);

    vec3 result = ambient * vec3(1, 0, 0);

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-vec3(-0.3, -1, -0.1));
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1, 1, 1);

   FragColor = vec4((ambient + diffuse) * vec3(1, 0, 0), 1);
}