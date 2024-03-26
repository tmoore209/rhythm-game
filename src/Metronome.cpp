#include "Metronome.hpp"

Metronome::Metronome() { }
Metronome::~Metronome() { }

Metronome::Metronome(StreamConductor* c, float offset) {
    this->offset = offset;
    lastbeat = offset;
    conductor = c;

    sound = LoadSound("sfx/metronome.wav");
}

void Metronome::Update(){
    float crotchet = conductor->GetChrotchet();
    if (conductor->GetSongTimePosition() > lastbeat + crotchet) {
        PlaySound(sound);
        lastbeat += crotchet;
    }
}