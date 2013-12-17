/*
 * Copyright (c) 2013, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This sketch will demonstrate the ability to log a number of previous state changes.
 * If the "keep" parameter is specified to the DebouncedInput constructor (parameter
 * 4) a pair of arrays are maintained internally with the timestamps of the previous
 * respective state changes.  The arrays operate as a FIFD register (First In First
 * Dropped) and values shift down through the array from entry 0 (the newest) to
 * the last entry (the oldest).
 */

#include <DebouncedInput.h>

// We want to keep 10 entries.  That will allocate 80 extra bytes in the object -
// 2 arrays * 10 entries * 4 bytes per entry (unsigned long)
const uint8_t numToKeep = 10;

// We want the button on pin 3.
const uint8_t buttonPin = 3;

// 20ms debounce time, with the internal pull-up enabled
DebouncedInput button(buttonPin, 20, true, numToKeep);

void setup() {
	// Set the pinMode and get the initial button state.
	button.begin();
	Serial.begin(9600);
}

void loop() {

	// If the state has changed to low then, for each of the previous 10 entries,
	// print the difference between them and the current time.
	if (button.changedTo(LOW)) {
		unsigned long now = millis();
		Serial.print(F("Time since last "));
		Serial.print(numToKeep);
		Serial.println(F(" button presses:"));
		for (int i = 0; i < 10; i++) {
			Serial.print(F("  "));
			Serial.print(now - button.getLowTime(i));
			Serial.println(F("ms"));
		}
	}
}
