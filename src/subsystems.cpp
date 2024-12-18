// drivetrain ports
#include "main.h" // IWYU pragma: keep

pros::MotorGroup left_motors({-15, -19, 18}); // left motors on ports 1, 2, 3
pros::MotorGroup right_motors({17, 16, -20}); // right motors on ports 4, 5, 6

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motors,               // left motor group
                              &right_motors,              // right motor group
                              11.25,                      // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2    // horizontal drift is 2 (for now)
);

pros::Imu imu(10);

lemlib::OdomSensors sensors(
    nullptr, // vertical tracking wheel 1, set to null
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a
             // second one
    &imu  // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings
    lateral_controller(20,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       6,   // derivative gain (kD)
                       3,   // anti windup
                       0.5,   // small error range, in inches
                       50, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       800, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );
// angular PID controller
lemlib::ControllerSettings
    angular_controller(2,   // proportional gain (kP)
                       0,   // integral gain (kI)
                       10,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );

// create drive curve settings
lemlib::ExpoDriveCurve drive_curve(3, 10, 1);

// create turn curve settings
lemlib::ExpoDriveCurve turn_curve(3, 10, 1);

// create the chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors, &drive_curve, &turn_curve);

// intake
pros::Motor intake(7, pros::v5::MotorGears::blue,
                        pros::v5::MotorEncoderUnits::deg);


// hook
pros::Motor hook(-8, pros::v5::MotorGears::blue,
                        pros::v5::MotorEncoderUnits::deg);

// mogo
pros::adi::DigitalOut mogo(1, LOW);
int mogo_state = LOW;
