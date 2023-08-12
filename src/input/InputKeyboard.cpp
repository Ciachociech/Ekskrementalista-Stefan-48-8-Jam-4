#include "input/InputKeyboard.h"

namespace input {

bool InputKeyboard::checkSusCombo(const std::uint8_t* states) { return false; }

bool InputKeyboard::checkDogeCombo(const std::uint8_t* states) { return false; }

InputKeyboard::InputKeyboard() {}

InputKeyboard::~InputKeyboard() {}

std::list<KeyAction> InputKeyboard::interpretAction() {
    const std::uint8_t* keyboardStates = SDL_GetKeyboardState(NULL);

    std::list<KeyAction> actions;

    if (checkSusCombo(keyboardStates)) {}
    if (checkDogeCombo(keyboardStates)) {}

    if (keyboardStates[defaultUpKey - scancodeShift] &&
        !keyboardStates[defaultDownKey - scancodeShift]) {
        actions.push_back(KeyAction::moveUp);
    } else if (!keyboardStates[defaultUpKey - scancodeShift] &&
               keyboardStates[defaultDownKey - scancodeShift]) {
        actions.push_back(KeyAction::moveDown);
    }
    if (keyboardStates[defaultLeftKey - scancodeShift] &&
        !keyboardStates[defaultRightKey - scancodeShift]) {
        actions.push_back(KeyAction::moveLeft);
    } else if (!keyboardStates[defaultLeftKey - scancodeShift] &&
               keyboardStates[defaultRightKey - scancodeShift]) {
        actions.push_back(KeyAction::moveRight);
    }

    if (keyboardStates[defaultShotKey - scancodeShift]) {
        actions.push_back(KeyAction::shootBullet);
    }
    if (keyboardStates[defaultInstinctKey - scancodeShift]) {
        actions.push_back(KeyAction::useInstinct);
    }

    //push back empty to prevent errors
    actions.push_back(KeyAction::none);

    return actions;
}

} // namespace input
