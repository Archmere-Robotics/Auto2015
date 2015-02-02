#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-irseeker-v2-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * hitechnic-irseeker-v2.h provides an API for the HiTechnic IR Seeker V2.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Driver renamed to HTIRS2
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * Dick Swan
 * 06 April 2010
 * version 0.2
 */

#include "ht-drivers\hitechnic-sensormux.h"
#include "ht-drivers\hitechnic-irseeker-v2.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor HTIRS2L = msensor_S4_1;
const tMUXSensor HTIRS2R = msensor_S4_4;

// global variables
string sTextLines[8];

// function prototypes
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC);
void displayInstructions();

// main task
task main ()
{
  int _dirL = 0;
  int _dirR = 0;
	int lacS1, lacS2, lacS3, lacS4, lacS5 = 0;
	int racS1, racS2, racS3, racS4, racS5 = 0;
	string tmpString;

  // show the user what to do
  displayInstructions();

  eraseDisplay();
  for (int i = 0; i < 8; ++i)
    sTextLines[i] = "";

  // display the current DSP mode
  // When connected to a SMUX, the IR Seeker V2 can only be
  // used in 1200Hz mode.
  displayTextLine(0, "       L     R");

  // The sensor is connected to the first port
  // of the SMUX which is connected to the NXT port S1.
  // To access that sensor, we must use msensor_S1_1.  If the sensor
  // were connected to 3rd port of the SMUX connected to the NXT port S4,
  // we would use msensor_S4_3

  while (true)
  {
    // Read the current non modulated signal direction
    _dirL = HTIRS2readDCDir(HTIRS2L);
    if (_dirL < 0)
      break; // I2C read error occurred

    // read the current modulated signal direction
    _dirR = HTIRS2readACDir(HTIRS2R);
    if (_dirR < 0)
      break; // I2C read error occurred

    // Read the individual signal strengths of the internal sensors
    // Do this for both unmodulated (DC) and modulated signals (AC)
    if (!HTIRS2readAllDCStrength(HTIRS2L, lacS1, lacS2, lacS3, lacS4, lacS5))
      break; // I2C read error occurred
    if (!HTIRS2readAllACStrength(HTIRS2R, racS1, racS2, racS3, racS4, racS5 ))
      break; // I2C read error occurred

      displayText(1, "D", _dirL, _dirR);
      displayText(2, "0", lacS1, racS1);
      displayText(3, "1", lacS2, racS2);
      displayText(4, "2", lacS3, racS3);
      displayText(5, "3", lacS4, racS4);
      displayText(6, "4", lacS5, racS5);
    if (HTSMUXreadPowerStatus(HTSMUX))
      displayTextLine(7, "Batt: bad");
    else
      displayTextLine(7, "Batt: good");
  }
}

// Display the instructions to the user
void displayInstructions() {
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "IRSeekr2");
  displayCenteredTextLine(3, "SMUX Test");
  displayCenteredTextLine(5, "Connect SMUX to");
  displayCenteredTextLine(6, "S1 and sensor to");
  displayCenteredTextLine(7, "SMUX Port 1");
}

// Minimize LCD screen flicker by only updating LCD when data has changed
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC)
{
  string sTemp;

  stringFormat(sTemp, "%4d  %4d", nValueDC, nValueAC);
  // Check if the new line is the same as the previous one
  // Only update screen if it's different.
  if (sTemp != sTextLines[nLineNumber])
  {
    string sTemp2;

    sTextLines[nLineNumber] = sTemp;
    stringFormat(sTemp2, "%s:  %s", cChar, sTemp);
    displayTextLine(nLineNumber, sTemp2);
  }
}

/*
 * $Id: hitechnic-irseeker-v2-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */