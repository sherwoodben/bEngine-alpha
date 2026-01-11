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

#    include <unordered_map> // for storing translation from bEngineKeyCode to GLFW_KEY codes

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

    /// @brief sets  the window's "should close" state by calling the GLFW provided function
    /// @param shouldClose true if the window should close (i.e. we're programatically closing a window) and false if
    /// the window should stay open
    void set_should_close(const bool shouldClose) const
    {
        glfwSetWindowShouldClose(m_glfwWindow, shouldClose ? GLFW_TRUE : GLFW_FALSE);
    };

    /// @brief for each of the inputs bEngine recognizes (keyboard, mouse, etc.) updates the input state so it's
    /// available for processing elsewhere
    /// @param inputState the input state struct to store the results in
    void update_input_state(bEngineInputState &inputState) const
    {
        // store a "translation" from the bEngineKeyCode enum to the GLFW_KEY_ bindings which are just ints
        static const std::unordered_map<bEngineKeyCode, int> keyBindings{
            {            bEngineKeyCode::key_1,             GLFW_KEY_1},
            {            bEngineKeyCode::key_2,             GLFW_KEY_2},
            {            bEngineKeyCode::key_3,             GLFW_KEY_3},
            {            bEngineKeyCode::key_4,             GLFW_KEY_4},
            {            bEngineKeyCode::key_5,             GLFW_KEY_5},
            {            bEngineKeyCode::key_6,             GLFW_KEY_6},
            {            bEngineKeyCode::key_7,             GLFW_KEY_7},
            {            bEngineKeyCode::key_8,             GLFW_KEY_8},
            {            bEngineKeyCode::key_9,             GLFW_KEY_9},
            {            bEngineKeyCode::key_0,             GLFW_KEY_0},

            {            bEngineKeyCode::key_a,             GLFW_KEY_A},
            {            bEngineKeyCode::key_b,             GLFW_KEY_B},
            {            bEngineKeyCode::key_c,             GLFW_KEY_C},
            {            bEngineKeyCode::key_d,             GLFW_KEY_D},
            {            bEngineKeyCode::key_e,             GLFW_KEY_E},
            {            bEngineKeyCode::key_f,             GLFW_KEY_F},
            {            bEngineKeyCode::key_g,             GLFW_KEY_G},
            {            bEngineKeyCode::key_h,             GLFW_KEY_H},
            {            bEngineKeyCode::key_i,             GLFW_KEY_I},
            {            bEngineKeyCode::key_j,             GLFW_KEY_J},
            {            bEngineKeyCode::key_k,             GLFW_KEY_K},
            {            bEngineKeyCode::key_l,             GLFW_KEY_L},
            {            bEngineKeyCode::key_m,             GLFW_KEY_M},
            {            bEngineKeyCode::key_n,             GLFW_KEY_N},
            {            bEngineKeyCode::key_o,             GLFW_KEY_O},
            {            bEngineKeyCode::key_p,             GLFW_KEY_P},
            {            bEngineKeyCode::key_q,             GLFW_KEY_Q},
            {            bEngineKeyCode::key_r,             GLFW_KEY_R},
            {            bEngineKeyCode::key_s,             GLFW_KEY_S},
            {            bEngineKeyCode::key_t,             GLFW_KEY_T},
            {            bEngineKeyCode::key_u,             GLFW_KEY_U},
            {            bEngineKeyCode::key_v,             GLFW_KEY_V},
            {            bEngineKeyCode::key_w,             GLFW_KEY_W},
            {            bEngineKeyCode::key_x,             GLFW_KEY_X},
            {            bEngineKeyCode::key_y,             GLFW_KEY_Y},
            {            bEngineKeyCode::key_z,             GLFW_KEY_Z},

            {     bEngineKeyCode::key_arrow_up,            GLFW_KEY_UP},
            {  bEngineKeyCode::key_arrow_right,         GLFW_KEY_RIGHT},
            {   bEngineKeyCode::key_arrow_down,          GLFW_KEY_DOWN},
            {   bEngineKeyCode::key_arrow_left,          GLFW_KEY_LEFT},

            {       bEngineKeyCode::key_escape,        GLFW_KEY_ESCAPE},
            {    bEngineKeyCode::key_backspace,     GLFW_KEY_BACKSPACE},
            {          bEngineKeyCode::key_tab,           GLFW_KEY_TAB},
            {    bEngineKeyCode::key_caps_lock,     GLFW_KEY_CAPS_LOCK},
            {        bEngineKeyCode::key_enter,         GLFW_KEY_ENTER},
            {   bEngineKeyCode::key_shift_left,    GLFW_KEY_LEFT_SHIFT},
            {  bEngineKeyCode::key_shift_right,   GLFW_KEY_RIGHT_SHIFT},
            { bEngineKeyCode::key_control_left,  GLFW_KEY_LEFT_CONTROL},
            {     bEngineKeyCode::key_alt_left,      GLFW_KEY_LEFT_ALT},
            {        bEngineKeyCode::key_space,         GLFW_KEY_SPACE},
            {    bEngineKeyCode::key_alt_right,     GLFW_KEY_RIGHT_ALT},
            {bEngineKeyCode::key_control_right, GLFW_KEY_RIGHT_CONTROL},
        };

        // store a "translation" from the bEngineMouseButtonCode enum to the GLFW_MOUSE_BUTTON_ bindings which are just
        // ints
        static const std::unordered_map<bEngineMouseButtonCode, int> mouseButtonBindings{
            { bEngineMouseButtonCode::mouse_left, GLFW_MOUSE_BUTTON_1},
            {  bEngineMouseButtonCode::mouse_mid, GLFW_MOUSE_BUTTON_3},
            {bEngineMouseButtonCode::mouse_right, GLFW_MOUSE_BUTTON_2},
        };

        // helper function which translates the bEngineKeyCode to a GLFW_KEY_ binding and returns the state (where true
        // means the key is pressed)
        const auto get_key_is_down = [this](const bEngineKeyCode keyCode) -> const bool {
            if (keyBindings.contains(keyCode))
            {
                const auto keyState = glfwGetKey(m_glfwWindow, keyBindings.at(keyCode));
                return (keyState == GLFW_PRESS || keyState == GLFW_REPEAT);
            }
            return false;
        };

        // helper function which translates the bEngineMouseButtonCode to a GLFW__MOUSE_BUTTON_ binding and returns the
        // state (where true means the key is pressed)
        const auto get_mouse_button_is_down = [this](const bEngineMouseButtonCode mouseButtonCode) -> const bool {
            if (mouseButtonBindings.contains(mouseButtonCode))
            {
                const auto buttonState = glfwGetMouseButton(m_glfwWindow, mouseButtonBindings.at(mouseButtonCode));
                return (buttonState == GLFW_PRESS || buttonState == GLFW_REPEAT);
            }
            return false;
        };

        // for each of the keys we're interested in, set the state of the key in the inputState struct
        for (bEngineKeyCode keyCode = bEngineKeyCode::first; keyCode != bEngineKeyCode::last; ++keyCode)
        {
            inputState.set_key_state(keyCode, get_key_is_down(keyCode));
        }

        // do the same for mouse buttons
        for (bEngineMouseButtonCode mouseButtonCode = bEngineMouseButtonCode::first;
             mouseButtonCode != bEngineMouseButtonCode::last;
             ++mouseButtonCode)
        {
            inputState.set_mouse_button_state(mouseButtonCode, get_mouse_button_is_down(mouseButtonCode));
        }

        // update the mouse position... being sure to normalize the position with respect to the window's size!
        // this is somewhat gross because we're storing the size of the window in the outer (not pimpl) window struct so
        // we don't have access to the stored values here. We could fix that by adding a pointer to the parent window
        // struct on the creation of the PIMPL, but we'll need to update those values if the window size changes
        // eventually and there's no way to do that either currently. Will consider options for when it comes time to
        // clean this up!
        double mouseX{0.0};
        double mouseY{0.0};
        glfwGetCursorPos(m_glfwWindow, &mouseX, &mouseY);

        int windowWidth{0};
        int windowHeight{0};
        glfwGetWindowSize(m_glfwWindow, &windowWidth, &windowHeight);

        inputState.set_mouse_axis_state(bEngineMouseAxisCode::mouse_x, (mouseX / static_cast<double>(windowWidth)));
        inputState.set_mouse_axis_state(bEngineMouseAxisCode::mouse_y, (mouseY / static_cast<double>(windowHeight)));
    };
};

#endif // WIN32

#pragma endregion

bEngine::bEngineWindow::bEngineWindow(WindowToken, const int width, const int height, std::string &&title)
    : m_size{width, height},
      m_title{title},
      m_impl{std::make_unique<PlatformWindowImpl>(m_size[0], m_size[1], m_title.c_str())} { };

bEngine::bEngineWindow::~bEngineWindow() { };

const bEngine::bEngineInputState &bEngine::bEngineWindow::get_input_state() const
{
    return m_inputState;
}

std::unique_ptr<bEngine::bEngineWindow> bEngine::bEngineWindow::create_window(
    const int     width,
    const int     height,
    std::string &&title)
{
    std::unique_ptr<bEngine::bEngineWindow> window{
        std::make_unique<bEngine::bEngineWindow>(WindowToken{}, width, height, std::move(title))};

    INFO_MSG(std::format("[WINDOW #{}] Created window.", window->get_window_ID()));

    return window;
}

const bool bEngine::bEngineWindow::get_should_close() const
{
    return m_impl->get_should_close();
}

const unsigned int bEngine::bEngineWindow::get_window_ID() const
{
    return m_windowID;
}

void bEngine::bEngineWindow::set_should_close(const bool shouldClose) const
{
    INFO_MSG(std::format("[WINDOW #{}] Set 'should close' flag to {}.", m_windowID, shouldClose ? "TRUE" : "FALSE"));
    m_impl->set_should_close(shouldClose);
}

void bEngine::bEngineWindow::update(const double deltaTime)
{
    // then, update the input state
    m_impl->update_input_state(m_inputState);
}