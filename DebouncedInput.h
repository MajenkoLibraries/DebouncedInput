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

#ifndef _DEBOUNCEDINPUT_H
#define _DEBOUNCEDINPUT_H

#if ARDUINO >= 100
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#include <stdlib.h>

class DebouncedInput
{
  private:
    byte _pin;
    int _value;
    unsigned long _lastChange;
    unsigned long _debounceTime;
    int _lrt;
    boolean _pullup;
    int _lastValue;
    unsigned long *_lastHigh;
    unsigned long *_lastLow;
    uint8_t _keep;
    
  public:
    DebouncedInput(byte pin, unsigned long dbt, boolean pullup, uint8_t keep = 0);
    void begin();
    int read();
    boolean changed();
    boolean changed(uint8_t *val);
    boolean changedTo(uint8_t val);
    unsigned long getHighTime(uint8_t seq = 0);
    unsigned long getLowTime(uint8_t seq = 0);
    void clearTimes();
#ifdef __PIC32MX__
    uint32_t _intTime;
    int _intDir;
    void attachInterrupt(void (*func)(int), int dir);
    void callOnChange();
    void (*_onChange)(int);
#endif
};

#endif
