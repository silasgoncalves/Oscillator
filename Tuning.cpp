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

#include "Tuning.h"

using namespace std;

Tuning::Tuning() {
	freqs[0] = 27.5;
	for (unsigned int i = 1; i < 88; i++) {
		freqs[i] = freqs[i-1] * ROOT_12_2;
	}
	
	names[0] = "A-1";
	names[1] = "A#-1";
	names[2] = "B-1";

	int oct = 0;
	char letter = 'C';
	bool sharp = false;
	for (unsigned int i = 3; i < 88 ; i++) {
		ostringstream oss;
		oss << letter << string((sharp) ? "#" : "") << oct;
		names[i] = oss.str();

		if (!sharp && letter != 'E' && letter != 'B') sharp = true;
		else {
			sharp = false;
			if (letter == 'G') {
				letter = 'A';
			}
			else if (letter == 'B') {
				letter++;
				oct++;
			}
			else letter++;
		}
	}
}

float Tuning::getFreq(unsigned int key) {	
	return (key < 88) ? freqs[key] : 0.0;
}

unsigned int Tuning::getKey(string name) {
	for (unsigned int i = 0; i < 88; i++) {
		if (names[i] == name) {
			return i;
		}
	}
	return 0;
}

float Tuning::getFreq(string name) {
	return getFreq(getKey(name));
}

