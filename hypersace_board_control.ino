
#include "spaceship_commands.ino"

void setup()
{
    spaceship_setup();
}

void loop()
{
    handleHyperspaceOverheat();

    if (digitalRead(LAUNCH_PIN) == HIGH)
    {
        if (hyperspaceReady() && !isHyperspace())
        {
            startHyperspace();
        }
        else if (isHyperspace())
        {
            stopHyperspace();
        }
    }
}
