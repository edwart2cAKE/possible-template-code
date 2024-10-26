#include "main.h"
#include "subsystems.h"

void some_auto() {
    chassis.setPose(0,0,0);

    chassis.moveToPoint(10, 10, 1000);
}