#include "PushButton.h"

PushButton::PushButton(uint32_t pin, bool isPullUp,
                       bool internalPullUpActivated)
{
    this->pin = pin;
    this->isPullUp = isPullUp;
    this->internalPullUpActivated = internalPullUpActivated;

    lastTimeStateChanged = millis();
    debounceDelay = 50;
}

void PushButton::init()
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    if (isPullUp && internalPullUpActivated)
    {
        gpio_pull_up(pin);
    }
    state= gpio_get(pin);
}

void PushButton::readState()
{
    unsigned long timeNow = millis();
    if (timeNow - lastTimeStateChanged > debounceDelay) {
        uint32_t newState = gpio_get(pin);
        if (newState != state) {
            state = newState;
            lastTimeStateChanged = timeNow;
        }
    }
}

bool PushButton::isPressed()
{
    readState();
    if (isPullUp) {
        return (state == 0);
    }
    else {
        return (state == 1);
    }
}