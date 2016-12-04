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

#include "common.h"
#include "BasicGenerator.h"
#include "Stream.h"
#include "LowPass.h"
#include "Mixer.h"
#include "Tuning.h"
#include "PianoRoll.h"
#include "Sample.h"

using namespace std;

int main() {
	const unsigned BUFFER_SIZE = 2048;
	const unsigned SAMPLE_RATE = 44100;

	shared_ptr<BasicGenerator> sine = make_shared<BasicGenerator>(SINE, 440., 10000);

	Tuning tn;
	shared_ptr<Generator> kick = make_shared<Sample>("kick.wav");
	shared_ptr<PianoRoll> seq = make_shared<PianoRoll>(kick);
	for (float t = 0.0; t < 8.0; t+= 0.5) {
		seq->addNote(t, Note(tn.getKey("C0"), 0.5, SAMPLE_RATE), SAMPLE_RATE);
	}

	shared_ptr<PianoRoll> pr = make_shared<PianoRoll>(sine);
	pr->addNote(0.0, Note(tn.getKey("G4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(0.5, Note(tn.getKey("G4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(1.0, Note(tn.getKey("G4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(1.5, Note(tn.getKey("A4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(2.0, Note(tn.getKey("B4"), 0.7, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(3.0, Note(tn.getKey("A4"), 0.7, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(4.0, Note(tn.getKey("G4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(4.5, Note(tn.getKey("B4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(5.0, Note(tn.getKey("A4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(5.5, Note(tn.getKey("A4"), 0.3, SAMPLE_RATE), SAMPLE_RATE);
	pr->addNote(6.0, Note(tn.getKey("G4"), 1.8, SAMPLE_RATE), SAMPLE_RATE);

	shared_ptr<Mixer> mix = make_shared<Mixer>(2);
	mix->getTrack(0).source = pr;
	mix->getTrack(1).source = seq;

	Stream stream(BUFFER_SIZE, SAMPLE_RATE);
	stream.addGenerator(mix);
	stream.play();

	sf::sleep(sf::seconds(8.2));

	return 0;
}

