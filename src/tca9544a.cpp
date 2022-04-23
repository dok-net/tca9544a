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

#include "tca9544a.h"

bool TCA9544A::connected()
{
	_i2cPort.beginTransmission(_address);
	uint8_t retval = _i2cPort.endTransmission();

	return !retval;
}

bool TCA9544A::setChannel(uint8_t channel)
{
	const uint8_t controlRegister = 0x04 | channel;
	if (controlRegister == _controlRegister)
	{
		return true;
	}
	_i2cPort.beginTransmission(_address);
	_i2cPort.write(controlRegister);
	if (_i2cPort.endTransmission() != 0)
	{
		return false; // Device did not ACK
	}
	_controlRegister = controlRegister;
	return true;
}

bool TCA9544A::clearChannels()
{
	_i2cPort.beginTransmission(_address);
	_i2cPort.write(0);
	if (_i2cPort.endTransmission() != 0)
	{
		return false; // Device did not ACK
	}
	_controlRegister = 0;
	return true;
}

uint8_t TCA9544A::readControlRegister()
{
	_i2cPort.requestFrom(_address, 1U);
	return _i2cPort.read();
}