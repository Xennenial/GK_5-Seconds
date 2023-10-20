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
	//background color white
	color = vec4(1.0, 1.0, 1.0, 1.0);
	
	//calculates the distance of the current point (vPos) from the center point
	float distance = length(vPos);

	//calculates the dot product between the normalized vPos and the hands direction vector
	float dotHour = dot(normalize(vPos), vec2(0.9 * cos(currentHourPointer), 0.9 * sin(currentHourPointer)));
	
	//drawing hour
	if (distance <= 0.9 && distance >= 0.8 && dotHour < 0.9 * sin(currentHourPointer))
	{
		//giving color
		 color = colorHour;
	}
	
	//calculates the dot product between the normalized vPos and the hands direction vector
	float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));
	//drawing minute
	if (distance <= 0.6 && distance >= 0.5 && dotMinute < 0.6 * sin(currentMinutePointer))
	{
		//giving color
		color = colorMinute;
	}

	//calculates the dot product between the normalized vPos and the hands direction vector
	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
	//drawing second
	if (distance <= 0.3 && distance >= 0.2 && dotSecond < sin(currentSecondPointer))
	{		
			//giving color
			color = colorSecond;
	}

}

