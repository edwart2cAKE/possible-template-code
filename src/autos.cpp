#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"
#include "subsystems.h"

void pid_lateral_test() {
    chassis.setPose(0, 0, 90);
    chassis.moveToPoint(10, 0, 1000);
    chassis.moveToPoint(0, 0, 1000, {.forwards = false});
    chassis.moveToPoint(20, 0, 1700);
    chassis.moveToPoint(0, 0, 1700, {.forwards = false});
    chassis.moveToPoint(30, 0, 2000);
    chassis.moveToPoint(0, 0, 2000, {.forwards = false});
}

void pid_angular_test() {
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 1000);
}

void pid_suite_test() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(10, 0, 1000);
    chassis.turnToPoint(10, 10, 1000);
    chassis.moveToPoint(10, 10, 1000);
    chassis.turnToPoint(0, 10, 1000);
    chassis.moveToPoint(0, 10, 1000);
    chassis.turnToPoint(0, 0, 1000);
    chassis.moveToPoint(0, 0, 1000);
}

void left_side() {
    // start pos
    chassis.setPose(-57,20,0);
    
    // move to wall stake
    chassis.moveToPoint(-57, 0, 1500, {.forwards = false});
    chassis.turnToHeading(90, 1500);
    chassis.waitUntilDone();
    chassis.tank(-50,-50);
    pros::delay(400);
    chassis.tank(0,0);
    chassis.turnToHeading(90, 300);
    chassis.waitUntilDone();

    // score
    int ms_running = 0;
    hook.move(127);
    pros::delay(500);
    hook.move(0);

    // go to mogo
    chassis.turnToPoint(-56, 8, 2000);
    chassis.moveToPoint(-56, 8, 2000);
    mogo.set_value(true);

    chassis.turnToPoint(-32.29, 19.452, 2000, {.forwards = false});
    chassis.moveToPoint(-32.29, 19.452, 2000, {.forwards = false});
    chassis.waitUntilDone();

    mogo.set_value(false); // */
}