#pragma once
#include "data/VehicleData.h"

// Interfaccia pura per tutti gli schermi.
// DisplayManager possiede un puntatore IScreen* e chiama questi metodi.
// Ogni screen sa come disegnarsi — DisplayManager non conosce i dettagli.
//
// Contratto:
//   drawFull()   → ridisegna tutto (chiamato una volta al mount)
//   update()     → ridisegna solo i valori cambiati (chiamato ogni tick)
//   onEnter()    → hook quando lo schermo diventa attivo
//   onExit()     → hook quando lo schermo viene abbandonato

class IScreen {
public:
    virtual ~IScreen() {}
    virtual void drawFull(const VehicleData& data) = 0;
    virtual void update  (const VehicleData& data) = 0;
    virtual void onEnter () {}   // default no-op
    virtual void onExit  () {}   // default no-op
    virtual const char* getName() const = 0;
};