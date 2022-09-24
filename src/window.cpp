#include "window.h"

#include <iostream>

Window *Window::s_instance = nullptr;

Window::Window(int width, int height, const std::string &title)
    : m_width(width)
    , m_height(height)
    , m_client_width(width)
    , m_client_height(height)
{
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "[error] failed to initialize glfw" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_glfw_handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_glfw_handle) {
        std::cerr << "[error] failed to create glfw window" << std::endl;
        std::exit(1);
    }
    glfwMakeContextCurrent(m_glfw_handle);
    if (glewInit() != GLEW_OK) {
        std::cerr << "[error] failed to initialize glew" << std::endl;
        std::exit(1);
    }

    glViewport(0, 0, m_width, m_height);
}

Window::~Window()
{
    glfwDestroyWindow(m_glfw_handle);
    glfwTerminate();
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(m_glfw_handle);
}

void Window::poll_events() const
{
    glfwPollEvents();
}

void Window::swap_buffers() const
{
    glfwSwapBuffers(m_glfw_handle);
}

Window *Window::get_instance()
{
    if (!s_instance) {
        s_instance = new Window(1000, 750, "Fireworks Demo");
    }
    return s_instance;
}