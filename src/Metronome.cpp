#include "Metronome.hpp"

Metronome::Metronome() { }
Metronome::~Metronome() { }

Metronome::Metronome(StreamConductor* c) {
    lastbeat = 0;
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