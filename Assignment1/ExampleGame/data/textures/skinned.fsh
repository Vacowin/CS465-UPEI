#version 150

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float fade;
uniform mat3 WorldIT;
uniform vec3 ViewDir;

// Light
uniform vec4 LightAmbient;
uniform vec4 LightSpecular;
uniform vec4 LightDiffuse;
uniform vec3 LightDir;

uniform vec4 LightSpecular1;
uniform vec4 LightDiffuse1;
uniform vec3 LightAttenuation1;
uniform float LightRange1;
uniform vec3 LightPos1;

in vec2 v_uv1;
in vec3 v_normal;
in vec4 v_pos;
out vec4 PixelColor;

void main()
{
	vec3 n = normalize( v_normal );

	// Ambient
	//vec4 ambient = LightAmbient;

	// Diffuse
	//vec4 diffuse = (LightDiffuse * max(0.0,dot(n, -LightDir)));

	// Specular
	//float specFactor = pow(max(dot(reflect(LightDir,n), ViewDir), 0.0), 1.0);
	//vec4 specular = (specFactor * texture(texture2, v_uv1) * LightSpecular);
    
	//vec4 light = clamp(ambient + diffuse + specular, 0, 1);

    //PixelColor = texture(texture1, v_uv1) * vec4( light.rgb, 1.0);

	vec3 LightDir1 = LightPos1 - v_pos.xyz;
	float distance1 = length(LightDir1);

	// normalize it
	LightDir1 /= distance1;
		
	// Ambient
	vec4 ambient1 = LightAmbient;

	// Diffuse
	vec4 diffuse1 = (LightDiffuse1 * max(0.0,dot(n, LightDir1)));

	// Specular
	float specFactor1 = pow(max(dot(reflect(LightDir1,n), ViewDir), 0.0), 1.0);
	vec4 specular1 = (specFactor1 * texture(texture2, v_uv1) * LightSpecular1);
		
	vec4 light1 = clamp(ambient1 + diffuse1 + specular1, 0, 1);
		
	// Attenuate the light
	float att = 1.0 / dot(LightAttenuation1, vec3(1.0, distance1, distance1*distance1));
	light1 *= att;
	
	PixelColor += texture(texture1, v_uv1) * vec4( light1.rgb, 1.0);
}
