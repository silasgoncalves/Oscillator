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

#include "LowPass.h"

using namespace std;

LowPass::LowPass(shared_ptr<Generator> source, float cutOff) {
	this->source = source;
	this->cutOff = cutOff;
}

shared_ptr<Generator> LowPass::clone() const {
	return sclone();
}

shared_ptr<LowPass> LowPass::sclone() const {
	shared_ptr<LowPass> ptr = make_shared<LowPass>(source, cutOff);
	ptr->freq = freq;
	return ptr;
}

shared_ptr<Generator> LowPass::getSource() {
	return source;
}

void LowPass::setSource(shared_ptr<Generator> source) {
	this->source = source;
}

float LowPass::getCutOff() {
	return cutOff;
}

void LowPass::setCutOff(float cutOff) {
	this->cutOff = cutOff;
}

sf::Int16 LowPass::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	sf::Int16* buf = new sf::Int16[bufferSize];
	float bufferDuration = bufferSize / sampleRate;
	fillBuffer(buf, t / bufferDuration, sampleRate, bufferSize, false);
	sf::Int16 val = buf[(unsigned int) (fmod(t, bufferDuration) * sampleRate)];
	delete buf;
	return val;
}

void LowPass::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	sf::Int16* srcBuf = new sf::Int16[bufferSize];
	source->fillBuffer(srcBuf, t, sampleRate, bufferSize, false);
	buffer[0] = srcBuf[0];
	for (unsigned int n = 1; n < bufferSize; n++) {
		float dt = 1. / ((float) sampleRate);
		float alpha = dt / ((1. / cutOff) + dt);
		sf::Int16 val = buffer[n-1] + alpha * (srcBuf[n] - buffer[n-1]);
		if (addition) buffer[n] += val;
		else buffer[n] = val;
	}
}

