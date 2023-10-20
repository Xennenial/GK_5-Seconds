#version 330

uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

uniform vec4 colorSecond;
uniform vec4 colorMinute;
uniform vec4 colorHour;

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	
	float distance = length(vPos);

	//drawing hour
	float dotHour = dot(normalize(vPos), vec2(0.8 * cos(currentHourPointer), 0.8 * sin(currentHourPointer)));
	if (distance <= 0.9 && distance >= 0.8 && dotHour < 0.8 * sin(currentHourPointer))
	{
		 color = vec4(1.0, 0.0, 0.0, 1.0);
	}

	//drawing minute
	float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));
	if (distance <= 0.6 && distance >= 0.5 && dotMinute < 0.6 * sin(currentMinutePointer))
	{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}

	//drawing second
	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
	if (distance <= 0.3 && distance >= 0.2 && dotSecond < sin(currentSecondPointer))
	{
			color = vec4(0.0, 0.0, 1.0, 1.0);
	}

}

