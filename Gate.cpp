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

#include "Gate.h"

using namespace std;

Gate::Gate(shared_ptr<Generator> source, float start, float end) {
	this->source = source;
	this->start = start;
	this->end = end;
}

shared_ptr<Generator> Gate::clone() const {
	return sclone();
}

shared_ptr<Gate> Gate::sclone() const {
	shared_ptr<Gate> ptr = make_shared<Gate>(source, start, end);
	ptr->freq = freq;
	return ptr;
}

sf::Int16 Gate::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	return (t < start || t > end) ? 0 : source->getSample(t, sampleRate, bufferSize);
}

void Gate::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	if (t < start || t > end) {
		if (!addition) {
			for (unsigned int n = 0; n < bufferSize; n++) {
				buffer[n] = 0;
			}
		}
	}
	else source->fillBuffer(buffer, t, sampleRate, bufferSize, addition);
}

