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

#include <DebouncedInput.h>

DebouncedInput::DebouncedInput(byte pin_, unsigned long dbt_, boolean pullup_ = true)
{
    this->pin = pin_;
    this->debounceTime = dbt_;
    this->pullup = pullup_;
}

void DebouncedInput::begin()
{
    if (this->pullup) {
        pinMode(this->pin, INPUT_PULLUP);
    } else {
        pinMode(this->pin, INPUT);
    }
    this->value = digitalRead(this->pin);
    this->lastValue = this->value;
}

int DebouncedInput::read() 
{
    int r;
    unsigned long now = millis();
    r = digitalRead(this->pin);
    if (r != this->lrt) {
        this->lrt = r;
        this->lastChange = now;
    }
    if (now - this->lastChange > this->debounceTime) {
        if (this->value != this->lrt) {
            this->value = this->lrt;
        }
    }
    return this->value;
}

boolean DebouncedInput::changed()
{
    int r = this->read();
    if (r != this->lastValue) {
        this->lastValue = r;
        return true;
    }
    return false;
}

boolean DebouncedInput::changed(uint8_t *val) {
    if (changed()) {
        *val = this->lastValue;
        return true;
    }
    return false;
}

boolean DebouncedInput::changedTo(uint8_t val) {
    if (changed()) {
        return val == this->lastValue;
    }
    return false;
}
