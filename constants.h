#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <termios.h>

#ifdef __arm__ // raspberry pi
#define PORTNAME "/dev/serial0"
#else // x86 with usb adaptor
#define PORTNAME "/dev/ttyUSB0"
#endif

#define SPEED B9600
#define PARITY 0

#endif // _CONSTANTS_H_ 
