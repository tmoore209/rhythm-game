#pragma once
#include <raylib.h>
#include <StreamConductor.hpp>

class Metronome
{
private:
    StreamConductor conductor;
    float lastbeat;
    Sound sound;

public:
    Metronome();
    Metronome(StreamConductor conductor);
    ~Metronome();

    void Update();

};


