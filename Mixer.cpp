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

#include "Mixer.h"

using namespace std;

Track::Track() {}

Track::Track(shared_ptr<Generator> source) {
	this->source = source;
}

Mixer::Mixer(unsigned int nTracks) {
	tracks.resize(nTracks);
}

shared_ptr<Generator> Mixer::clone() const {
	return sclone();
}

shared_ptr<Mixer> Mixer::sclone() const {
	shared_ptr<Mixer> ptr = make_shared<Mixer>(tracks.size());
	ptr->freq = freq;
	ptr->tracks = tracks;
	return ptr;
}

Track& Mixer::getTrack(unsigned int index) {
	return tracks[index];
}

void Mixer::setTrack(unsigned int index, Track track) {
	tracks[index] = track;
}

sf::Int16 Mixer::getSample(float t, unsigned int sampleRate, unsigned int bufferSize) {
	sf::Int16 val = 0;
	for (auto track : tracks) {
		if (track.source) {
			val += track.source->getSample(t, sampleRate, bufferSize);
		}
	}
}

void Mixer::fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition) {
	if (!addition) {
		for (unsigned int n = 0; n < bufferSize; n++) {
			buffer[n] = 0;
		}
	}
	for (auto track : tracks) {
		if (track.source) {
			track.source->fillBuffer(buffer, t, sampleRate, bufferSize, true);
		}
	}
}

