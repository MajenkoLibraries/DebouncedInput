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
 * TwoButton.ino
 *
 * Two buttons connected between pins 3/GND and 4/GND.  Two LEDs connected to
 * pins 12 and 13 with respective resistors.  Press one button and an LED
 * toggles.  Press the other button and the other LED toggles.
 */

#include <DebouncedInput.h>

const uint8_t button1Pin = 3;
const uint8_t button2Pin = 4;
const uint8_t led1Pin = 12;
const uint8_t led2Pin = 13;

// Create a new debounced button on pin 3, with a 20ms debounce period.  Enable
// the internal pullup resistor.
DebouncedInput button1(button1Pin, 20, true);

// Do the same on pin 4:
DebouncedInput button2(button2Pin, 20, true);

uint8_t led1State = LOW;
uint8_t led2State = LOW;

void setup() {
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    digitalWrite(led1Pin, led1State);
    digitalWrite(led2Pin, led2State);

    // Initialise the button pins and get the current
    // button state
    button1.begin();
    button2.begin();
}

void loop() {
    // If a button has changed from high to low (changedTo(LOW)) then
    // toggle the respective LED.
    if (button1.changedTo(LOW)) {
        led1State = !led1State;
        digitalWrite(led1Pin, led1State);
    }
    if (button2.changedTo(LOW)) {
        led2State = !led2State;
        digitalWrite(led2Pin, led2State);
    }
}
