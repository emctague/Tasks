#include <Tasks.h>

class MyTask : public Task {
//               ^
// Specifier doesn't really matter.

    void update() {
        Serial.println("Task Called.");
    }
};

MyTask myTask; // Create task.

void setup () {
    Serial.begin(9600);
}

void loop() {

}