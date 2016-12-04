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

#ifndef BASIC_GENERATOR_H
#define BASIC_GENERATOR_H

#include "common.h"
#include "Generator.h"

enum Shape {
	SINE,
	SAW,
	SQUARE,
	NOISE
};

class BasicGenerator : public Generator {
	private:
		Shape shape;
		unsigned int ampl;
	public:
		BasicGenerator();
		BasicGenerator(Shape shape, float freq, unsigned int ampl);

		virtual std::shared_ptr<Generator> clone() const;
		std::shared_ptr<BasicGenerator> sclone() const;
		
		Shape getShape();
		void setShape(Shape shape);
		unsigned int getAmpl();
		void setAmpl(unsigned int ampl);

		virtual sf::Int16 getSample(float t, unsigned int sampleRate, unsigned int bufferSize);
};

#endif

