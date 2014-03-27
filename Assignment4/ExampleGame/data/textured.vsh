#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
uniform mat3 worldIT;

in vec4 a_position;
in vec2 a_uv1;
in vec3 a_normal;

out vec2 v_uv1;
out vec4 v_pos;
out vec3 v_normal;

void main()
{
    gl_Position = projection * view * world * a_position;
	v_uv1 = a_uv1;

	vec3 n = (worldIT * a_normal).xyz;
	v_normal = n;
	v_pos = world * a_position;
}
