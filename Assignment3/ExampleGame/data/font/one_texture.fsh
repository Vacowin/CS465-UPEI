#version 150
in vec2 v_uv1;

uniform vec4 fontcolor;
uniform sampler2D tex;

out vec4 PixelColor;

void main()
{
	PixelColor = texture(tex, v_uv1) * fontcolor;
}
