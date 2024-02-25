#include "main.h"

void drive_forward(double distance, int speed) {
	pros::MotorGroup f_left_mg({3,2,-1});
	pros::MotorGroup f_right_mg({11,12,-13});

	double f_average_position = (f_left_mg.get_position() + f_right_mg.get_position()) / 2.0;

	f_left_mg.move_relative(distance, speed);
	f_right_mg.move_relative(distance, speed);

	while (!((f_average_position < distance + 3) && (f_average_position > distance - 3))) {
		pros::delay(5);
	}
}

void drive_backward(double distance, int speed) {
	pros::MotorGroup b_left_mg({-3,-2,1});
	pros::MotorGroup b_right_mg({-11,-12,13});

	double b_average_position = (b_left_mg.get_position() + b_right_mg.get_position()) / 2.0;

	b_left_mg.move_relative(distance, speed);
	b_right_mg.move_relative(distance, speed);

	while (!((b_average_position < distance + 3) && (b_average_position > distance - 3))) {
		pros::delay(5);
	}
}

void turn_right(int velocity, int milliseconds) {
	pros::MotorGroup left_mg({3,2,-1});

	left_mg.move_velocity(velocity);
	pros::delay(milliseconds);
	left_mg.move_velocity(0);
}

void turn_left(int velocity, int milliseconds) {
	pros::MotorGroup right_mg({11,12,-13});

	right_mg.move_velocity(velocity);
	pros::delay(milliseconds);
	right_mg.move_velocity(0);
}

void open_wings() {
	pros::ADIDigitalOut wings ({'A'});
	wings.set_value(true);
}

void close_wings() {
	pros::ADIDigitalOut wings ({'A'});
	wings.set_value(false);
}

void grab() {
	pros::Motor intake ({7});
	intake.move_voltage(-12000);
}

void drop() {
	pros::Motor intake ({7});
	intake.move_voltage(12000);
}