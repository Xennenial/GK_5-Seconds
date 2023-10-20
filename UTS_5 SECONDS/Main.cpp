#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "util.h"
#include "constanta.h"

using namespace std;

unsigned int program;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //key TAB to changed time base on user input
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        cout << "Input Time: " << endl;
        cout << "Hour: ";
        cin >> Hour;

        cout << "Minute: ";
        cin >> Minute;

        cout << "Second: ";
        cin >> Second;

        //multiply the Hour and Minute by the number of seconds per hour and minute
        glfwSetTime((Hour * 3600) + (Minute * 60) + Second);
        cout << "Time has Changed" << endl;
    }
    //key W to move one hour foward
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        cout << "Hour Foward" << endl;
        glfwSetTime(currentTime + 3600);
    }
    //key S to move one hour backward
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        cout << "Hour Backward" << endl;
        glfwSetTime(currentTime - 3600);
    }
    //key A to move one minute backward
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        cout << "Minute Foward" << endl;
        glfwSetTime(currentTime + 60);
    }
    //key D to move one minute foward
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        cout << "Minute Backward" << endl;
        glfwSetTime(currentTime - 60);
    }
    //key RIGHT ARROW to speed up the clock
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        cout << "Clock Speed Up" << endl;
        speed += 1.0f;
        //tempspeed have the same value with speed
        tempspeed += 1.0f;
    }
    //key LEFT ARROW to slow down the clock
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        cout << "Clock Slow Down" << endl;
        speed -= 0.1f;
        tempspeed -= 0.1f;

        //speed can't be less than 0.0 if speed less than 0.0, speed value will be reseted
        if (speed < 0.0f) {
            cout << "Clock Speed Reached Minumum Speed" << endl;
            cout << "Speed Reseted";
            speed = 1.0f;
            tempspeed = 1.0f;
        }
    }
    //Key R to reset speed
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        cout << "Speed Reseted" << endl;
        speed = 1.0f;
        tempspeed = 1.0f;
    }
    //Key P to pause the clock for a while 
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        //if Speed value is not 0 (clock is not on 'pause' condition, Speed value is changed to 0
        if (speed > 0.0f) {
            cout << "Pause"<<endl;
            speed = 0.0f; 
        }
        //if Speed value is 0 (clock is on 'pause' condition, Speed value is changed to tempspeed
        else {
            cout << "Continue"<<endl;
            speed = tempspeed;
        }
    }
    //key C to change clock's color: Hour, Minute, and Second
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        cout << "Colors Have Changed" << endl;
        
        //Looping condition to generate random number for color between min number (0.0) to max number (1.0);
        for (int i = 0; i < 4; i++) {
            colorSecond[i] = (rand() * 1.0f) / RAND_MAX;
            colorMinute[i] = (rand() * 1.0f) / RAND_MAX;
            colorHour[i] = (rand() * 1.0f) / RAND_MAX;
        }
        
        cout << colorSecond[0] << " " << colorSecond[1] << " " << colorSecond[2] << " " << colorSecond[3] << endl;
        cout << colorMinute[0] << " " << colorMinute[1] << " " << colorMinute[2] << " " << colorMinute[3] << endl;
        cout << colorHour[0] << " " << colorHour[1] << " " << colorHour[2] << " " << colorHour[3] << endl;

        glUniform4f(colorSecondLoc, colorSecond[0], colorSecond[1], colorSecond[2], colorSecond[3]);
        glUniform4f(colorMinuteLoc, colorMinute[0], colorMinute[1], colorMinute[2], colorMinute[3]);
        glUniform4f(colorHourLoc, colorMinute[0], colorHour[1], colorHour[2], colorHour[3]);
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(620, 620, "JAM BIG BENG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallBack);

    GLenum err = glewInit();

    float vertices[] = {
        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
     };

    unsigned int indexArr[] = {
        0,1,2,
        0,2,3
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    cout << vertexBuffer << endl;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);



    unsigned indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexArr, GL_STATIC_DRAW);


    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);

    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);


    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    //get the location of the uniform variable
    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    //get the location of the uniform variable and send color data to the shader
    colorSecondLoc = glGetUniformLocation(program, "colorSecond");
    glUniform4f(colorSecondLoc, colorSecond[0], colorSecond[1], colorSecond[2], colorSecond[3]);
    colorMinuteLoc = glGetUniformLocation(program, "colorMinute");
    glUniform4f(colorMinuteLoc, colorMinute[0], colorMinute[1], colorMinute[2], colorMinute[3]);
    colorHourLoc = glGetUniformLocation(program, "colorHour");
    glUniform4f(colorHourLoc, colorHour[0], colorHour[1], colorHour[2], colorHour[3]);

    while (!glfwWindowShouldClose(window))
    {
        //time update
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speed;
        lastTime = currentTime;

        //update the position of the clock hands
        currentSecondPointer += deltaTime * velocitySecondPointer;
        currentMinutePointer += deltaTime * velocityMinutePointer;
        currentHourPointer += deltaTime * velocityHourPointer;

        //Send the position of the clock hands to the shader
        glUniform1f(currentSecondPointerLoc, currentSecondPointer * 3.14159265f / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14159265f / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14159265f / 180.0f);


        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}