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

#include "Shifter.h"

using namespace std;

Shifter::Shifter(shared_ptr<Generator> source, float shift) {
	this->source = source;
	this->shift = shift;
}

shared_ptr<Generator> Shifter::clone() const {
	return sclone();
}

shared_ptr<Shifter> Shifter::sclone() const {
	shared_ptr<Shifter> ptr = make_shared<Shifter>(source, shift);
	ptr->freq = freq;
	return ptr;
}

sf::Int16 Shifter::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	return (t < shift) ? 0 : source->getSample(t - shift, sampleRate, bufferSize);
}

void Shifter::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	if (t < shift) {
		if (!addition) {
			for (unsigned int n = 0; n < bufferSize; n++) {
				buffer[n] = 0;
			}
		}
	}
	else source->fillBuffer(buffer, t - shift, sampleRate, bufferSize, addition);
}

