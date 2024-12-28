#include <stdio.h>

const uint8_t HYPERSPACE_PIN = 3;
const uint8_t HYPERSPACE_READY_PIN = 4;
const uint8_t HYPERSPACE_ALERT_LED = 5;
const uint8_t LAUNCH_PIN = 2;
const int TEMPERATURE_PIN = A0;

const uint16_t HYPERSPACE_LOADING_TIME = 1000;        // 5 seconds
const uint16_t HYPERSPACE_TEMPERATURE_ALERT = 25;     // 25 degree
const uint16_t HYPERSPACE_TEMPERATURE_SAFE_MODE = 40; // 40 degree
const uint16_t HYPERSPACE_ALERT_INTERVAL = 50;        // 50ms

const uint16_t READ_TEMP_INTERVAL = 2000; // 1 second

boolean override_save_mode = false;
uint8_t lastLaunchButtonState;
boolean hyperspaceOverheatedState = false;
unsigned long lastTemperatureReadMillis = 0;
unsigned long lastAlertMillis = 0;

#pragma region states

boolean hyperspaceAlertLedOn()
{
    return digitalRead(HYPERSPACE_ALERT_LED) == HIGH;
}

float getTemperature()
{
    float voltage = analogRead(TEMPERATURE_PIN) / 1024.0 * 5.0;
    return (voltage - 0.5) * 100;
}

boolean launchButtonPressed()
{
    return digitalRead(LAUNCH_PIN) == HIGH;
}

boolean hyperspaceReady()
{
    return digitalRead(HYPERSPACE_READY_PIN) == HIGH;
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
    if (hyperspaceOverheatedState)
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
    Serial.begin(9600);
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
    pinMode(HYPERSPACE_ALERT_LED, OUTPUT);
    pinMode(LAUNCH_PIN, INPUT);

    check_module(HYPERSPACE_PIN);
    check_module(HYPERSPACE_READY_PIN);
    check_module(HYPERSPACE_ALERT_LED);
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

    monitorTemperature();
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

void monitorTemperature()
{
    if (millis() - lastTemperatureReadMillis > READ_TEMP_INTERVAL)
    {
        lastTemperatureReadMillis = millis();
        Serial.println("Temperature: " + String(getTemperature()));
    }
}

void hyperspaceMonitoring()
{

    handleAlertLed();

    handleHyperspaceOverheat();
}
void handleAlertLed()
{

    if (getTemperature() > HYPERSPACE_TEMPERATURE_ALERT && getTemperature() < HYPERSPACE_TEMPERATURE_SAFE_MODE)
    {
        if (millis() - lastAlertMillis > HYPERSPACE_ALERT_INTERVAL)
        {
            lastAlertMillis = millis();
            digitalWrite(HYPERSPACE_ALERT_LED, !hyperspaceAlertLedOn());
        }
    }

    else if (getTemperature() > HYPERSPACE_TEMPERATURE_SAFE_MODE)
    {
        digitalWrite(HYPERSPACE_ALERT_LED, HIGH);
        hyperspaceOverheatedState = true;
    }
    else
    {
        digitalWrite(HYPERSPACE_ALERT_LED, LOW);
    }
}