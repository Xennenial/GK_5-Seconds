#version 330

//variabel random color
//uniform vec4 color1;
//uniform vec4 color2;

//variabel jarum-jarum
uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;


layout(location = 0) out vec4 color;
varying vec2 vPos;

void main()
{

    color = vec4(1.0, 1.0, 1.0, 1.0);

    float distance = length (vPos);
    float dotSecond = dot (normalize (vPos), vec2(cos (currentSecondPointer), sin (currentSecondPointer)));

    //drawing second
    if (distance <= 1.00 && distance >= 0.80) //panjang jarum
    {
        if (dotSecond > 0.999) /*lebar jarum*/ color = vec4(1.0, 0.0, 0.0, 1.0);
    }

    float dotMinute = dot (normalize (vPos), vec2(cos (currentMinutePointer), sin (currentMinutePointer)));
    //drawing minute
    if (distance >= 0.50 && distance <= 0.70)
    {
        if (dotMinute > 0.995)
        color = vec4(0.0, 1.0, 0.0, 1.0);
    }

    float dotHour = dot (normalize (vPos), vec2(cos (currentHourPointer), sin (currentHourPointer)));
    //drawing hour
    if (distance >= 0.20 && distance <= 0.40)
    {
        if (dotHour > 0.999)
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }

    //randomcolor
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

