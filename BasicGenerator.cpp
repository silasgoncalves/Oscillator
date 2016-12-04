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

#include "BasicGenerator.h"

using namespace std;

BasicGenerator::BasicGenerator() {
	this->shape = SINE;
	this->freq = 440.;
	this->ampl = 30000;	
}

BasicGenerator::BasicGenerator(Shape shape, float freq, unsigned int ampl) {
	this->shape = shape;
	this->freq = freq;
	this->ampl = ampl;
}

shared_ptr<Generator> BasicGenerator::clone() const {
	return sclone();
}

shared_ptr<BasicGenerator> BasicGenerator::sclone() const {
	shared_ptr<BasicGenerator> ptr = make_shared<BasicGenerator>();
	ptr->freq = freq;
	ptr->shape = shape;
	ptr->freq = freq;
	ptr->ampl = ampl;
	return ptr;
}

Shape BasicGenerator::getShape() {
	return shape;	
}

void BasicGenerator::setShape(Shape shape) {
	this->shape = shape;
}

unsigned int BasicGenerator::getAmpl() {
	return ampl;
}

void BasicGenerator::setAmpl(unsigned int ampl) {
	this->ampl = ampl;
}

sf::Int16 BasicGenerator::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	switch (shape) {
		case SINE:
			return ampl * sin(TWO_PI * freq * t);
		case SAW:
			return ampl * (fmod(t * freq, 1 / freq) * 2 - 1);
		case SQUARE:
			return (fmod(t * freq, 1 / freq) < 0.5) ? ampl : -ampl;
		case NOISE:
			return ampl * (rand() % 3 - 1);
		default:
			return 0;
	}
}

