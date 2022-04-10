//
// Created by william on 3/9/22.
//

#include "GLFWSession.h"
#include "DrawableHelper.h"


void GLFWSession::runLoop() {
    loop();

    delete window;
    window = nullptr;
    delete font;
    font = nullptr;
    glfwTerminate();
    glfwSetErrorCallback(nullptr);
}

void GLFWSession::init() {
    glfwSetErrorCallback(
            [](int errCode, const char* errMsg) {
                std::cerr << "GLFW Error: " << errMsg << std::endl;
            }
    );

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = new Window("Battleship", 800, 600, this);

    glfwMakeContextCurrent(window->handle);

    int pWidth, pHeight;
    glfwGetWindowSize(window->handle, &pWidth, &pHeight);
    GLFWvidmode vidmode = *glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window->handle, (vidmode.width - pWidth) / 2, (vidmode.height - pHeight) / 2);

    //enable vsync
    glfwSwapInterval(1);

    window->setVisible(true);
}

void GLFWSession::loop() {
    font = new Font("UbuntuMono-R.ttf");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    onWindowResize(window);

    window->setupFramebuffer();
    auto timeNanos = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    while (!glfwWindowShouldClose(window->handle)) {
        ++frameCount;
        if (frameCount % 10 == 0) {
            auto newTimeNanos = std::chrono::high_resolution_clock::now();
            fps = 10 * (1000000000L / std::chrono::nanoseconds{newTimeNanos - timeNanos}.count());
            timeNanos = newTimeNanos;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDisable(GL_TEXTURE_2D);
        DrawableHelper::rect(-1, -1, 1, 1, 0xFF2b2b2b);

        glPushMatrix();

        glTranslatef(-1, 1, 0);
        glScalef(2.0f / (float) window->getWidth(), -2.0f / (float) window->getHeight(), 1);

        double cursorX, cursorY;
        glfwGetCursorPos(window->handle, &cursorX, &cursorY);

        mtx.lock();
        screen->onRender((float) cursorX, (float) cursorY);
        mtx.unlock();

        glPopMatrix();

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
}