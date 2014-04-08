/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    const char* systemCode = argv[1];
    bool multicode = false;
    int unitCode = 0;
    const char* unitCodeStr = argv[2];
    if (strlen(argv[2]) == 1)
        unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);

    if (wiringPiSetup () == -1) return 1;
	printf("sending systemCode[%s] unitCode[%s] command[%i]\n", systemCode, unitCodeStr, command);
	printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);

    switch(command) {
        case 1:
            if (unitCode)
                mySwitch.switchOn(systemCode, unitCode);
            else
                mySwitch.switchOn(systemCode, unitCodeStr);
            break;
        case 0:
            if (unitCode)
                mySwitch.switchOff(systemCode, unitCode);
            else
                mySwitch.switchOff(systemCode, unitCodeStr);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
	return 0;
}
