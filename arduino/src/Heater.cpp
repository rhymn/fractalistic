#include "Arduino.h"
#include "Heater.h"

/**
 * Constructor
 *
 */
Heater::Heater(int one, int two, int three, int four, int five, int six){
	_one = one;
	_two = two;
	_three = three;
	_four = four;
	_five = five;
	_six = six;
}


void Heater::setEffect(int e){

	// Each effect step has a binary equivalent for digitalWrite
	byte pattern[] = {B000000, B100000, B101000, B101010, B011010, B010110, B010101, B110101, B111101, B111111};

	digitalWrite(_two, bitRead(pattern[e], 4)); digitalWrite(_four, bitRead(pattern[e], 2)); digitalWrite(_six, bitRead(pattern[e], 0));
	digitalWrite(_one, bitRead(pattern[e], 5)); digitalWrite(_three, bitRead(pattern[e], 3)); digitalWrite(_five, bitRead(pattern[e], 1));
}





