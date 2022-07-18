#include <Tasks.h>

class SensorPolling : public Task {
private:
    uint16_t lastReading;
    const uint8_t pin;

    void update()
    {
        lastReading = analogRead(pin);
    }
public:
    SensorPolling(uint8_t pin , uint16_t pollingInterval) : Task(pollingInterval), pin(pin) {

    }

    SensorPolling(uint8_t pin) : SensorPolling(pin, 0) {

    }

    uint16_t get()
    {
        return lastReading;
    }
};

SensorPolling potentiometer = SensorPolling(A0, 20); //Important! quick updates.
SensorPolling mySensor = SensorPolling(A1, 120); //Less important.

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print("potentiometer: ");
    Serial.print(potentiometer.get());
    Serial.print(", mySensor: ");
    Serial.println(mySensor.get());
}