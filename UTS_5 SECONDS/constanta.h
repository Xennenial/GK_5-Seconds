#pragma once

float velocitySecondPointer = -3.0f;
float velocityMinutePointer = -0.05f;
float velocityHourPointer = -0.004166666666f;
float speed = 1.0f;
float tempspeed = 1.0f;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float Second;
float Minute;
float Hour;

GLint colorSecondLoc;
GLint colorMinuteLoc;
GLint colorHourLoc;

float colorSecond[] = { 0.0, 0.0, 1.0, 1.0 };
float colorMinute[] = { 0.0, 1.0, 0.0, 1.0 };
float colorHour[] = { 1.0, 0.0, 0.0, 1.0 };
