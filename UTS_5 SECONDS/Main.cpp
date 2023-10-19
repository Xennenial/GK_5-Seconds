#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Util.h"

using namespace std;

unsigned int program;

float velocitySecondPointer = -3.0f;
float velocityMinutePointer = -0.05f;
float velocityHourPointer = -0.0042222222f;
float speed = 1.0f;
float tempspeed = 1.0f;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

char Decision;
int Hour;
int Minute;
int Second;

void keyFowardBackward(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        cout << "Jam dimajukan" << endl;
        glfwSetTime(currentTime + 3600);
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        cout << "Jam dimundurkan" << endl;
        glfwSetTime(currentTime - 3600);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        cout << "Menit dimajukan" << endl;
        glfwSetTime(currentTime + 60);
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        cout << "Menit dimundurkan" << endl;
        glfwSetTime(currentTime - 60);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        cout << "Kecepatan Bertambah" << endl;
        speed += 1.0f;
        tempspeed += 1.0f;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        cout << "Kecepatan Berkurang" << endl;
        speed -= 0.1f;
        tempspeed -= 0.1f;

        if (speed < 0.0f) {
            cout << "Kecepatan Sudah Mencapai Minimum" << endl;
            cout << "Kecepatan Kembali Normal";
            speed = 1.0f;
            tempspeed = 1.0f;
        }
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        cout << "Kecepatan Kembali Normal" << endl;
        speed = 1.0f;
        tempspeed = 1.0f;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        if (speed > 0.0f) {
            cout << "Pause"<<endl;
            speed = 0.0f; 
        }
        else {
            cout << "Continue"<<endl;
            speed = tempspeed;
        }
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        cout << "Input Time : \n";
        cout << "Jam : ";
        cin >> Hour;

        cout << "Menit : ";
        cin >> Minute;

        cout << "Detik : ";
        cin >> Second;

        float hour = Hour * 3600;
        float minute = Minute * 60;
        float second = Second;

        glfwSetTime(hour + minute + second);
        cout << "Time Changed Successfully" << endl;
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 640, "JAM BIG BANG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyFowardBackward);

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
    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speed;
        lastTime = currentTime;

        currentSecondPointer += (deltaTime * velocitySecondPointer);
        currentMinutePointer += (deltaTime * velocityMinutePointer);
        currentHourPointer += (deltaTime * velocityHourPointer);

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