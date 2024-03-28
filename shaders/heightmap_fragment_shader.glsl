#version 330 core

in vec3 Position;
vec4 color;

out vec4 Fragment_color;

uniform float Height;

uniform vec3 position;
uniform float intensity;

uniform vec3 Eye;

in vec3 Normal;
in vec4 ModelPosition;



void main()
{
        vec3 normal = normalize(Normal);
        
    	vec3 lightDirection = position - ModelPosition.xyz;

		vec3 ambient = intensity * vec3(0.5f);

		vec3 norm = normal.xyz;

		vec3 N = normalize(norm);
		vec3 L = normalize(lightDirection);

		vec3 diffuse = max(dot(N, L), 0.0) * intensity * vec3(1.0f);

		vec3 V = normalize(Eye - ModelPosition.xyz);
		vec3 R = reflect(-L, N);

		vec3 specular = pow(max(dot(V, R), 0.0), 4.0f) * vec3(1.0f);

		vec3 result = (ambient + diffuse + specular);

    float Scaled_y = Position.y;

    float height = Height ;

    float H1Q1 = height * (0.3f) ;
    float H2Q1 = height * (0.4f) ;

    float H1Q2 = height * (0.45f ) ;
    float H2Q2 = height * (0.55f ) ;

    float Q3 = height * (0.625f) ;
    float Q4 = height * (0.75f ) ;

    if(Position.y > Q3)//color gray for the peaks
    {
        color = vec4(vec3(0.9f), 1.0f) * vec4((ambient + diffuse ), 1.0f);
    }

    else if(Position.y >= H2Q2 && Position.y <= Q3)
    {
        color = vec4(vec3(0.5f), 1.0f) * vec4((ambient + diffuse), 1.0f) ;
    }

    else if(Position.y >= H2Q1 && Position.y <= H2Q2)
    {
            color = vec4(vec3(0.2f,  0.41f, 0.2), 1.0f) * vec4((ambient + diffuse), 1.0f) ;
    }

    else if(Position.y >= H1Q2 && Position.y <= H2Q1)
    {
          color = vec4(vec3(0.7098f,  0.3961f, 0.1137), 1.0f) * vec4((ambient + diffuse), 1.0f) ;
    }

    else if(Position.y >= H1Q1 && Position.y <= H1Q2)
    {
          color = vec4(vec3(0.761f,  0.698, 0.502), 1.0f) * vec4((ambient + diffuse), 1.0f) ;
    }

    else if(Position.y < H1Q1)//sky blue for poodle at lowest depths
    {
        color = vec4(vec3(0.0f, 0.44f, 0.54f), 1.0f) * vec4(result, 1.0f);
    }

    Fragment_color = vec4(color);
}