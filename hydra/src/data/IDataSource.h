#pragma once
#include "VehicleData.h"

// Pure interface 

class IDataSource {
public:
    virtual ~IDataSource() {}

    // Called by the scheduler every TASK_PERIOD_SENSORS_MS
    // NON blocking: read, leave.
    virtual void update(uint32_t nowMs) = 0;

    // Current snapshot. Returns reference const: no copy
    virtual const VehicleData& getData() const = 0;

    virtual const char* getSourceName() const = 0; 
};