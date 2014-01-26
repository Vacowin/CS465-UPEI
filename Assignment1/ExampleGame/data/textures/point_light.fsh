#version 150

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float fade;
uniform mat3 WorldIT;
uniform vec3 ViewDir;

uniform vec4 LightAmbient;

uniform vec4 LightSpecular1;
uniform vec4 LightDiffuse1;
uniform vec3 LightAttenuation1;
uniform float LightRange1;
uniform vec3 LightPos1;

uniform vec4 LightSpecular2;
uniform vec4 LightDiffuse2;
uniform vec3 LightAttenuation2;
uniform float LightRange2;
uniform vec3 LightPos2;

in vec2 v_uv1;
in vec3 v_normal;
in vec4 v_pos;
out vec4 PixelColor;

void main()
{
	vec3 n = normalize( v_normal );

	vec3 LightDir1 = LightPos1 - v_pos.xyz;
	float distance1 = length(LightDir1);

	if (distance1 > LightRange1)
	{
		PixelColor += texture(texture1, v_uv1) * vec4( LightAmbient.rgb, 1.0);
	}
	else
	{
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


	vec3 LightDir2 = LightPos2 - v_pos.xyz;
	float distance2 = length(LightDir2);

	if (distance2 > LightRange2)
	{
		PixelColor += texture(texture1, v_uv1) * vec4( LightAmbient.rgb, 1.0);
	}
	else
	{
	// normalize it
	LightDir2 /= distance2;
		
	// Ambient
	vec4 ambient2 = LightAmbient;

	// Diffuse
	vec4 diffuse2 = (LightDiffuse2 * max(0.0,dot(n, LightDir2)));

	// Specular
	float specFactor2 = pow(max(dot(reflect(LightDir2,n), ViewDir), 0.0), 1.0);
	vec4 specular2 = (specFactor2 * texture(texture2, v_uv1) * LightSpecular2);
		
	vec4 light2 = clamp(ambient2 + diffuse2 + specular2, 0, 1);
		
	// Attenuate the light
	float att2 = 1.0 / dot(LightAttenuation2, vec3(1.0, distance2, distance2*distance2));
	light2 *= att2;
	
	PixelColor += texture(texture1, v_uv1) * vec4( light2.rgb, 1.0);
	}
}
