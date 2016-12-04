/*

    This file is part of Oscillator.
	Copyright 2016 Raphaël Dujardin.

    Oscillator is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Oscillator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Oscillator.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Generator.h"

using namespace std;

void Generator::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	unsigned int n;
	float toff;
	for (n = 0, toff = t; n < bufferSize; n++, toff += 1. / sampleRate) {
		if (!addition)
			buffer[n] = getSample(toff, sampleRate, bufferSize);
		else
			buffer[n] += getSample(toff, sampleRate, bufferSize);
	}
}

float Generator::getFreq() {
	return freq;
}

void Generator::setFreq(float freq) {
	this->freq = freq;
}

