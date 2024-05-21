#include "Button.hpp"
#include <raylib.h>
#include <stdio.h>
#include "FocusStack.hpp"

void TextButton::Draw() {
    // TODO: use MeasureTextEx to also get height
    int w = MeasureText(this->text.c_str(), 24);
    auto focused = FocusStack::IsFocused(this);

    int rx = this->x - w - 5;
    int ry = this->y - 5;
    int rw = w + 10;
    int rh = 24 + 5 + 5;

        DrawRectangle(rx, ry, rw, rh, focused ? LIGHTBLUE : DARKBLUE);

    DrawText (
        this->text.c_str(),
        this->x - w,
        this->y,
        24,
        focused ? WHITE : GRAY
    ); 
}

int TextButton::Update() {
    int val;
    val = UiElement::Update();
    if (val)
        return val;

    if (FocusStack::IsNotFocused(this))
        return 0;

    if (IsKeyPressed(KEY_Z) && cb_onPress) {
        auto val = cb_onPress();
        if (val)
            return val;
    }   
    return val;
}

TextButton::TextButton(int x, int y, std::string text){
    this->x = x;
    this->y = y;
    this->text = text;
}

TextButton::TextButton(int x, int y, std::string text, int (*onPress)()){
    this->x = x;
    this->y = y;
    this->text = text;
    this->cb_onPress = onPress;
}
