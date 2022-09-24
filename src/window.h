#pragma once

#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Window
{
    int m_width = 0;
    int m_height = 0;
    int m_client_width = 0;
    int m_client_height = 0;

    GLFWwindow *m_glfw_handle = nullptr;

    static Window *s_instance;
    Window(int width, int height, const std::string &title);

public:
    ~Window();
    bool should_close() const;
    void poll_events() const;
    void swap_buffers() const;

    static Window *get_instance();
};
