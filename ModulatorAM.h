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

#ifndef MODULATOR_AM_H
#define MODULATOR_AM_H

#include "common.h"
#include "Generator.h"

class ModulatorAM : public Generator {
	private:
		std::shared_ptr<Generator> modulated;
		std::shared_ptr<Generator> modulator;
	public:
		ModulatorAM(std::shared_ptr<Generator> modulated, std::shared_ptr<Generator> modulator);

		virtual std::shared_ptr<Generator> clone() const;
		std::shared_ptr<ModulatorAM> sclone() const;

		virtual sf::Int16 getSample(float t, unsigned int sampleRate, unsigned int bufferSize);
		virtual void fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition=false);
};

#endif

