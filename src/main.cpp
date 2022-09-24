
#include "firework.h"
#include "island.h"
#include "model.h"
#include "ocean.h"
#include "window.h"

int main()
{
    Window *window = Window::get_instance();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    Camera camera;

    Ocean ocean;
    Island island;
    Firework fireworks[] = {
        Firework(glm::vec3(1.0f, -1.0f, 2.0f), "res/textures/red.png"),
        Firework(glm::vec3(-2.0f, -1.0f, -2.0f), "res/textures/blue.png"),
        Firework(glm::vec3(2.0f, -1.0f, 0.0f), "res/textures/white.png"),
        Firework(glm::vec3(0.0f, -1.0f, 2.0f), "res/textures/yellow.png"),
        Firework(glm::vec3(-1.0f, -1.0f, 2.0f), "res/textures/green.png"),
    };

    float prev_time = -1.0f;
    while (!window->should_close()) {
        window->poll_events();
        window->swap_buffers();

        float curr_time = glfwGetTime();
        if (prev_time < 0.0f) {
            prev_time = curr_time;
        }
        float delta_time = curr_time - prev_time;
        prev_time = curr_time;

        ocean.update(delta_time);
        island.update(delta_time);
        for (Firework &firework : fireworks) {
            firework.update(delta_time);
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ocean.render(&camera);
        island.render(&camera);
        for (Firework &firework : fireworks) {
            firework.render(&camera);
        }
    }
    delete window;
}