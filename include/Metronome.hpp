#pragma once
#include <raylib.h>
#include <StreamConductor.hpp>

class Metronome
{
private:
    StreamConductor* conductor;
    float lastbeat;
    float offset;
    Sound sound;

public:
    Metronome();
    Metronome(StreamConductor* conductor, float offset=0);
    ~Metronome();

    void Update();

};


