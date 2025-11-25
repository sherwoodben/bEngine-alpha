#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineWindow.h"

/// @file bEngineWindow.cpp
/// @brief implementations for the bEngineWindow.h file

#include "bEngineUtilities.h"

#include <format>

// WINDOWS platform window implementation
#ifdef WIN32

#    include <GLFW\glfw3.h>

struct bEngine::bEngineWindow::PlatformWindowImpl
{
    static GLFWwindow *const create_glfw_window_with_hints(const int width, const int height, const char *const title)
    {
#    ifdef DEBUG
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#    endif // DEBUG

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        return glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    GLFWwindow *const m_glfwWindow{nullptr};

    PlatformWindowImpl() = delete;

    PlatformWindowImpl(const int width, const int height, const char *const title)
        : m_glfwWindow{create_glfw_window_with_hints(width, height, title)} { };

    ~PlatformWindowImpl() { glfwDestroyWindow(m_glfwWindow); };

    const bool get_should_close() const { return glfwWindowShouldClose(m_glfwWindow); };
};

#endif // WIN32

const std::string bEngine::bEngineWindow::s_defaultWindowName{"bEngine-alpha Window"};

bEngine::bEngineWindow::bEngineWindow(
    WindowToken,
    const int                 width,
    const int                 height,
    std::string             &&title,
    bEngine::window_render_fn renderFn)
    : m_size{width, height},
      m_title{title},
      m_renderFn{renderFn},
      m_impl{std::make_unique<PlatformWindowImpl>(m_size[0], m_size[1], m_title.c_str())}
{
    INFO_MSG(std::format("Created Window #{}", m_windowID));
}

bEngine::bEngineWindow::~bEngineWindow()
{
    INFO_MSG(std::format("Destroyed Window #{}", m_windowID));
}

std::unique_ptr<bEngine::bEngineWindow> bEngine::bEngineWindow::create_window(
    const int                 width,
    const int                 height,
    std::string             &&title,
    bEngine::window_render_fn renderFn)
{
    return std::make_unique<bEngine::bEngineWindow>(WindowToken{}, width, height, std::move(title), renderFn);
}

const bool bEngine::bEngineWindow::get_should_close() const
{
    return m_impl->get_should_close();
}

const unsigned int bEngine::bEngineWindow::get_window_ID() const
{
    return m_windowID;
}

void bEngine::bEngineWindow::render() const
{
    if (m_renderFn)
    {
        m_renderFn(this);
    }
}
