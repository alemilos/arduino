#include <Arduino.h>
#include "config/Config.h"
#include "data/SimulatedDataSource.h"
#include "display/DisplayManager.h"
#include "input/InputManager.h"
#include "scheduler/Scheduler.h"


// ── Global Objects (static storage, no heap) ────────
static SimulatedDataSource simSource;
// static RealDataSource      realSource(Serial1); // enable if real data is reachable
static IDataSource*        dataSource = &simSource;  // swap here to &realSource when available 

static DisplayManager displayMgr;
static InputManager   inputMgr;
static Scheduler<6>   scheduler;

static void taskSensors()  { dataSource->update(millis()); }
static void taskInput()    { inputMgr.update(millis()); }
static void taskDisplay()  { displayMgr.update(dataSource->getData()); }

// static void taskLogic() {
    // // Change screen handling (not required yet)
    // if (inputMgr.wasPressed(ButtonID::MODE)) {
    //     static uint8_t screen = 0;
    //     screen = (screen + 1) % 3;
    //     displayMgr.setScreen(screen);
    // }

    // // Not necessary to swap at runtime (but in any case...)
    // if (inputMgr.wasPressed(ButtonID::SELECT)) {
    //     // Swap sorgente dati a runtime
    //     if (dataSource == &simSource) dataSource = &realSource;
    //     else                            dataSource = &simSource;
    // }
// }

void setup() {
    Serial.begin(SERIAL_BAUD_DEBUG);
    Serial1.begin(SERIAL_BAUD_ECU);

    displayMgr.begin();

    scheduler.addTask(taskSensors,   TASK_PERIOD_SENSORS_MS);
    // scheduler.addTask(taskInput,     TASK_PERIOD_INPUT_MS);
    scheduler.addTask(taskDisplay,   TASK_PERIOD_DISPLAY_MS);
    // scheduler.addTask(taskLogic,     TASK_PERIOD_INPUT_MS);
    // scheduler.addTask(taskSerialLog, TASK_PERIOD_SERIAL_LOG_MS);
}

void loop() {
    scheduler.tick(millis());
}