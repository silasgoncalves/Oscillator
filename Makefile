#
#
#    This file is part of Oscillator.
# 	 Copyright 2016 Raphaël Dujardin.
#
#    Oscillator is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Oscillator is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with Oscillator.  If not, see <http://www.gnu.org/licenses/>.
#
#

all:
	g++ main.cpp Generator.cpp BasicGenerator.cpp Stream.cpp LowPass.cpp Mixer.cpp Tuning.cpp PianoRoll.cpp Shifter.cpp Gate.cpp ModulatorAM.cpp Sample.cpp -o oscillator -lsfml-audio -lsfml-system --std=c++11 -g
