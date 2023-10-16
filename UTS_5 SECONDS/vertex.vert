#version 330

//variabel scale untuk mengirim posisi
//uniform float scale;
layout(location = 0) in vec3 inPosition;
varying vec2 vPos;

void main()
{
    gl_Position = vec4(inPosition.xy /* * scale */, 0.0, 1.0);
    vPos = inPosition.xy;
}
