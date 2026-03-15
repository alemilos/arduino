#pragma once
#include <stdint.h>

/**
 The goal of the scheduler is to register tasks and execute them when a 
 specific period of time (specified when the task is added to the Sceduler)
 has passed.

 Usage example:
    Scheduler<10> scheduler;
    scheduler.addTask([]{ sensors.update(millis()); }, 20)
 */

typedef void (*TaskFn)();

template<uint8_t MAX_TASKS>
class Scheduler {
public:
    Scheduler() : _count(0) {}

    bool addTask(TaskFn fn, uint16_t periodMs) {
        if (_count >= MAX_TASKS) return false;
        _tasks[_count].fn       = fn;
        _tasks[_count].periodMs = periodMs;
        _tasks[_count].lastMs   = 0;
        _count++;
        return true;
    }

    // called in the main loop
    void tick(uint32_t nowMs) {
        for (uint8_t i = 0; i < _count; i++) {
            Task& t = _tasks[i];
            if ((nowMs - t.lastMs) >= t.periodMs) {
                t.lastMs = nowMs;
                t.fn();
            }
        }
    }

private:
    struct Task {
        TaskFn   fn;
        uint16_t periodMs;
        uint32_t lastMs;
    };

    Task    _tasks[MAX_TASKS];
    uint8_t _count;
};