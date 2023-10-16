#version 330

//uniform vec4 color1;
//uniform vec4 color2;

uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

layout(location = 0) out vec4 color;
varying vec2 vPos;

void main()
{

    color = vec4(0.0, 0.0, 0.0, 1.0);

    float distance = length (vPos);
    float dotSecond = dot (normalize (vPos), vec2(cos (currentSecondPointer), sin (currentSecondPointer)));

    //drawing second

    //panjang jarum
    if (distance <= 0.9)
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);

        //lebar jarum
        if (dotSecond > 0.999) color = vec4(1.0, 0.0, 0.0, 1.0);
    }

    float dotMinute = dot (normalize (vPos), vec2(cos (currentMinutePointer), sin (currentMinutePointer)));
    //drawing minute
    if (distance <= 0.6 && dotMinute > 0.995)
    {
        color = vec4(0.0, 1.0, 0.0, 1.0);
    }

    float dotHour = dot (normalize (vPos), vec2(cos (currentHourPointer), sin (currentHourPointer)));
    //drawing hour
    if (distance <= 0.3 && dotHour > 0.999)
    {
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }


    /*if (vPos.y < 0)
    {
        color = color1;
     }
    else
    {
        color = color2;
    }
    */  

}

