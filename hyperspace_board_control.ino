
const uint8_t HYPERSPACE_PIN = 3;
const uint8_t HYPERSPACE_READY_PIN = 4;
const uint8_t HYPERSPACE_OVERHEATED = 5;
const uint8_t LAUNCH_PIN = 2;

const uint16_t HYPERSPACE_LOADING_TIME = 1000;                 // 5 seconds
const uint16_t HYPERSPACE_MAX_USING_BEFORE_OVERHEATED = 20000; // 5 seconds

uint8_t lastLaunchButtonState;

#pragma region states

boolean launchButtonPressed()
{
    return digitalRead(LAUNCH_PIN) == HIGH;
}

boolean hyperspaceReady()
{
    return digitalRead(HYPERSPACE_READY_PIN) == HIGH;
}

boolean hyperspaceOverheated()
{
    return digitalRead(HYPERSPACE_OVERHEATED) == HIGH;
}

boolean isHyperspace()
{
    return digitalRead(HYPERSPACE_PIN) == HIGH;
}

#pragma endregion

#pragma region commands
void startHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, HIGH);
    digitalWrite(HYPERSPACE_READY_PIN, LOW);
}

void stopHyperspace()
{
    digitalWrite(HYPERSPACE_PIN, LOW);
    loadHyperspace();
}

void handleHyperspaceOverheat()
{
    if (hyperspaceOverheated())
    {
        stopHyperspace();
    }
}

void loadHyperspace()
{

    delay(HYPERSPACE_LOADING_TIME);
    digitalWrite(HYPERSPACE_READY_PIN, HIGH);
}
#pragma endregion

void setup()
{
    spaceship_setup();
}

void loop()
{
    spaceship_loop();
}
void spaceship_setup()
{
    pinMode(HYPERSPACE_PIN, OUTPUT);
    pinMode(HYPERSPACE_READY_PIN, OUTPUT);
    pinMode(HYPERSPACE_OVERHEATED, OUTPUT);
    pinMode(LAUNCH_PIN, INPUT);

    check_module(HYPERSPACE_PIN);
    check_module(HYPERSPACE_READY_PIN);
    check_module(HYPERSPACE_OVERHEATED);
    lastLaunchButtonState = launchButtonPressed();
    loadHyperspace();
}

void check_module(uint8_t module)
{
    digitalWrite(module, HIGH);
    delay(1000);
    digitalWrite(module, LOW);
}

void spaceship_loop()
{

    hyperspaceMonitoring();

    if (launchButtonPressed() != lastLaunchButtonState && launchButtonPressed())
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

    lastLaunchButtonState = launchButtonPressed();
}

void hyperspaceMonitoring()
{

    handleHyperspaceOverheat();
}