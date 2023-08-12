#ifndef INPUT_INPUTKEYBOARD_H_
#define INPUT_INPUTKEYBOARD_H_

#include <cstdint>
#include <list>

#include <SDL.h>

namespace input {

enum class KeyAction {
    none = 0,
    moveUp = 1,
    moveDown,
    moveLeft,
    moveRight,
    shootBullet,
    useInstinct
};

const SDL_Keycode defaultUpKey = SDLK_w;
const SDL_Keycode defaultDownKey = SDLK_s;
const SDL_Keycode defaultLeftKey = SDLK_a;
const SDL_Keycode defaultRightKey = SDLK_d;
const SDL_Keycode defaultShotKey = SDLK_k;
const SDL_Keycode defaultInstinctKey = SDLK_l;

namespace {
    constexpr std::uint8_t scancodeShift = 93;
}

class InputKeyboard {
private:
    std::uint8_t susComboProgress_;
    std::uint8_t dogeComboProgress_;

    bool checkSusCombo(const std::uint8_t* states);
    bool checkDogeCombo(const std::uint8_t* states);

public:
    InputKeyboard();
    virtual ~InputKeyboard();

    std::list<KeyAction> interpretSingleAction();
    std::list<KeyAction> interpretMultipleAction();
};

} // namespace input

#endif // !INPUT_INPUTKEYBOARD_H_
