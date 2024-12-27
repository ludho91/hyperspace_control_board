#include "spaceship_setup.ino";
/**
 * @brief Hyperspace states
 */

bool hyperspaceReady()
{
    return digitalRead(HYPERSPACE_READY_PIN) == HIGH;
}

bool hyperspaceOverheated()
{
    return digitalRead(HYPERSPACE_OVERHEATED) == HIGH;
}

bool isHyperspace()
{
    return digitalRead(HYPERSPACE_PIN) == HIGH;
}
