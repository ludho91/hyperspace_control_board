
const uint8_t HYPERSPACE_PIN = 3;
const uint8_t HYPERSPACE_READY_PIN = 4;
const uint8_t HYPERSPACE_OVERHEATED = 5;
const uint8_t LAUNCH_PIN = 2;

void setup()
{
    if (hyperspaceOverheated())
    {
        stopHyperspace();
    }
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
    delay(200);                      // Wait for 1 second
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
    delay(100);
}

void launch()
{
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
    delay(200);                      // Wait for 1 second
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
    delay(100);
}

/** /
** @brief Hyperspace states
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

/**
 *Hyperspace controls
 */

void startHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, HIGH);
}

void stopHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, LOW);
}