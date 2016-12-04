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

#ifndef GENERATOR_H
#define GENERATOR_H

#include "common.h"

class Generator {
	protected:
		float freq;
	public:
		virtual std::shared_ptr<Generator> clone() const = 0;
		virtual sf::Int16 getSample(float t, unsigned int sampleRate, unsigned int bufferSize) = 0;
		virtual void fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition=false);

		virtual float getFreq();
		virtual void setFreq(float freq);
};

#endif

