/*
    Tasks.h - Task management system for Arduino
    Created by Ethan McTague, March 29, 2019

    Copyright (C) 2019 Ethan McTague
*/
#include "Arduino.h"
#pragma once

class Task;

/* The task manager is a singleton at the core of the Task System.
   It ties into the main loop, calling any added tasks.

   This object need not be interacted with by you, because the Task
   constructor automatically registers the task with the TaskManager.
 */
extern class _TaskManager {
    friend void loop();
    void update ();

    Task** tasks = nullptr;
    int taskCount = 0;

private:
    /* Add a task to the task loop. */
    friend class Task;
    int add(Task* task);

    /* Remove a task from the task loop. */
    void remove(int taskIndex);
} TaskManager;

/* A task that can occur in the task manager.
   All tasks implementing this interface will be automatically registered,
   and have their update method called every loop iteration.
   Implement this interface like so:

   class MyTask : public Task {
   protected:
       void update() override;
   };

   Set the interval like so:
   class MyTask : public Task {
       MyTask()
          : Task(500) <- Set the interval in the constructor initializer list by instantiating base class `Task` with interval param.
       {

       }
   }

   Or:
   class MyTask : public Task {
       void f() {
           setTaskInterval(500);
       }
   }
 */
class Task {
private:
    int taskIndex;
    uint32_t interval;
    uint32_t lastCall;
protected:
    friend class _TaskManager;
    virtual void update() = 0;
    void setTaskInterval(uint32_t);
public:
    Task();
    Task(uint32_t);
    ~Task();
};

/* A task that calls the function pointer given in its
   constructor - created with CallTask::create() and then
   survives until the end of execution. */
class CallTask : public Task {
protected:
    void update() override;

private:
    void (*callback)();
    
    CallTask(void (*callback)());

public:
    static void create(void (*callback)());
};

extern void _loop();
#ifndef _TASKS_INTERNAL
#define loop _loop
#endif