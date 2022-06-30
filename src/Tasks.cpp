/*
    Tasks.cpp - Task management system for Arduino
    Created by Ethan McTague, March 29, 2019

    Copyright (C) 2019 Ethan McTague
*/
#define _TASKS_INTERNAL
#include "Tasks.h"

_TaskManager TaskManager;

int _TaskManager::add(Task* task) {
    tasks = (Task**)realloc(tasks, ++taskCount * sizeof(Task*));
    tasks[taskCount - 1] = task;
    return taskCount - 1;
}

void _TaskManager::remove(int taskIndex) {
    tasks[taskCount - 1]->taskIndex = taskIndex;
    tasks[taskIndex] = tasks[taskCount - 1];
    tasks = (Task**)realloc(tasks, --taskCount * sizeof(Task*));
}

Task::Task() : Task(0)
{
}

Task::Task(uint32_t interval) : interval(interval), lastCall(0)
{
    taskIndex = TaskManager.add(this);
}

Task::~Task() {
    TaskManager.remove(taskIndex);
}

void Task::setTaskInterval(uint32_t newInterval) {
    interval = newInterval;
}

void _TaskManager::update() {
    for (int i = 0; i < taskCount; i++) {
        if (millis() - tasks[i]->lastCall >= tasks[i]->interval) {
            tasks[i]->lastCall = millis();
            tasks[i]->update();
        }
    }
}

CallTask::CallTask(void (*callback)()) : callback(callback)
{

}

void CallTask::update ()
{
    callback();
}

void CallTask::create (void (*callback)()) {
    if (callback != nullptr)
        new CallTask(callback);
}

void loop ()
{
    TaskManager.update();
    _loop();
}
