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

#include "Stream.h"

using namespace std;

Stream::Stream(unsigned int bufferSize, unsigned int sampleRate) {
	this->bufferSize = bufferSize;
	this->sampleRate = sampleRate;
	buffer = new sf::Int16[bufferSize];
	timeOffset = 0.0;
	stillGen = 0;
	unsigned int channelCount = 1;
	initialize(channelCount, this->sampleRate);
}

Stream::~Stream() {
	delete buffer;
}

void Stream::addGenerator(shared_ptr<Generator> generator) {
	generators.push_back(generator);
	stillGen++;
}

bool Stream::onGetData(Chunk& data) {
	if (stillGen == 0) return false;
	for (unsigned int n = 0; n < bufferSize; n++) {
		buffer[n] = 0;
	}
	for (auto gen : generators) {
		try {
			gen->fillBuffer(buffer, timeOffset, sampleRate, bufferSize, true);
		}
		catch (bool e) {
			stillGen--;
		}
	}
	data.samples = buffer;
	data.sampleCount = bufferSize;
	timeOffset += ((float) bufferSize) / ((float) sampleRate);
	return true;
}

void Stream::onSeek(sf::Time timeOffset) {
	this->timeOffset = timeOffset.asSeconds();
	stillGen = generators.size();
}
