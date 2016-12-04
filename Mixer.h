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

#ifndef MIXER_H
#define MIXER_H

#include "common.h"
#include "Generator.h"

struct Track {
	std::shared_ptr<Generator> source;

	Track();
	Track(std::shared_ptr<Generator> source);
};

class Mixer : public Generator {
	private:
		std::vector<Track> tracks;
	public:
		Mixer(unsigned int nTracks);

		virtual std::shared_ptr<Generator> clone() const;
		std::shared_ptr<Mixer> sclone() const;

		Track& getTrack(unsigned int index);
		void setTrack(unsigned int index, Track track);

		virtual sf::Int16 getSample(float t, unsigned int sampleRate, unsigned int bufferSize);
		virtual void fillBuffer(sf::Int16* buffer, float t, unsigned int sampleRate, unsigned int bufferSize, bool addition=false);
};

#endif

