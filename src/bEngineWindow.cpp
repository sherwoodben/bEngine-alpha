#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineWindow.h"

/// @file bEngineWindow.cpp
/// @brief implementations for the bEngineWindow.h file

#include "bEngineUtilities.h" // for access to info messaging, etc.

#include <format> // for formatting info messages, etc.

#pragma region PLATFORM_IMPLEMENTATIONS

// WINDOWS platform window implementation
#ifdef WIN32

#    include <GLFW\glfw3.h> // the PlatformWindowImpl holds a GLFWWindow*, using GLFW for window management

struct bEngine::bEngineWindow::PlatformWindowImpl
{
    /// @brief helper function which creates a GLFW window with the appropriate window hints and the desired size/title
    /// @param width the desired width of the window (in pixels)
    /// @param height the desired height of the window (in pixels)
    /// @param title the desired title for the window
    /// @return the GLFWwindow* associated with the new window
    static GLFWwindow *const create_glfw_window_with_hints(const int width, const int height, const char *const title)
    {
        // only set the debug context to true in debug mode
#    ifdef DEBUG
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#    endif // DEBUG

        // tageting GL 4.6 (core)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // for now, we do NOT want windows to be (freely) resizable BUT this is likely to change in the future!
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        return glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    /// @brief the GLFWWindow* associated with this PlatformWindowImpl
    GLFWwindow *const m_glfwWindow{nullptr};

    /// @brief default ctor is insufficient
    PlatformWindowImpl() = delete;

    /// @brief ctor which takes the necessary arguments to actually construct a PlatformWindowImpl
    ///
    /// creates a GLFWwindow and stores the pointer to the window
    /// @param width the desired width of the window (in pixels)
    /// @param height the desired height of the window (in pixels)
    /// @param title the desired title of the window
    PlatformWindowImpl(const int width, const int height, const char *const title)
        : m_glfwWindow{create_glfw_window_with_hints(width, height, title)} { };

    /// @brief dtor destroys the GLFWwindow associated with this PlatformWindowImpl
    ~PlatformWindowImpl() { glfwDestroyWindow(m_glfwWindow); };

    /// @brief gets the window's "should close" state by calling the GLFW provided function
    ///
    /// NOT using events/callbacks at this time
    /// @return true if the window should close (i.e. the 'X' button was closed, or ALT+F4, etc.) and false if the
    /// window should stay open
    const bool get_should_close() const { return glfwWindowShouldClose(m_glfwWindow); };
};

#endif // WIN32

#pragma endregion

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
