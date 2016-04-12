/* Copyright (c) 2010-2011 mbed.org, MIT License
* Modified Mouse code for Joystick - WH 2012
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/* Contributors:
 * Tero Kontkanen
 * Etienne Saint-Paul
 */

#include "stdint.h"
#include "USBGameController.h"

bool USBGameController::update(int16_t brake, int16_t clutch, int16_t throttle, int16_t rudder, int16_t x, int16_t y, uint32_t button, uint8_t hat)
{
	Throttle = throttle;
	Brake = brake;
	Clutch = clutch;
	Rudder = rudder;
	X = x;
	Y = y;
	Z = y;
	T = y;
	Buttons = button;     
	Hat = hat;

	return(update());
}

#define AddAxisValue(m_val)		{report.data[i++] = m_val & 0xff; report.data[i++] = ((m_val & 0xff00) >> 8);}
 
bool USBGameController::update() 
{
	HID_REPORT report;

	int i=0;

	report.data[i++] = 1;
	AddAxisValue(X);
	AddAxisValue(Y);
	AddAxisValue(Z);
	AddAxisValue( Brake);
	AddAxisValue(Throttle);
	AddAxisValue(Clutch);
	AddAxisValue(Rudder);
	AddAxisValue(T);

	//report.data[8] = ((Buttons & 0x0f) << 4) | (Hat & 0x0f) ;
	report.data[i++] = ((Buttons & 0xff) >>0);
	report.data[i++] = ((Buttons & 0xff00) >>8);
	report.data[i++] = ((Buttons & 0xff0000) >>16);
	report.data[i++] = ((Buttons & 0xff000000) >>24);
	report.length = i;

	return send(&report);
}

bool USBGameController::throttle(int16_t t) {
     Throttle = t;
     return update();
}

bool USBGameController::rudder(int16_t r) {
     Brake = r;
     return update();
}

bool USBGameController::move(int16_t x, int16_t y) {
     X = x;
     Y = y;
     return update();
}

bool USBGameController::button(uint32_t button) {
     Buttons = button;
     return update();
}

bool USBGameController::hat(uint8_t hat) {
     Hat = hat;
     return update();
}


void USBGameController::_init() {

   Throttle = -127;
   Brake = -127;
   Clutch=0;
   Rudder=0;
   X = 0;                       
   Y = 0;     
   Buttons = 0x00;
   Hat = 0x00;              
}

#define NB_AXIS			8
#define NB_FF_AXIS		1

#define X_AXIS_NB_BITS	16
#define Y_AXIS_NB_BITS	16
#define Z_AXIS_NB_BITS	16
#define RX_AXIS_NB_BITS	16
#define RY_AXIS_NB_BITS	16
#define RZ_AXIS_NB_BITS	16
#define SX_AXIS_NB_BITS	16
#define SY_AXIS_NB_BITS	16
#define NB_BUTTONS		32

#define X_AXIS_LOG_MAX		((1L<<(X_AXIS_NB_BITS-1))-1)
#define X_AXIS_LOG_MIN		(-X_AXIS_LOG_MAX)
#define X_AXIS_PHYS_MAX		((1L<<X_AXIS_NB_BITS)-1)

#define Y_AXIS_LOG_MAX		((1L<<(Y_AXIS_NB_BITS))-1)
#define Y_AXIS_LOG_MIN		0//(-Y_AXIS_LOG_MAX)
#define Y_AXIS_PHYS_MAX		((1L<<Y_AXIS_NB_BITS)-1)

#define Z_AXIS_LOG_MAX		((1L<<(Z_AXIS_NB_BITS))-1)
#define Z_AXIS_LOG_MIN		0//(-Z_AXIS_LOG_MAX)
#define Z_AXIS_PHYS_MAX		((1L<<Z_AXIS_NB_BITS)-1)

#define RX_AXIS_LOG_MAX		((1L<<(RX_AXIS_NB_BITS))-1)
#define RX_AXIS_LOG_MIN		0//(-RX_AXIS_LOG_MAX)
#define RX_AXIS_PHYS_MAX	((1L<<RX_AXIS_NB_BITS)-1)

#define RY_AXIS_LOG_MAX		((1L<<(RY_AXIS_NB_BITS))-1)
#define RY_AXIS_LOG_MIN		0//(-RY_AXIS_LOG_MAX)
#define RY_AXIS_PHYS_MAX	((1L<<RY_AXIS_NB_BITS)-1)

#define RZ_AXIS_LOG_MAX		((1L<<(RZ_AXIS_NB_BITS))-1)
#define RZ_AXIS_LOG_MIN		0//(-RZ_AXIS_LOG_MAX)
#define RZ_AXIS_PHYS_MAX	((1L<<RZ_AXIS_NB_BITS)-1)

#define SX_AXIS_LOG_MAX		((1L<<(SX_AXIS_NB_BITS))-1)
#define SX_AXIS_LOG_MIN		0//(-SX_AXIS_LOG_MAX)
#define SX_AXIS_PHYS_MAX	((1L<<SX_AXIS_NB_BITS)-1)

#define SY_AXIS_LOG_MAX		((1L<<(SY_AXIS_NB_BITS))-1)
#define SY_AXIS_LOG_MIN		0//(-SY_AXIS_LOG_MAX)
#define SY_AXIS_PHYS_MAX	((1L<<SY_AXIS_NB_BITS)-1)


#define ADD_FFB

static uint8_t ffb_joystick_report_desc[] = 
{
	0x05, 0x01,                     // Usage Page (Generic Desktop)
	0x09, 0x04,                     // Usage (Joystick)
	0xA1, 0x01,                     // Collection (Application)
	0x85, 0x01,	// REPORT_ID (1)

 #if NB_AXIS>=1
		0x09, 0x01,                     // Usage (Pointer)
        0xA1, 0x00,                     // Collection ()
			0x09, 0x30,					// USAGE (x)
			0x16,X_AXIS_LOG_MIN & 0xFF,(X_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,X_AXIS_LOG_MAX & 0xFF,(X_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,X_AXIS_PHYS_MAX & 0xFF,(X_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(X_AXIS_PHYS_MAX >> 16) & 0xFF,(X_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,X_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#if NB_AXIS>=2
			0x09,0x31,					// USAGE (y)
			0x16,Y_AXIS_LOG_MIN & 0xFF,(Y_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,Y_AXIS_LOG_MAX & 0xFF,(Y_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,Y_AXIS_PHYS_MAX & 0xFF,(Y_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(Y_AXIS_PHYS_MAX >> 16) & 0xFF,(Y_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,Y_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif //NB_AXIS>=2
#if NB_AXIS>=3
			0x09,0x32,					// USAGE (z)
			0x16,Z_AXIS_LOG_MIN & 0xFF,(Z_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,Z_AXIS_LOG_MAX & 0xFF,(Z_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,Z_AXIS_PHYS_MAX & 0xFF,(Z_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(Z_AXIS_PHYS_MAX >> 16) & 0xFF,(Z_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,Z_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif //NB_AXIS>=3
#if NB_AXIS>=4
			0x09,0x33, // USAGE (Pointer)
			0x16,RX_AXIS_LOG_MIN & 0xFF,(RX_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,RX_AXIS_LOG_MAX & 0xFF,(RX_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,RX_AXIS_PHYS_MAX & 0xFF,(RX_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(RX_AXIS_PHYS_MAX >> 16) & 0xFF,(RX_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,RX_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif	//NB_AXIS>=4
#if NB_AXIS>=5
			0x09,0x34,					// USAGE (y)
			0x16,RY_AXIS_LOG_MIN & 0xFF,(RY_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,RY_AXIS_LOG_MAX & 0xFF,(RY_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,RY_AXIS_PHYS_MAX & 0xFF,(RY_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(RY_AXIS_PHYS_MAX >> 16) & 0xFF,(RY_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,RY_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif	//NB_AXIS>=5
#if NB_AXIS>=6
			0x09,0x35,					// USAGE (z)
			0x16,RZ_AXIS_LOG_MIN & 0xFF,(RZ_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,RZ_AXIS_LOG_MAX & 0xFF,(RZ_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,RZ_AXIS_PHYS_MAX & 0xFF,(RZ_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(RZ_AXIS_PHYS_MAX >> 16) & 0xFF,(RZ_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,RZ_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif	//NB_AXIS>=6
#if NB_AXIS>=7
			0x09,0x36,					// USAGE (z)
			0x16,SX_AXIS_LOG_MIN & 0xFF,(SX_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,SX_AXIS_LOG_MAX & 0xFF,(SX_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,SX_AXIS_PHYS_MAX & 0xFF,(SX_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(SX_AXIS_PHYS_MAX >> 16) & 0xFF,(SX_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,SX_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif	//NB_AXIS>=7
#if NB_AXIS>=8
			0x09,0x37,					// USAGE (z)
			0x16,SY_AXIS_LOG_MIN & 0xFF,(SY_AXIS_LOG_MIN >> 8) & 0xFF, // LOGICAL_MINIMUM
			0x27,SY_AXIS_LOG_MAX & 0xFF,(SY_AXIS_LOG_MAX >> 8) & 0xFF,0,0, // LOGICAL_MAXIMUM
			0x35,0x00,					// PHYSICAL_MINIMUM (00)
			0x47,SY_AXIS_PHYS_MAX & 0xFF,(SY_AXIS_PHYS_MAX >> 8) & 0xFF,0,0,//(SY_AXIS_PHYS_MAX >> 16) & 0xFF,(SY_AXIS_PHYS_MAX >> 24) & 0xFF, // LOGICAL_MAXIMUM (0xffff)
			0x75,SY_AXIS_NB_BITS,		// REPORT_SIZE (AXIS_NB_BITS)
			0x95,1,						// REPORT_COUNT (1)
			0x81,0x02,					// INPUT (Data,Var,Abs)
#endif	//NB_AXIS>=8
		0xC0,                           // End Collection
#endif	//NB_AXIS>=1

		0x15, 0x00,                     // Logical Minimum (0)
		0x25, 0x01,                     // Logical Maximum (1)
		0x75, 0x01,                     // Report Size (1)
		0x95, 0x20,                     // Report Count (32)
		0x05, 0x09,                     // Usage Page (Button)
		0x19, 0x01,                     // Usage Minimum (Button #1)
		0x29, 0x20,                     // Usage Maximum (Button #32)
		0x81, 0x02,                     // Input (variable,absolute)

#ifdef ADD_FFB
		0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
		0x09, 0x92,	// USAGE (PID State Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x02,	// REPORT_ID (02)
			0x09, 0x9F,	// USAGE (Device Paused)
			0x09, 0xA0,	// USAGE (Actuators Enabled)
			0x09, 0xA4,	// USAGE (Safety Switch)
			0x09, 0xA5,	// USAGE (Actuator Override Switch)
			0x09, 0xA6,	// USAGE (Actuator Power)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x25, 0x01,	// LOGICAL_MINIMUM (01)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
			0x75, 0x01,	// REPORT_SIZE (01)
			0x95, 0x05,	// REPORT_COUNT (05)
			0x81, 0x02,	// INPUT (Data,Var,Abs)
			0x95, 0x03,	// REPORT_COUNT (03)
			0x81, 0x03,	// INPUT (Constant,Var,Abs)
			0x09, 0x94,	// USAGE (Effect Playing)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x25, 0x01,	// LOGICAL_MAXIMUM (01)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
			0x75, 0x01,	// REPORT_SIZE (01)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x81, 0x02,	// INPUT (Data,Var,Abs)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x07,	// REPORT_SIZE (07)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x81, 0x02,	// INPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x21,	// USAGE (Set Effect Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x03,	// REPORT_ID (01)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x25,	// USAGE (25)
			0xA1, 0x02,	// COLLECTION (Logical)
			0x09, 0x26,	// USAGE (26)
			0x09, 0x27,	// USAGE (27)
			0x09, 0x30,	// USAGE (30)
			0x09, 0x31,	// USAGE (31)
			0x09, 0x32,	// USAGE (32)
			0x09, 0x33,	// USAGE (33)
			0x09, 0x34,	// USAGE (34)
			0x09, 0x40,	// USAGE (40)
			0x09, 0x41,	// USAGE (41)
			0x09, 0x42,	// USAGE (42)
			0x09, 0x43,	// USAGE (43)
			0x09, 0x28,	// USAGE (28)
			0x25, 0x0C,	// LOGICAL_MAXIMUM (0C)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x0C,	// PHYSICAL_MAXIMUM (0C)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x00,	// OUTPUT (Data)
		0xC0,	// END COLLECTION ()
			0x09, 0x50,	// USAGE (Duration)
			0x09, 0x54,	// USAGE (Trigger Repeat Interval)
			0x09, 0x51,	// USAGE (Sample Period)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x7F,	// LOGICAL_MAXIMUM (7F FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x7F,	// PHYSICAL_MAXIMUM (7F FF)
			0x66, 0x03, 0x10,	// UNIT (Eng Lin:Time)
			0x55, 0xFD,	// UNIT_EXPONENT (-3)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x03,	// REPORT_COUNT (03)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x55, 0x00,	// UNIT_EXPONENT (00)
			0x66, 0x00, 0x00,	// UNIT (None)
			0x09, 0x52,	// USAGE (Gain)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x53,	// USAGE (Trigger Button)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x08,	// LOGICAL_MAXIMUM (08)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x08,	// PHYSICAL_MAXIMUM (08)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x55,	// USAGE (Axes Enable)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x05, 0x01,	// USAGE_PAGE (Generic Desktop)
				0x09, 0x30,	// USAGE (X)
#if NB_FF_AXIS>1
				0x09, 0x31,	// USAGE (Y)
#endif	//NB_AXIS>1
				0x15, 0x00,	// LOGICAL_MINIMUM (00)
				0x25, 0x01,	// LOGICAL_MAXIMUM (01)
				0x75, 0x01,	// REPORT_SIZE (01)
				0x95, NB_FF_AXIS,	// REPORT_COUNT (NB_FF_AXIS)
				0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0xC0,	// END COLLECTION ()
			0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
			0x09, 0x56,	// USAGE (Direction Enable)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x95, 0x07 - NB_FF_AXIS,	// REPORT_COUNT (05 (2 axes) or 06 (1 axes)) seems to be for padding
			0x91, 0x03,	// OUTPUT (Constant,Var,Abs)
			0x09, 0x57,	// USAGE (Direction)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x0B, 0x01, 0x00, 0x0A, 0x00,
				0x0B, 0x02, 0x00, 0x0A, 0x00,
				0x66, 0x14, 0x00,	// UNIT (Eng Rot:Angular Pos)
				0x55, 0xFE,	// UNIT_EXPONENT (FE)
				0x15, 0x00,	// LOGICAL_MINIMUM (00)
				0x26, 0xB4, 0x00,	// LOGICAL_MAXIMUM (00 B4)
				0x35, 0x00,	// PHYSICAL_MINIMUM (00)
				0x47, 0xA0, 0x8C, 0x00, 0x00,	// PHYSICAL_MAXIMUM (00 00 8C A0)
				0x66, 0x00, 0x00,	// UNIT (None)
				0x75, 0x08,	// REPORT_SIZE (08)
				0x95, 0x01,	// REPORT_COUNT (01)		//0x02,	// REPORT_COUNT (02)
				0x91, 0x02,	// OUTPUT (Data,Var,Abs)
				0x55, 0x00,	// UNIT_EXPONENT (00)
				0x66, 0x00, 0x00,	// UNIT (None)
			0xC0,	// END COLLECTION ()
			0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
//			0x09,0xA7,	// USAGE (Start Delay)
			0x66, 0x03, 0x10,	// UNIT (Eng Lin:Time)
			0x55, 0xFD,	// UNIT_EXPONENT (-3)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x7F,	// LOGICAL_MAXIMUM (7F FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x7F,	// PHYSICAL_MAXIMUM (7F FF)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
//			0x91,0x02,	// OUTPUT (Data,Var,Abs)
			0x66, 0x00, 0x00,	// UNIT (None)
			0x55, 0x00,	// UNIT_EXPONENT (00)
		0xC0,	// END COLLECTION ()

		0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
		0x09, 0x5A,	// USAGE (Set Envelope Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x04,	// REPORT_ID (02)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x5B,	// USAGE (Attack Level)
			0x09, 0x5D,	// USAGE (Fade Level)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x95, 0x02,	// REPORT_COUNT (02)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x5C,	// USAGE (5C)
			0x09, 0x5E,	// USAGE (5E)
			0x66, 0x03, 0x10,	// UNIT (Eng Lin:Time)
			0x55, 0xFD,	// UNIT_EXPONENT (-3)
			0x26, 0xFF, 0x7F,	// LOGICAL_MAXIMUM (7F FF)
			0x46, 0xFF, 0x7F,	// PHYSICAL_MAXIMUM (7F FF)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x45, 0x00,	// PHYSICAL_MAXIMUM (00)
			0x66, 0x00, 0x00,	// UNIT (None)
			0x55, 0x00,	// UNIT_EXPONENT (00)
		0xC0,	// END COLLECTION ()

		0x09, 0x5F,	// USAGE (Set Condition Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x05,	// REPORT_ID (03)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x23,	// USAGE (Parameter Block Offset)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x25, 0x01,	// LOGICAL_MAXIMUM (01)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
			0x75, 0x04,	// REPORT_SIZE (04)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x58,	// USAGE (Type Specific Block Offset)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x0B, 0x01, 0x00, 0x0A, 0x00,	// USAGE (Instance 1)
				0x0B, 0x02, 0x00, 0x0A, 0x00,	// USAGE (Instance 2)
				0x75, 0x02,	// REPORT_SIZE (02)
				0x95, 0x02,	// REPORT_COUNT (02)
				0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0xC0,	// END COLLECTION ()
			0x15, 0x80,	// LOGICAL_MINIMUM (80)
			0x25, 0x7F,	// LOGICAL_MAXIMUM (7F)
			0x36, 0xF0, 0xD8,	// PHYSICAL_MINIMUM (-10000)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x09, 0x60,	// USAGE (CP Offset)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x36, 0xF0, 0xD8,	// PHYSICAL_MINIMUM (-10000)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x09, 0x61,	// USAGE (Positive Coefficient)
//			0x09,0x62,	// USAGE (Negative Coefficient)
			0x95, 0x01,	// REPORT_COUNT (01)	// ???? WAS 2 with "negative coeff"
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x09, 0x63,	// USAGE (Positive Saturation)
			0x09, 0x64,	// USAGE (Negative Saturation)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x02,	// REPORT_COUNT (02)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
//			0x09,0x65,	// USAGE (Dead Band )
//			0x46,0x10,0x27,	// PHYSICAL_MAXIMUM (10000)
//			0x95,0x01,	// REPORT_COUNT (01)
//			0x91,0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x6E,	// USAGE (Set Periodic Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x06,	// REPORT_ID (04)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x70,	// USAGE (Magnitude)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x6F,	// USAGE (Offset)
			0x15, 0x80,	// LOGICAL_MINIMUM (80)
			0x25, 0x7F,	// LOGICAL_MAXIMUM (7F)
			0x36, 0xF0, 0xD8,	// PHYSICAL_MINIMUM (-10000)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x71,	// USAGE (Phase)
			0x66, 0x14, 0x00,	// UNIT (Eng Rot:Angular Pos)
			0x55, 0xFE,	// UNIT_EXPONENT (FE)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x47, 0xA0, 0x8C, 0x00, 0x00,	// PHYSICAL_MAXIMUM (00 00 8C A0)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x72,	// USAGE (Period)
			0x26, 0xFF, 0x7F,	// LOGICAL_MAXIMUM (7F FF)
			0x46, 0xFF, 0x7F,	// PHYSICAL_MAXIMUM (7F FF)
			0x66, 0x03, 0x10,	// UNIT (Eng Lin:Time)
			0x55, 0xFD,	// UNIT_EXPONENT (-3)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x66, 0x00, 0x00,	// UNIT (None)
			0x55, 0x00,	// UNIT_EXPONENT (00)
		0xC0,	// END COLLECTION ()

		0x09, 0x73,	// USAGE (Set Constant Force Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x07,	// REPORT_ID (05)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x70,	// USAGE (Magnitude)
			0x16, 0x01, 0xFF,	// LOGICAL_MINIMUM (-255)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (255)
			0x36, 0xF0, 0xD8,	// PHYSICAL_MINIMUM (-10000)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x74,	// USAGE (Set Ramp Force Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x08,	// REPORT_ID (06)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x75,	// USAGE (Ramp Start)
			0x09, 0x76,	// USAGE (Ramp End)
			0x15, 0x80,	// LOGICAL_MINIMUM (-128)
			0x25, 0x7F,	// LOGICAL_MAXIMUM (127)
			0x36, 0xF0, 0xD8,	// PHYSICAL_MINIMUM (-10000)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x02,	// REPORT_COUNT (02)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x68,	// USAGE (Custom Force Data Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x09,	// REPORT_ID (07)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x6C,	// USAGE (Custom Force Data Offset)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0x10, 0x27,	// LOGICAL_MAXIMUM (10000)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x69,	// USAGE (Custom Force Data)
			0x15, 0x81,	// LOGICAL_MINIMUM (-127)
			0x25, 0x7F,	// LOGICAL_MAXIMUM (127)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x00,	// PHYSICAL_MAXIMUM (255)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x0C,	// REPORT_COUNT (0C)
			0x92, 0x02, 0x01,	// OUTPUT ( Data,Var,Abs,Buf)
		0xC0,	// END COLLECTION ()

		0x09, 0x66,	// USAGE (Download Force Sample)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0A,	// REPORT_ID (08)
			0x05, 0x01,	// USAGE_PAGE (Generic Desktop)
			0x09, 0x30,	// USAGE (X)
			0x09, 0x31,	// USAGE (Y)
			0x15, 0x81,	// LOGICAL_MINIMUM (-127)
			0x25, 0x7F,	// LOGICAL_MAXIMUM (127)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x00,	// PHYSICAL_MAXIMUM (255)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x02,	// REPORT_COUNT (02)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
		0x09, 0x77,	// USAGE (Effect Operation Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0B,	// REPORT_ID (0A)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x78,	// USAGE (78)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x09, 0x79,	// USAGE (Op Effect Start)
				0x09, 0x7A,	// USAGE (Op Effect Start Solo)
				0x09, 0x7B,	// USAGE (Op Effect Stop)
				0x15, 0x01,	// LOGICAL_MINIMUM (01)
				0x25, 0x03,	// LOGICAL_MAXIMUM (03)
				0x75, 0x08,	// REPORT_SIZE (08)
				0x95, 0x01,	// REPORT_COUNT (01)
				0x91, 0x00,	// OUTPUT (Data,Ary,Abs)
			0xC0,	// END COLLECTION ()
			0x09, 0x7C,	// USAGE (Loop Count)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x00,	// PHYSICAL_MAXIMUM (00 FF)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x90,	// USAGE (PID Block Free Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0C,	// REPORT_ID (0B)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x96,	// USAGE (PID Device Control)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0D,	// REPORT_ID (0C)
			0x09, 0x97,	// USAGE (DC Enable Actuators)
			0x09, 0x98,	// USAGE (DC Disable Actuators)
			0x09, 0x99,	// USAGE (DC Stop All Effects)
			0x09, 0x9A,	// USAGE (DC Device Reset)
			0x09, 0x9B,	// USAGE (DC Device Pause)
			0x09, 0x9C,	// USAGE (DC Device Continue)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x06,	// LOGICAL_MAXIMUM (06)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x00,	// OUTPUT (Data)
		0xC0,	// END COLLECTION ()

		0x09, 0x7D,	// USAGE (Device Gain Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0E,	// REPORT_ID (0D)
			0x09, 0x7E,	// USAGE (Device Gain)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0x10, 0x27,	// PHYSICAL_MAXIMUM (10000)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
		0xC0,	// END COLLECTION ()

		0x09, 0x6B,	// USAGE (Set Custom Force Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x0F,	// REPORT_ID (0E)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x6D,	// USAGE (Sample Count)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x00,	// PHYSICAL_MAXIMUM (00 FF)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x09, 0x51,	// USAGE (Sample Period)
			0x66, 0x03, 0x10,	// UNIT (Eng Lin:Time)
			0x55, 0xFD,	// UNIT_EXPONENT (-3)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x7F,	// LOGICAL_MAXIMUM (32767)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x7F,	// PHYSICAL_MAXIMUM (32767)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x91, 0x02,	// OUTPUT (Data,Var,Abs)
			0x55, 0x00,	// UNIT_EXPONENT (00)
			0x66, 0x00, 0x00,	// UNIT (None)
		0xC0,	// END COLLECTION ()

		0x09, 0xAB,	// USAGE (Create New Effect Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x10,	// REPORT_ID (05)
			0x09, 0x25,	// USAGE (Effect Type)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x09, 0x26,	// USAGE (26)
				0x09, 0x27,	// USAGE (27)
				0x09, 0x30,	// USAGE (30)
				0x09, 0x31,	// USAGE (31)
				0x09, 0x32,	// USAGE (32)
				0x09, 0x33,	// USAGE (33)
				0x09, 0x34,	// USAGE (34)
				0x09, 0x40,	// USAGE (40)
				0x09, 0x41,	// USAGE (41)
				0x09, 0x42,	// USAGE (42)
				0x09, 0x43,	// USAGE (43)
				0x09, 0x28,	// USAGE (28)
				0x25, 0x0C,	// LOGICAL_MAXIMUM (0C)
				0x15, 0x01,	// LOGICAL_MINIMUM (01)
				0x35, 0x01,	// PHYSICAL_MINIMUM (01)
				0x45, 0x0C,	// PHYSICAL_MAXIMUM (0C)
				0x75, 0x08,	// REPORT_SIZE (08)
				0x95, 0x01,	// REPORT_COUNT (01)
				0xB1, 0x00,	// FEATURE (Data)
			0xC0,	// END COLLECTION ()
			0x05, 0x01,	// USAGE_PAGE (Generic Desktop)
			0x09, 0x3B,	// USAGE (Byte Count)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x26, 0xFF, 0x01,	// LOGICAL_MAXIMUM (511)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x46, 0xFF, 0x01,	// PHYSICAL_MAXIMUM (511)
			0x75, 0x0A,	// REPORT_SIZE (0A)
			0x95, 0x01,	// REPORT_COUNT (01)
			0xB1, 0x02,	// FEATURE (Data,Var,Abs)
			0x75, 0x06,	// REPORT_SIZE (06)
			0xB1, 0x01,	// FEATURE (Constant,Ary,Abs)
		0xC0,	// END COLLECTION ()

		0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
		0x09, 0x89,	// USAGE (PID Block Load Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x11,	// REPORT_ID (06)
			0x09, 0x22,	// USAGE (Effect Block Index)
			0x25, 0x28,	// LOGICAL_MAXIMUM (28)
			0x15, 0x01,	// LOGICAL_MINIMUM (01)
			0x35, 0x01,	// PHYSICAL_MINIMUM (01)
			0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0xB1, 0x02,	// FEATURE (Data,Var,Abs)
			0x09, 0x8B,	// USAGE (Block Load Status)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x09, 0x8C,	// USAGE (Block Load Success)
				0x09, 0x8D,	// USAGE (Block Load Full)
				0x09, 0x8E,	// USAGE (Block Load Error)
				0x25, 0x03,	// LOGICAL_MAXIMUM (03)
				0x15, 0x01,	// LOGICAL_MINIMUM (01)
				0x35, 0x01,	// PHYSICAL_MINIMUM (01)
				0x45, 0x03,	// PHYSICAL_MAXIMUM (03)
				0x75, 0x08,	// REPORT_SIZE (08)
				0x95, 0x01,	// REPORT_COUNT (01)
				0xB1, 0x00,	// FEATURE (Data)
			0xC0,	// END COLLECTION ()
			0x09, 0xAC,	// USAGE (RAM Pool Available)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x27, 0xFF, 0xFF, 0x00, 0x00,	// LOGICAL_MAXIMUM (00 00 FF FF)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x47, 0xFF, 0xFF, 0x00, 0x00,	// PHYSICAL_MAXIMUM (00 00 FF FF)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0xB1, 0x00,	// FEATURE (Data)
		0xC0,	// END COLLECTION ()

		0x09, 0x7F,	// USAGE (PID Pool Report)
		0xA1, 0x02,	// COLLECTION (Logical)
			0x85, 0x12,	// REPORT_ID (07)
			0x09, 0x80,	// USAGE (RAM Pool Size)
			0x75, 0x10,	// REPORT_SIZE (10)
			0x95, 0x01,	// REPORT_COUNT (01)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x27, 0xFF, 0xFF, 0x00, 0x00,	// LOGICAL_MAXIMUM (00 00 FF FF)
			0x47, 0xFF, 0xFF, 0x00, 0x00,	// PHYSICAL_MAXIMUM (00 00 FF FF)
			0xB1, 0x02,	// FEATURE (Data,Var,Abs)
			0x09, 0x83,	// USAGE (Simultaneous Effects Max)
			0x26, 0xFF, 0x00,	// LOGICAL_MAXIMUM (00 FF)
			0x46, 0xFF, 0x00,	// PHYSICAL_MAXIMUM (00 FF)
			0x75, 0x08,	// REPORT_SIZE (08)
			0x95, 0x01,	// REPORT_COUNT (01)
			0xB1, 0x02,	// FEATURE (Data,Var,Abs)
			0x09, 0xA9,	// USAGE (Device Managed Pool)
			0x09, 0xAA,	// USAGE (Shared Parameter Blocks)
			0x75, 0x01,	// REPORT_SIZE (01)
			0x95, 0x02,	// REPORT_COUNT (02)
			0x15, 0x00,	// LOGICAL_MINIMUM (00)
			0x25, 0x01,	// LOGICAL_MAXIMUM (01)
			0x35, 0x00,	// PHYSICAL_MINIMUM (00)
			0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
			0xB1, 0x02,	// FEATURE (Data,Var,Abs)
			0x75, 0x06,	// REPORT_SIZE (06)
			0x95, 0x01,	// REPORT_COUNT (01)
			0xB1, 0x03,	// FEATURE ( Cnst,Var,Abs)
		0xC0,	// END COLLECTION ()
#endif	//ADD_FFB
	0xc0, // END_COLLECTION
};

uint8_t * USBGameController::reportDesc() 
{   
/*
         static uint8_t reportDescriptor[] = {

             USAGE_PAGE(1), 0x01,           // Generic Desktop           
             LOGICAL_MINIMUM(1), 0x00,      // Logical_Minimum (0)             
             USAGE(1), 0x04,                // Usage (Joystick)
             COLLECTION(1), 0x01,           // Application

               USAGE_PAGE(1), 0x01,            // Generic Desktop
               USAGE(1), 0x01,                 // Usage (Pointer)
               COLLECTION(1), 0x00,            // Physical
                 USAGE(1), 0x30,                 // X, wheel angle
                 USAGE(1), 0x31,                 // Y, always 0

				 //pedals etc
				 USAGE(1), 0x32,                 // Z
                 USAGE(1), 0x33,                 // Rx
                 USAGE(1), 0x34,                 // Ry
                 USAGE(1), 0x35,                 // Rz
			     USAGE(1), 0x36,                 // Rz
			     USAGE(1), 0x37,                 // Rz

				 // 16 bit values
                 LOGICAL_MINIMUM(2), 0x01, 0x80,       // -32767
                 LOGICAL_MAXIMUM(2), 0xff, 0x7f, // 32767
                 REPORT_SIZE(1), 0x10,
                 REPORT_COUNT(1), 0x08,
                 INPUT(1), 0x02,                 // Data, Variable, Absolute

               END_COLLECTION(0),               

               USAGE_PAGE(1), 0x09,            // Buttons
               USAGE_MINIMUM(1), 0x01,         // 1
               USAGE_MAXIMUM(1), 0x20,         // 32
               LOGICAL_MINIMUM(1), 0x00,       // 0
               LOGICAL_MAXIMUM(1), 0x01,       // 1
               REPORT_SIZE(1), 0x01,
               REPORT_COUNT(1), 0x20,
               UNIT_EXPONENT(1), 0x00,         // Unit_Exponent (0)
               UNIT(1), 0x00,                  // Unit (None)                                           
               INPUT(1), 0x02,                 // Data, Variable, Absolute
             END_COLLECTION(0)

        };

      reportLength = sizeof(reportDescriptor);
      return reportDescriptor;
*/
	reportLength = sizeof(ffb_joystick_report_desc);
	return ffb_joystick_report_desc;
}

uint8_t * USBGameController::stringIproductDesc() {
    static uint8_t stringIproductDescriptor[] = {
        0x12,                                                       //bLength
        STRING_DESCRIPTOR,                                          //bDescriptorType 0x03
        'S',0,'i',0,'m',0,'u',0,'C',0,'U',0,'B',0,'E',0 //bString iProduct - HID device
    };
    return stringIproductDescriptor;
}

bool USBGameController::EPINT_OUT_callback()
{
	bool returnval;

    USBDevice::readEP(EPINT_OUT, receivedReports[receivedReportBufferHead].data, &receivedReports[receivedReportBufferHead].length, MAX_HID_REPORT_SIZE);

	receivedReportBufferHead=(receivedReportBufferHead+1)&(RX_REPORT_BUFFER_COUNT-1);

    // We activate the endpoint to be able to recceive data
    if (!readStart(EPINT_OUT, MAX_HID_REPORT_SIZE))
        returnval= false;
    else
    	returnval= true;

    return returnval;
}

unsigned int USBGameController::getPendingReceivedReportCount()
{
	 //calculate how many reports are pending to read
	 return (receivedReportBufferHead-receivedReportBufferTail)&(RX_REPORT_BUFFER_COUNT-1);
}

HID_REPORT USBGameController::getReceivedReport()
{
	 int takeFrom=receivedReportBufferTail;
	 receivedReportBufferTail=(receivedReportBufferTail+1)&(RX_REPORT_BUFFER_COUNT-1);
	 return receivedReports[takeFrom];
}


bool USBGameController::handleReceivedHIDReport(HID_REPORT report)
{
	int type=report.data[0];//type is integer that is defined descriptor as REPORT_ID

	switch(type)
	{
	case 13:
		/*	13 = 	0x09, 0x96,	// USAGE (PID Device Control)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x85, 0x0D,	// REPORT_ID (0C)
				0x09, 0x97,	// USAGE (DC Enable Actuators)
				0x09, 0x98,	// USAGE (DC Disable Actuators)
				0x09, 0x99,	// USAGE (DC Stop All Effects)
				0x09, 0x9A,	// USAGE (DC Device Reset)
				0x09, 0x9B,	// USAGE (DC Device Pause)
				0x09, 0x9C,	// USAGE (DC Device Continue)
		 */
		int command=report.data[1];
		switch(command)
		{
		case 1://enable actuators
			FFBEnabled=true;
			break;
		case 2://disable actuators
			FFBEnabled=false;
			break;
		case 3://stop all effects
			break;
		case 4://device reset
			break;
		case 5://device pause
			break;
		case 6://continue
			break;
		}

		//should we send PID status report now?
		if(FFBEnabled)
		{
			/*generate report
			0x05, 0x0F,	// USAGE_PAGE (Physical Interface)
			0x09, 0x92,	// USAGE (PID State Report)
			0xA1, 0x02,	// COLLECTION (Logical)
				0x85, 0x02,	// REPORT_ID (02)
				0x09, 0x9F,	// USAGE (Device Paused)
				0x09, 0xA0,	// USAGE (Actuators Enabled)
				0x09, 0xA4,	// USAGE (Safety Switch)
				0x09, 0xA5,	// USAGE (Actuator Override Switch)
				0x09, 0xA6,	// USAGE (Actuator Power)
				0x15, 0x00,	// LOGICAL_MINIMUM (00)
				0x25, 0x01,	// LOGICAL_MINIMUM (01)
				0x35, 0x00,	// PHYSICAL_MINIMUM (00)
				0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
				0x75, 0x01,	// REPORT_SIZE (01)
				0x95, 0x05,	// REPORT_COUNT (05)
				0x81, 0x02,	// INPUT (Data,Var,Abs)
				0x95, 0x03,	// REPORT_COUNT (03)
				0x81, 0x03,	// INPUT (Constant,Var,Abs)
				0x09, 0x94,	// USAGE (Effect Playing)
				0x15, 0x00,	// LOGICAL_MINIMUM (00)
				0x25, 0x01,	// LOGICAL_MAXIMUM (01)
				0x35, 0x00,	// PHYSICAL_MINIMUM (00)
				0x45, 0x01,	// PHYSICAL_MAXIMUM (01)
				0x75, 0x01,	// REPORT_SIZE (01)
				0x95, 0x01,	// REPORT_COUNT (01)
				0x81, 0x02,	// INPUT (Data,Var,Abs)
				0x09, 0x22,	// USAGE (Effect Block Index)
				0x15, 0x01,	// LOGICAL_MINIMUM (01)
				0x25, 0x28,	// LOGICAL_MAXIMUM (28)
				0x35, 0x01,	// PHYSICAL_MINIMUM (01)
				0x45, 0x28,	// PHYSICAL_MAXIMUM (28)
				0x75, 0x07,	// REPORT_SIZE (07)
				0x95, 0x01,	// REPORT_COUNT (01)
				0x81, 0x02,	// INPUT (Data,Var,Abs)*/
			HID_REPORT report_out;
			int i=0;
			report_out.data[i++] = 2;
			report_out.data[i++] = 0b11010;
			report_out.data[i++] = 0;
			report_out.length = i;
			return send(&report_out);
		}
		else//disable
		{
			HID_REPORT report_out;
			int i=0;
			report_out.data[i++] = 2;
			report_out.data[i++] = 0b1000;
			report_out.data[i++] = 0;
			report_out.length = i;
			return send(&report_out);
		}
		break;
	}
}

