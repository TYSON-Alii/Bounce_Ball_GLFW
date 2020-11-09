#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
double const PI = 3.14;
double xpos;
double ypos;
float mouse_pos_x;
float mouse_pos_y;
float yon = 0;
float x = 250;
float y = 250;
float hareket_y = 0;
float hareket_x = 0;
float yari_cap = 100;
bool tiklandimi = false;
bool basildimi = false;
bool key_press_right = false;
bool key_press_left = false;

GLFWwindow* window = NULL;
GLFWmonitor* monitor = NULL;

void keyboard(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        key_press_right = true;
    }
    else
    {
        key_press_right = false;
    }

    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        key_press_left = true;
    }
    else
    {
        key_press_left = false;
    }
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        hareket_y = 0.1;
    }
}

void mouse(GLFWwindow* window,int button,int action,int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        tiklandimi = true;
    }
    else
    {
        tiklandimi = false;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        basildimi = true;
    }
    else
    {
        basildimi = false;
    }
}

void sekiller()
{
    if(yari_cap < 2)
    {
        yari_cap = 100;
    }
    glLoadIdentity();

    glPointSize(4);
    glTranslatef(x,y,0);

    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    float i;
    for(i = -1; i <= 1; i += 1 / yari_cap)
    {
        glVertex2f(cos(i*PI)*yari_cap,sin(i*PI)*yari_cap);
    }
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    window = glfwCreateWindow(500, 500, "HELLO WORLD!!",NULL, NULL);
    if(!window)
        throw std::runtime_error("glfwOpenWindow failed.");
    glfwMakeContextCurrent(window);
    glViewport(0.0f, 0.0f,500,500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,500,0,500,0,1);
    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.75, 0.75, 0.75, 1);
        sekiller();

        glfwSetKeyCallback(window, keyboard);
        glfwSetMouseButtonCallback(window ,mouse);
        glfwGetCursorPos(window, &xpos, &ypos);

        glLoadIdentity();
        glfwSwapBuffers(window);

        glfwPollEvents();

        hareket_y -= 0.0001;
        y = y + hareket_y;
        x = x + hareket_x;

        if(key_press_left)
        {
            hareket_x -= 0.0001;
        }
        if(key_press_right)
        {
            hareket_x += 0.0001;
        }

        mouse_pos_x = xpos;
        if(ypos < 250)
        {
            mouse_pos_y = 500 - ypos;
        }
        else if(ypos > 250)
        {
            mouse_pos_y = fabs(ypos - 500);
        }
        if(tiklandimi)
        {
            yari_cap += 0.01;
        }
        if(basildimi)
        {
            yari_cap -= 0.01;
        }
        if(y - yari_cap < 0 || y + yari_cap > 500)
        {
            hareket_y = -hareket_y;
        }
        if(x - yari_cap < 0 || x + yari_cap > 500)
        {
            hareket_x = -hareket_x;
        }

    }
    glfwTerminate();
    return 0;
}
