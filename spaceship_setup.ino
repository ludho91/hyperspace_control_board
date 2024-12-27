const uint8_t HYPERSPACE_PIN = 3;
const uint8_t HYPERSPACE_READY_PIN = 4;
const uint8_t HYPERSPACE_OVERHEATED = 5;
const uint8_t LAUNCH_PIN = 2;

void spaceship_setup()
{
    pinMode(HYPERSPACE_PIN, OUTPUT);
    pinMode(HYPERSPACE_READY_PIN, OUTPUT);
    pinMode(HYPERSPACE_OVERHEATED, OUTPUT);
    pinMode(LAUNCH_PIN, INPUT);
}