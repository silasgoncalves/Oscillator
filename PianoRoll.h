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

#ifndef PIANO_ROLL_H
#define PIANO_ROLL_H

#include "common.h"
#include "Generator.h"
#include "Mixer.h"
#include "Tuning.h"
#include "Shifter.h"
#include "Gate.h"

struct Note {
	unsigned int key;
	unsigned int duration;

	Note(unsigned int key, unsigned int duration);
	Note(unsigned int key, float duration, unsigned int sampleRate);
};

class PianoRoll : public Generator {
	private:
		std::shared_ptr<Generator> instrument;
		std::map<unsigned int, std::vector<Note>> notes;
		unsigned int numNotes;

		Tuning tuning;

		std::shared_ptr<Mixer> mixer;
	public:
		PianoRoll(std::shared_ptr<Generator> instrument);

		virtual std::shared_ptr<Generator> clone() const;
		std::shared_ptr<PianoRoll> sclone() const;

		std::vector<Note> getNotes(unsigned int n);

		void addNoteSample(unsigned int n, Note note, unsigned int sampleRate);
		void addNote(float t, Note note, unsigned int sampleRate);

		virtual sf::Int16 getSample(float t, unsigned int sampleRate, unsigned int bufferSize);
		virtual void fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition);
};

#endif

