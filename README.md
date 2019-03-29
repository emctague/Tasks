# Tasks

This is an Arduino library that implements task management,
hooking into the global `loop` function to automatically call
any registered tasks.

Tasks are automatically registered when initialized, and
automatically de-registered when destroyed.

## Usage

```cpp
#include "Tasks.h"

class MyTask : public Task {
protected:
    void update() override {
        Serial.println("Task Updated!");
    }
}

MyTask aTask;

void setup () {
    Serial.begin(9600);
}

void loop () {
    Serial.println("Loop Called!");
}

// Output:
// Task Updated!
// Loop Called!
// Task Updated!
// Loop Called!
// ...
```

### CallTask

CallTask is a simple Task type that can be created using
`CallTask::create()`. It takes in a lambda or function pointer
with no arguments, which should return void.

After creation, a CallTask will exist behind-the-scenes for
the entire lifetime of the program.

```cpp
#include "Tasks.h"

void setup () {
    CallTask::create([]() -> void { Serial.println("Hello!"); });
}

void loop () {

}

// Output:
// Hello!
// Hello!
// ...
```