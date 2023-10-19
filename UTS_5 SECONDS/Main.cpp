#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Util.h"

using namespace std;

//float color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//float color2[] = { 1.0f, 0.0f, 0.0f, 1.0f };

unsigned int program;
//GLint color1loc, color2loc;

//key ganti warna random
/*void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        for (int i = 0; i < 4; i++)
        {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
        }

        cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << color1[3] << endl;
        cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << color2[3] << endl;

        glUniform4f(color1loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2loc, color2[0], color2[1], color2[2], color2[3]);
    }
}*/

//key memaju/memundurkan jam buat tambah/kurang 
/*
*/

//key memaju/memundurkan menit
/*
*/

//key mempercepat/memperlambat dan mereset kecepatan jam (buat +/- 1.0x per key ditekan)
/*
*/

//membuat pengguna dapat memasukkan waktu yang spesifik dengan mengubah satu variabel pada program
/*
*/

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

//Key Forward-Backward Hour and Minute, Speed Control
void keyFowardBackward(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        cout << "Jam dimajukan" << endl;
        currentHourPointer -= 94.28571428571429f;
        currentTime = currentTime;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        cout << "Jam dimundurkan" << endl;
        currentHourPointer += 94.28571428571429f;
        currentTime = currentTime;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            cout << "Menit dimajukan" << endl;
            currentMinutePointer -= 18.85714285714286f;
            currentHourPointer -= 1.571428571428571f;
            currentTime = currentTime;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
            cout << "Menit dimundurkan" << endl;
            currentMinutePointer += 18.85714285714286f;
            currentHourPointer += 1.571428571428571f;
            currentTime = currentTime;
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

        // Calculate the angle for the second hand
        currentSecondPointer = (Second / 60) * (2 * 3.14159265358979323846 / 60);

        // Calculate the angle for the minute hand, including the seconds
        currentMinutePointer = (Minute / 60) * (2 * 3.14159265358979323846 / 60) + currentSecondPointer / 60;

        // Calculate the angle for the hour hand, including the minutes and seconds
        currentHourPointer = (Hour / 12) * (2 * 3.14159265358979323846 / 12) + currentMinutePointer / 12 + currentSecondPointer / 720;
    }
}

/* User Menentukan Waktu??
void DeclareTime() {
    cout << "Ingin Menentukan Jam (Y/N): " << endl;
    cin >> Decision;
    Decision = toupper(Decision);

    if (Decision == 'Y') {
        cout << "Masukkan Jam, Menit, dan Detik: ";
        cin >> Hour >> Minute >> Second;

        currentSecondPointer += Second * -18.85714285714286f;
        currentMinutePointer += (Minute * -18.85714285714286f) + (Second * -0.3142857143f);
        currentHourPointer += (Hour * -94.28571428571429f) + (Minute * -1.571428571428571f) + (Second * -0.000436508f);
    }
}
*/

//Key Speed Controller

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "JAM BIG BANG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Input Key
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