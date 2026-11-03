#pragma once
#include <iostream>

class TouchControls {
public:
    bool forwardPressed = false;
    bool backwardPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
    bool jumpPressed = false;

    // Перевірка, чи палець торкнувся віртуальної кнопки на екрані телефону
    void handleTouch(float touchX, float touchY, int screenWidth, int screenHeight, bool isDown) {
        // Проста зона лівого джойстика/кнопок ходьби у лівому нижньому кутку
        if (touchX < screenWidth * 0.3f && touchY > screenHeight * 0.6f) {
            forwardPressed = isDown;
        }
        // Зона правого нижнього кутка — стстрибок / дія
        if (touchX > screenWidth * 0.7f && touchY > screenHeight * 0.6f) {
            jumpPressed = isDown;
        }
    }

    void reset() {
        forwardPressed = false;
        backwardPressed = false;
        leftPressed = false;
        rightPressed = false;
        jumpPressed = false;
    }
};
