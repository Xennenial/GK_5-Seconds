#version 330

layout (location = 0) in vec3 pos;
varying vec2 vPos;

void main()
{
	//set the position of the point that will be drawn on the screen
	gl_Position = vec4(pos.xy, 0.0, 1.0);
	vPos = pos.xy;
}