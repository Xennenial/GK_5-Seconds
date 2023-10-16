#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include "Util.h"

using namespace std;

//float color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//float color2[] = { 1.0f, 0.0f, 0.0f, 1.0f };

unsigned int program;
//GLint color1loc, color2loc;

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

float velocitySecondPointer = -18.0f;;
float velocityMinutePointer = -0.295f;
float velocityHourPointer = -0.0251;
float speed = 60.0f;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

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



    GLenum err = glewInit();

    float vertices[] = {
    1.0, 1.0,
    -1.0, 1.0,
    -1.0, -1.0,
    1.0, -1.0
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

   // GLint scaleloc = glGetUniformLocation(program, "scale");
   // glUniform1f(scaleloc, 0.5f);

   // color1loc = glGetUniformLocation(program, "color1");
   // glUniform4f(color1loc, color1[0], color1[1], color1[2], color1[3]);

    //color2loc = glGetUniformLocation(program, "color2");
    //glUniform4f(color2loc, color2[0], color2[1], color2[2], color2[3]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speed;
        lastTime = currentTime;

        currentSecondPointer = currentSecondPointer + (deltaTime * velocitySecondPointer);
        currentMinutePointer = currentMinutePointer + (deltaTime * velocityMinutePointer);
        currentHourPointer = currentHourPointer + (deltaTime * velocityHourPointer);

        glUniform1f(currentSecondPointerLoc, currentSecondPointer / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer / 180.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, nullptr);

        //glfwSetKeyCallback(window, keyCallback);

        // glDrawArrays(GL_TRIANGLES, 0, 6);


        /*
        glColor3f(1.0f, 0.0f,0.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        */



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}