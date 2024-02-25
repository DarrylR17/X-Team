#include "main.h"
#include "auton_functions.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

#define MOTOR_LEFT_FRONT 3
#define MOTOR_LEFT_BACK 2
#define MOTOR_LEFT_TOP 1

#define MOTOR_RIGHT_FRONT 11
#define MOTOR_RIGHT_BACK 12
#define MOTOR_RIGHT_TOP 13

#define INTAKE 7
#define DIGITAL_SENSOR_PORT 'A'

void offense_autonomous() {
	drive_forward(100, 200); //add parameters later
	drop();
	drive_backward(100, 200); //add parameters later
	drive_forward(100, 200); //add parameters later
	drive_backward(100, 200); //add parameters later
	turn_right(200, 1000); //add parameters later
	drive_forward(100, 200); //add parameters later
	grab();
	turn_left(200, 1000); //add parameters later
	drive_forward(100, 200); //add parameters later
	drop();
}

void defense_autonomous() {
	drive_forward(100, 200); //add parameters later
	drop();
	drive_backward(100, 200); //add parameters later
	drive_forward(100, 200); //add parameters later
	drive_backward(100, 200); //add parameters later
	turn_left(200, 1000); //add parameters later
	drive_forward(100, 200); //add parameters later
	grab();
	drive_backward(100, 200); //add parameters later
	turn_right(200, 1000); //add parameters later
	drive_forward(100, 200); //add parameters later
	drop();
}






/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1,-2,3}); // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4,5,-6}); // Creates a motor group with forwards port 4 and reversed ports 4 & 6

	while (true) {
		if(master.get_digital(DIGITAL_R2)) {
			defense_autonomous();
		}
	}
}