#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineInput.h"

/// @file bEngineInput.cpp
/// @brief implementations for the bEngineInput.h file

/// @brief an anonymous namespace to store some data
namespace
{
    /// @brief "human readable" names (really 'debug names') for each of the bEngineKeyCode values
    const std::unordered_map<bEngine::bEngineKeyCode, std::string> g_keyCodeNames{
        {            bEngine::bEngineKeyCode::key_1,         "1"},
        {            bEngine::bEngineKeyCode::key_2,         "2"},
        {            bEngine::bEngineKeyCode::key_3,         "3"},
        {            bEngine::bEngineKeyCode::key_4,         "4"},
        {            bEngine::bEngineKeyCode::key_5,         "5"},
        {            bEngine::bEngineKeyCode::key_6,         "6"},
        {            bEngine::bEngineKeyCode::key_7,         "7"},
        {            bEngine::bEngineKeyCode::key_8,         "8"},
        {            bEngine::bEngineKeyCode::key_9,         "9"},
        {            bEngine::bEngineKeyCode::key_0,         "0"},
        {            bEngine::bEngineKeyCode::key_a,         "A"},
        {            bEngine::bEngineKeyCode::key_b,         "B"},
        {            bEngine::bEngineKeyCode::key_c,         "C"},
        {            bEngine::bEngineKeyCode::key_d,         "D"},
        {            bEngine::bEngineKeyCode::key_e,         "E"},
        {            bEngine::bEngineKeyCode::key_f,         "F"},
        {            bEngine::bEngineKeyCode::key_g,         "G"},
        {            bEngine::bEngineKeyCode::key_h,         "H"},
        {            bEngine::bEngineKeyCode::key_i,         "I"},
        {            bEngine::bEngineKeyCode::key_j,         "J"},
        {            bEngine::bEngineKeyCode::key_k,         "K"},
        {            bEngine::bEngineKeyCode::key_l,         "L"},
        {            bEngine::bEngineKeyCode::key_m,         "M"},
        {            bEngine::bEngineKeyCode::key_n,         "N"},
        {            bEngine::bEngineKeyCode::key_o,         "O"},
        {            bEngine::bEngineKeyCode::key_p,         "P"},
        {            bEngine::bEngineKeyCode::key_q,         "Q"},
        {            bEngine::bEngineKeyCode::key_r,         "R"},
        {            bEngine::bEngineKeyCode::key_s,         "S"},
        {            bEngine::bEngineKeyCode::key_t,         "T"},
        {            bEngine::bEngineKeyCode::key_u,         "U"},
        {            bEngine::bEngineKeyCode::key_v,         "V"},
        {            bEngine::bEngineKeyCode::key_w,         "W"},
        {            bEngine::bEngineKeyCode::key_x,         "X"},
        {            bEngine::bEngineKeyCode::key_y,         "Y"},
        {            bEngine::bEngineKeyCode::key_z,         "Z"},
        {     bEngine::bEngineKeyCode::key_arrow_up,        "UP"},
        {  bEngine::bEngineKeyCode::key_arrow_right,     "RIGHT"},
        {   bEngine::bEngineKeyCode::key_arrow_down,      "DOWN"},
        {   bEngine::bEngineKeyCode::key_arrow_left,      "LEFT"},
        {       bEngine::bEngineKeyCode::key_escape,    "ESCAPE"},
        {    bEngine::bEngineKeyCode::key_backspace, "BACKSPACE"},
        {          bEngine::bEngineKeyCode::key_tab,       "TAB"},
        {    bEngine::bEngineKeyCode::key_caps_lock,  "CAPSLOCK"},
        {        bEngine::bEngineKeyCode::key_enter,     "ENTER"},
        {   bEngine::bEngineKeyCode::key_shift_left,   "L SHIFT"},
        {  bEngine::bEngineKeyCode::key_shift_right,   "R SHIFT"},
        { bEngine::bEngineKeyCode::key_control_left,    "L CTRL"},
        {     bEngine::bEngineKeyCode::key_alt_left,     "L ALT"},
        {        bEngine::bEngineKeyCode::key_space,     "SPACE"},
        {    bEngine::bEngineKeyCode::key_alt_right,     "R ALT"},
        {bEngine::bEngineKeyCode::key_control_right,    "R CTRL"},
    };

    /// @brief "human readable" names (really 'debug names') for each of the bEngineMouseButtonCode values
    const std::unordered_map<bEngine::bEngineMouseButtonCode, std::string> g_mouseButtonCodeNames{
        { bEngine::bEngineMouseButtonCode::mouse_left, "L MOUSE"},
        {  bEngine::bEngineMouseButtonCode::mouse_mid, "M MOUSE"},
        {bEngine::bEngineMouseButtonCode::mouse_right, "R MOUSE"},
    };

    /// @brief "human readable" names (really 'debug names') for each of the bEngineMouseAxisCode values
    const std::unordered_map<bEngine::bEngineMouseAxisCode, std::string> g_mouseAxisCodeNames{
        {bEngine::bEngineMouseAxisCode::mouse_x, "MOUSE X"},
        {bEngine::bEngineMouseAxisCode::mouse_y, "MOUSE Y"},
    };
} // namespace

const bool bEngine::bEngineInputState::get_key_state(const bEngineKeyCode keyCode) const
{
    if (m_keyboardState.contains(keyCode))
    {
        return m_keyboardState.at(keyCode);
    }

    return false;
}

const double bEngine::bEngineInputState::get_mouse_axis_state(const bEngineMouseAxisCode mouseAxisCode) const
{
    if (m_mouseAxesState.contains(mouseAxisCode))
    {
        return m_mouseAxesState.at(mouseAxisCode);
    }

    return 0.0;
}

const bool bEngine::bEngineInputState::get_mouse_button_state(const bEngineMouseButtonCode mouseButtonCode) const
{
    if (m_mouseButtonsState.contains(mouseButtonCode))
    {
        return m_mouseButtonsState.at(mouseButtonCode);
    }

    return false;
}

void bEngine::bEngineInputState::set_key_state(const bEngineKeyCode keyCode, const bool state)
{
    m_keyboardState.insert_or_assign(keyCode, state);
}

void bEngine::bEngineInputState::set_mouse_axis_state(const bEngineMouseAxisCode mouseAxisCode, const double state)
{
    m_mouseAxesState.insert_or_assign(mouseAxisCode, state);
}

void bEngine::bEngineInputState::set_mouse_button_state(const bEngineMouseButtonCode mouseButtonCode, const bool state)
{
    m_mouseButtonsState.insert_or_assign(mouseButtonCode, state);
}

const std::string bEngine::Input::get_keycode_name(const bEngineKeyCode keyCode)
{
    if (g_keyCodeNames.contains(keyCode))
    {
        return g_keyCodeNames.at(keyCode);
    }

    return "UNKNOWN";
}

const std::string bEngine::Input::get_mouse_button_code_name(const bEngineMouseButtonCode mouseButtonCode)
{
    if (g_mouseButtonCodeNames.contains(mouseButtonCode))
    {
        return g_mouseButtonCodeNames.at(mouseButtonCode);
    }

    return "UNKNOWN";
}

const std::string bEngine::Input::get_mouse_axis_code_name(const bEngineMouseAxisCode mouseAxisCode)
{
    if (g_mouseAxisCodeNames.contains(mouseAxisCode))
    {
        return g_mouseAxisCodeNames.at(mouseAxisCode);
    }

    return "UNKNOWN";
}
