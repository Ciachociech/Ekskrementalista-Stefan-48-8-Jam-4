#include "input/InputKeyboard.h"

namespace input {

bool InputKeyboard::checkSusCombo(const std::uint8_t* states) { return false; }

bool InputKeyboard::checkDogeCombo(const std::uint8_t* states) { return false; }

InputKeyboard::InputKeyboard() {}

InputKeyboard::~InputKeyboard() {}

std::list<KeyAction> InputKeyboard::interpretSingleAction()
{
    const std::uint8_t* keyboardStates = SDL_GetKeyboardState(NULL);

    std::list<KeyAction> actions;

    if (checkSusCombo(keyboardStates)) {}
    if (checkDogeCombo(keyboardStates)) {}

    if (keyboardStates[defaultInstinctKey - scancodeStdShift]) {
        actions.push_back(KeyAction::useInstinct);
    }
    if (keyboardStates[defaultChangeLanguage - scancodeNumShift]) {
        actions.push_back(KeyAction::changeLanguage);
    }

    //push back empty to prevent errors
    actions.push_back(KeyAction::none);

    return actions;
}

std::list<KeyAction> InputKeyboard::interpretMultipleAction()
{
    const std::uint8_t* keyboardStates = SDL_GetKeyboardState(NULL);

    std::list<KeyAction> actions;

    if (keyboardStates[defaultUpKey - scancodeStdShift] &&
        !keyboardStates[defaultDownKey - scancodeStdShift]) {
        actions.push_back(KeyAction::moveUp);
    } else if (!keyboardStates[defaultUpKey - scancodeStdShift] &&
        keyboardStates[defaultDownKey - scancodeStdShift]) {
        actions.push_back(KeyAction::moveDown);
    }
    if (keyboardStates[defaultLeftKey - scancodeStdShift] &&
        !keyboardStates[defaultRightKey - scancodeStdShift]) {
        actions.push_back(KeyAction::moveLeft);
    } else if (!keyboardStates[defaultLeftKey - scancodeStdShift] &&
        keyboardStates[defaultRightKey - scancodeStdShift]) {
        actions.push_back(KeyAction::moveRight);
    }

    if (keyboardStates[defaultShotKey - scancodeStdShift]) {
        actions.push_back(KeyAction::shootBullet);
    }

    //push back empty to prevent errors
    actions.push_back(KeyAction::none);

    return actions;
}

} // namespace input
