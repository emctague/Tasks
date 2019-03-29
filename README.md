# Tasks

This is an Arduino library that implements task management,
hooking into the global `loop` function to automatically call
any registered tasks.

Tasks are automatically registered when initialized, and
automatically de-registered when destroyed.

The main benefit of the Task system is that individual objects
that need to be updated constantly (e.g. those that watch pin values)
can avoid forcing the developer to call an `update()` method each iteration.
Rather, they can simply make their object extend `Task`.

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

void otherTask () {
    Serial.println("Function task!");
}

void setup () {
    Serial.begin(9600);
    CallTask::create([]() -> void { Serial.println("Lambda Task!"); });
    CallTask::create(otherTask);
}

void loop () {

}

// Output:
// Lambda Task!
// Function Task!
// Lambda Task!
// Function Task!
// ...
```