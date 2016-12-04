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

#include "PianoRoll.h"

using namespace std;

Note::Note(unsigned int key, unsigned int duration) {
	this->key = key;
	this->duration = duration;
}

Note::Note(unsigned int key, float duration, unsigned int sampleRate) {
	this->key = key;
	this->duration = duration * sampleRate;
}

PianoRoll::PianoRoll(shared_ptr<Generator> instrument) {
	this->instrument = instrument;	
	this->mixer = make_shared<Mixer>(200);
	numNotes = 0;
}

shared_ptr<Generator> PianoRoll::clone() const {
	return sclone();
}

shared_ptr<PianoRoll> PianoRoll::sclone() const {
	shared_ptr<PianoRoll> ptr = make_shared<PianoRoll>(instrument);
	ptr->freq = freq;
	ptr->notes = notes;
	ptr->numNotes = numNotes;
	ptr->mixer = mixer->sclone();
	return ptr;
}

vector<Note> PianoRoll::getNotes(unsigned int n) {
	if (notes.count(n)) return notes[n];
	else return vector<Note>();
}

void PianoRoll::addNoteSample(unsigned int n, Note note, unsigned int sampleRate) {
	if (numNotes >= 200) throw false;
	shared_ptr<Generator> noteGen = instrument->clone();
	noteGen->setFreq(tuning.getFreq(note.key));
	shared_ptr<Gate> gate = make_shared<Gate>(noteGen, 0, ((float) note.duration) / ((float) sampleRate));
	shared_ptr<Shifter> shifted = make_shared<Shifter>(gate, ((float) n) / ((float) sampleRate));
	mixer->setTrack(numNotes, Track(shifted));
	if (!notes.count(n)) notes[n] = vector<Note>();
	notes[n].push_back(note);
	numNotes++;
}

void PianoRoll::addNote(float t, Note note, unsigned int sampleRate) {
	addNoteSample(t * sampleRate, note, sampleRate);
}

sf::Int16 PianoRoll::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	return mixer->getSample(t, sampleRate, bufferSize);
}

void PianoRoll::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	mixer->fillBuffer(buffer, t, sampleRate, bufferSize, addition);
}

