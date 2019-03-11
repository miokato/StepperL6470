#include <Arduino.h>
#include <StepperL6470.h>

// SM-42BYG (Holding Torque 0.22N.m)

#define PIN_SPI_SS 	10
#define PIN_MOSI 	11
#define PIN_MISO 	12
#define PIN_SCK 	13
#define PIN_BUSY 	4
#define PIN_ALARM	5
#define PIN_RESET	6

L6470 stepper(PIN_SPI_SS, PIN_MOSI, PIN_MISO, PIN_SCK, PIN_BUSY, PIN_ALARM, PIN_RESET);

void setup() {
    initialize();

    stepper.move(0, 25600); // Rotate 360
}

void loop() {
}

void initialize() {
	stepper.setparam_acc(0x8A);
	stepper.setparam_dec(0x8A);
	stepper.setparam_maxspeed(0xA);
	stepper.setparam_minspeed(0x0);
	stepper.setparam_fsspd(0x3FF);
	
	stepper.setparam_kvalhold(0xFF);
	stepper.setparam_kvalrun(0xFF); 
	stepper.setparam_kvalacc(0x64);
	stepper.setparam_kvaldec(0x32);
	
	stepper.setparam_intspd(0x408);
	stepper.setparam_stslp(0x19);
	stepper.setparam_fnslpacc(0x29);
	stepper.setparam_fnslpdec(0x29);

	stepper.setparam_stepmood(0x7);

	stepper.setparam_ocdth(0xF);
	stepper.setparam_stallth(0x7F);
}