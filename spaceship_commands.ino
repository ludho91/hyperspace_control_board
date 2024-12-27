/**
 * @brief Spaceship commands
 */

#include "spaceship_setup.ino"
#include "spaceship_states.ino"
void startHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, HIGH);
}

void stopHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, LOW);
}

void handleHyperspaceOverheat()
{
    if (hyperspaceOverheated())
    {
        stopHyperspace();
    }
}
