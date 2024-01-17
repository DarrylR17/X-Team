#include "main.h"

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
void autonomous() {}

/**
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
// Declaring Ports
#define MOTOR_LEFT_FRONT 1;
#define MOTOR_LEFT_BACK 2;
#define MOTOR_RIGHT_FRONT 3;
#define MOTOR_RIGHT_BACK 4;
// Placeholder Values
// #define MOTOR_INTAKE_TOP 16;
// #define MOTOR_INTAKE_BOTTOM 17;
// #define MOTOR_CATAPULT 18;
// #define MOTOR_LEFT_EXTENSION 19;
// #define MOTOR_RIGHT_EXTENSION 20;
// Boolean value to track if the extensions are extended
bool extendState = false;
// Function for operator control
void opcontrol() 
{
	// Declaring Motors, Pneumatics if any, and a controller
	pros::Controller master (CONTROLLER_MASTER); 
	pros::Motor left_front (MOTOR_LEFT_FRONT);
	pros::Motor left_back (MOTOR_LEFT_BACK);
	pros::Motor right_front (MOTOR_RIGHT_FRONT);
	pros::Motor right_back (MOTOR_RIGHT_BACK);
	// new stuff
	// pros::Motor intake_top (MOTOR_INTAKE_TOP);
	// pros::Motor intake_bottom (MOTOR_INTAKE_BOTTOM);
	// pros::Motor catapult (MOTOR_CATAPULT);
	// pros::Motor left_extension (MOTOR_LEFT_EXTENSION);
	// pros::Motor right_extension (MOTOR_RIGHT_EXTENSION);

	while (true) 
	{
		// Tank Drive for the Drive Train motors (If you change Y value
		// of left joystick it will change the left side's velocity corresponding
		// to how far up or down you moved it, works the same for the right side)
		left_front.move(master.get_analog(ANALOG_LEFT_Y));
		left_back.move(master.get_analog(ANALOG_LEFT_Y));
		right_front.move(master.get_analog(ANALOG_RIGHT_Y));
		right_back.move(master.get_analog(ANALOG_RIGHT_Y));
		// Intake function which checks if L2(placeholder input) is pressed
		// and if so moves the intake motors
		if(master.get_digital(E_CONTROLLER_DIGITAL_L2))
		{
			// intake
			// Placeholder Value for Voltage
			// intake_top.move(127);
			// Placeholder Value for Voltage
			// intake_bottom.move(127);
			// A message on the central display which tests if the hardware is working
			pros::lcd::set_text(3, "L2 is being pressed :D");
		}
		else
		{
			// stops it from moving
			// intake_top.move(0);
			// intake_bottom.move(0);
			// Clears the line above so it's easier to check if it's working
			pros::lcd::clear_line(3);
		}
		// Catapult function which checks if R2(placeholder input) is pressed
		// and if so moves the catapult motor
		if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
		{
			// Catapult
			// Placeholder Value for Voltage
			// catapult.move(127);
			// A message on the central display which tests if the hardware is working
			pros::lcd::set_text(4, "R2 is being pressed :D");
		}	
		else
		{
			// stops it from moving
			// catapult.move(0);
			// Clears the line above so it's easier to check if it's working
			pros::lcd::clear_line(4);
		}
		// Extension function which checks if Y(placeholder input) is pressed
		// and if so retracts/extends the extension
		if(master.get_digital(E_CONTROLLER_DIGITAL_Y))
		{
			// A message on the central display which tests if the hardware is working
			pros::lcd::set_text(5, "Y is being pressed :D");
			// There is a possibility in which instead of using move_absolute(motor encoder value, voltage)
			// we can use move_relative which is similar to move_absolute, however uses relative movement
			// Checks whether or not the extensions or extended or not if so retracts, if not extends
			if (extendState)
			{
				/**
				* Retracts
				* left_extension.move_absolute(Input Double Value corresponding to retract, velocity from -127 to 127)
				* right_extension.move_absolute(Input Double Value corresponding to retract, velocity from -127 to 127)
				*/
			}
			else
			{
				/**
				* Extends
				* left_extension.move_absolute(Input Double Value corresponding to extend, velocity from -127 to 127)
				* right_extension.move_absolute(Input Double Value corresponding to extend, velocity from -127 to 127)
				*/
			}
			extendState = !extendState;
		}
		else
		{
			// Clears the line above so it's easier to check if it's working
			pros::lcd::clear_line(5);
		}
	// Delay for the program	
	pros::delay(20);
	}
}
