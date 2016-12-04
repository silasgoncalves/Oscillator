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

#include "Sample.h"

using namespace std;

Sample::Sample(string filename) {
	this->filename = filename;
	soundBuffer.loadFromFile(filename);
}

std::shared_ptr<Generator> Sample::clone() const {
	return sclone();
}

std::shared_ptr<Sample> Sample::sclone() const {
	std::shared_ptr<Sample> ptr = make_shared<Sample>(filename);
	return ptr;
}

sf::Int16 Sample::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	unsigned int index = t * soundBuffer.getSampleRate();	
	if (index < soundBuffer.getSampleCount()) return soundBuffer.getSamples()[index];
	else return 0;
}

void Sample::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	/* WARNING : assuming same sample rate */	
	unsigned int n0 = t * soundBuffer.getSampleRate();
	const sf::Int16* src = soundBuffer.getSamples();
	for (unsigned int n = 0; n < bufferSize; n++) {
		sf::Int16 val = (n0 + n < soundBuffer.getSampleCount()) ? src[n0 + n] : 0;
		if (addition) buffer[n] += val;
		else buffer[n] = val;
	}
}

