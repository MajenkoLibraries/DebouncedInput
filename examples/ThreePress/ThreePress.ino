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
 * Press a button 3 times within 2 seconds to trigger the action
 */

#include <DebouncedInput.h>

// We want to keep 3 entries.  That will allocate 24 extra bytes in the object -
// 2 arrays * 3 entries * 4 bytes per entry (unsigned long)
const uint8_t numToKeep = 3;

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

	// If the state has changed to low then check the time of a press 2 times ago.  If it was
	// fast enough, then tell us, and clear out the button press times.
	if (button.changedTo(LOW)) {
		if ((button.getLowTime(2) > 0) && (millis() - button.getLowTime(2) < 2000)) {
			Serial.println(F("You pressed it!"));
			button.clearTimes();
		}
	}
}
