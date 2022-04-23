/* MIT License
 * Copyright (c) 2022 Dirk O. Kaar <dok@dok-net.net>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Datasheet: https://www.ti.com/lit/ds/symlink/tca9544a.pdf
 */

#ifndef __tca9544a_h
#define __tca9544a_h

#include <Wire.h>

#define TCA9544ADDR 0x70

class TCA9544A
{
private:
	uint8_t _address;
	TwoWire& _i2cPort;
	uint8_t _controlRegister;

public:
	TCA9544A(TwoWire& i2cPort = Wire) : _i2cPort(i2cPort)
	{
	}

	bool begin(uint8_t address = TCA9544ADDR)
	{
		_address = address;
		return connected();
	}

	bool connected();

	bool setChannel(uint8_t channel);

	bool clearChannels();

	uint8_t readInterrupts()
	{
		return readControlRegister() >> 4;
	}

	uint8_t readControlRegister();
};

#endif // __tca9544a_h
