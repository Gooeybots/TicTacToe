#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

void Resize(GLFWwindow * window, int width, int height);

bool SetupWindow(const char * title, const int width, const int height)
{
    if(glfwInit() != GL_TRUE)
        std::cerr << "Couldn't initialize glfw\n";
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow* window(glfwCreateWindow(width, height, title, NULL, NULL));

        if(!window)
            std::cerr << "Couldn't create OpenGL context\n";
        else
        {
            glfwMakeContextCurrent(window);

            glewExperimental = GL_TRUE;
            if(glewInit() != GLEW_OK)
                std::cerr << "Couldn't initialize glew\n";
            else
            {
// had to add this is as GLEW was giving me an unknown enum error(1280) :(
                GLenum err(glGetError());
                if(!(err == 1280 || err == GL_NO_ERROR))
                    std::cerr << "ERROR I REPEAT ERROR: " << err << "\n";

                glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
                glfwSetWindowSizeCallback(window, Resize);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glViewport(0, 0, width, height);

                return true;
            }
        }
    }
    return false;
}

// To keep viewport square
void Resize(GLFWwindow * window, int width, int height)
{
// really no point in window apart from killing the issue message of unused var
    if(width == height && window)
    {
        glViewport(0, 0, width, height);
    }
    else if(width < height)
    {
        int bottom;
        bottom = (height - width) / 2;
        glViewport(0, bottom, width, width);
    }
    else
    {
        int left;
        left = (width - height) / 2;
        glViewport(left, 0, height, height);
    }
}
