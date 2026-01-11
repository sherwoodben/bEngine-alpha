#pragma once

/// @file bEngineInput.h
/// @brief definitions and declarations associated with user-input

#include <string>        // for storing the various input codes as human-readable strings
#include <unordered_map> // for storing input state based on an enum value

namespace bEngine
{
    /// @brief keycodes associated with keyboard input
    enum struct bEngineKeyCode : uint16_t
    {
        key_1 = 0,
        key_2,
        key_3,
        key_4,
        key_5,
        key_6,
        key_7,
        key_8,
        key_9,
        key_0,

        key_a,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,

        key_arrow_up,
        key_arrow_right,
        key_arrow_down,
        key_arrow_left,

        key_escape,
        key_backspace,
        key_tab,
        key_caps_lock,
        key_enter,
        key_shift_left,
        key_shift_right,
        key_control_left,
        key_alt_left,
        key_space,
        key_alt_right,
        key_control_right,

        last,
        first = key_1,
    };

    /// @brief gets a human readable string associated with a bEngineKeyCode
    /// @param keyCode the bEngineKeyCode in question
    /// @return a human readable string representing the bEngineKeyCode (i.e. 'A' for bEngineKeyCode::key_a)
    const std::string get_keycode_name(const bEngineKeyCode keyCode);

    /// @brief custom incrementor so we can iterate over the key codes
    /// @param keyCode the keyCode to increment
    /// @return the next sequential keyCode, or bEngineKeyCode::last if there is no next key code
    inline bEngineKeyCode operator++(bEngineKeyCode keyCode)
    {
        if (keyCode != bEngineKeyCode::last)
        {
            // cast from a bEngineKeyCode to a uint16_t, add one, then cast the result back to a bEngineKeyCode
            return static_cast<bEngineKeyCode>(static_cast<uint16_t>(keyCode) + 1);
        }

        return bEngineKeyCode::last;
    };

    enum struct bEngineMouseButtonCode : uint16_t
    {
        mouse_left = 0,
        mouse_mid,
        mouse_right,

        last,
        first = mouse_left,
    };

    /// @brief gets a human readable string associated with a bEngineMouseButtonCode
    /// @param keyCode the bEngineMouseButtonCode in question
    /// @return a human readable string representing the bEngineMouseButtonCode (i.e. 'L MOUSE' for
    /// bEngineKeyCode::mouse_left)
    const std::string get_mouse_button_code_name(const bEngineMouseButtonCode mouseButtonCode);

    /// @brief custom incrementor so we can iterate over the key codes
    /// @param keyCode the keyCode to increment
    /// @return the next sequential keyCode, or bEngineKeyCode::last if there is no next key code
    inline bEngineMouseButtonCode operator++(bEngineMouseButtonCode mouseButtonCode)
    {
        if (mouseButtonCode != bEngineMouseButtonCode::last)
        {
            // cast from a bEngineMouseButtonCode to a uint16_t, add one, then cast the result back to a
            // bEngineMouseButtonCode
            return static_cast<bEngineMouseButtonCode>(static_cast<uint16_t>(mouseButtonCode) + 1);
        }

        return bEngineMouseButtonCode::last;
    };

    enum struct bEngineMouseAxisCode : uint16_t
    {
        mouse_x,
        mouse_y,

        last,
        first = mouse_x,
    };

    /// @brief gets a human readable string associated with a bEngineMouseAxisCode
    /// @param keyCode the bEngineMouseAxisCode in question
    /// @return a human readable string representing the bEngineMouseAxisCode (i.e. 'MOUSE X' for
    /// bEngineMouseAxisCode::mouse_x)
    const std::string get_mouse_axis_code_name(const bEngineMouseAxisCode mouseAxisCode);

    /// @brief custom incrementor so we can iterate over the mouse axis codes
    /// @param keyCode the mouseAxisCode to increment
    /// @return the next sequential mouseAxisCode, or bEngineMouseAxisCode::last if there is no next axis code
    inline bEngineMouseAxisCode operator++(bEngineMouseAxisCode mouseAxisCode)
    {
        if (mouseAxisCode != bEngineMouseAxisCode::last)
        {
            // cast from a bEngineMouseButtonCode to a uint16_t, add one, then cast the result back to a
            // bEngineMouseButtonCode
            return static_cast<bEngineMouseAxisCode>(static_cast<uint16_t>(mouseAxisCode) + 1);
        }

        return bEngineMouseAxisCode::last;
    };

    /// @brief the class which stores the input state associated with the application
    class bEngineInputState
    {
      private:
        /// @brief the state of each key on the keyboard bEngine is interested in
        ///
        /// true indicates the key is pressed, while false means the key is released
        std::unordered_map<bEngineKeyCode, bool> m_keyboardState;

        /// @brief the state of each key/button on the mouse bEngine is interested in
        ///
        /// true indicates the key is pressed, while false means the key is released
        std::unordered_map<bEngineMouseButtonCode, bool> m_mouseButtonsState;

        /// @brief the state of each of the axes associated with the mouse (i.e. x- and y- positions)
        ///
        /// the values are provided as doubles, with the value normalized to the size of the window the mouse position
        /// is in reference to
        std::unordered_map<bEngineMouseAxisCode, double> m_mouseAxesState;

      public:
        /// @brief gets the state associated with the desired bEngineKeyCode
        /// @param keyCode the bEngineKeyCode to get the state of
        /// @return true if the key is down, and false if the key is released
        const bool get_key_state(const bEngineKeyCode keyCode) const;

        /// @brief gets the state associated with the desired bEngineMouseAxisCode
        /// @param mouseAxisCode the bEngineMouseAxisCode to get the state of
        /// @return a value which is normalized based on the size of the window the mouse position is in reference to
        /// for the axis in question
        const double get_mouse_axis_state(const bEngineMouseAxisCode mouseAxisCode) const;

        /// @brief gets the state associated with the desired bEngineMouseButtonCode
        /// @param mouseButtonCode the bEngineMouseButtonCode to get the state of
        /// @return true if the key is down, and false if the key is released
        const bool get_mouse_button_state(const bEngineMouseButtonCode mouseButtonCode) const;

        /// @brief sets the state of the provided bEngineKeyCode
        /// @param keyCode the bEngineKeyCode to set the state for
        /// @param state true if the key state should be 'pressed' or false if the state should be 'released'
        void set_key_state(const bEngineKeyCode keyCode, const bool state);

        /// @brief sets the state of the provided bEngineMouseAxisCode
        /// @param mouseAxisCode the bEngineMouseAxisCode to set the state for
        /// @param state the position of the mouse in the relevant axis (normalized to the size of the window the mouse
        /// position is in reference to)
        void set_mouse_axis_state(const bEngineMouseAxisCode mouseAxisCode, const double state);

        /// @brief sets the state of the provided bEngineMouseButtonCode
        /// @param mouseButtonCode the bEngineMouseButtonCode to set the state for
        /// @param state true if the key state should be 'pressed' or false if the state should be 'released'
        void set_mouse_button_state(const bEngineMouseButtonCode mouseButtonCode, const bool state);
    };
} // namespace bEngine