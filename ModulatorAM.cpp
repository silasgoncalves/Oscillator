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

#include "ModulatorAM.h"

using namespace std;

ModulatorAM::ModulatorAM(shared_ptr<Generator> modulated, shared_ptr<Generator> modulator) {
	this->modulated = modulated;
	this->modulator = modulator;
}

shared_ptr<Generator> ModulatorAM::clone() const {
	return sclone();
}

shared_ptr<ModulatorAM> ModulatorAM::sclone() const {
	shared_ptr<ModulatorAM> ptr = make_shared<ModulatorAM>(modulated, modulator);
	return ptr;
}

sf::Int16 ModulatorAM::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	float ratio = ((float) modulator->getSample(t, sampleRate, bufferSize)) / ((float) 0x7FFF);	
	return modulated->getSample(t, sampleRate, bufferSize) * ratio;
}

void ModulatorAM::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	sf::Int16* modulatedBuf = new sf::Int16[bufferSize];
	sf::Int16* modulatorBuf = new sf::Int16[bufferSize];
	modulated->fillBuffer(modulatedBuf, t, sampleRate, bufferSize, false);
	modulator->fillBuffer(modulatorBuf, t, sampleRate, bufferSize, false);
	for (unsigned int n = 0; n < bufferSize; n++) {
		float ratio = ((float) modulatorBuf[n]) / ((float) 0x7FFF);
		sf::Int16 val = modulatedBuf[n] * ratio;		
		if (addition) {
			buffer[n] += val;
		}
		else {
			buffer[n] = val;
		}
	}
	delete modulatedBuf;
	delete modulatorBuf;
}

