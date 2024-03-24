#pragma once
#include "StreamConductor.hpp"

#define HIT_PERFECT 0
#define HIT_GOOD 1
#define HIT_BAD 2


class CrosshairMetronome
{
private:
    StreamConductor conductor;
    float lastbeat;
    Sound se_bad;
    Sound se_good;
    Sound se_perfect;
    Rectangle rect;

public:
    CrosshairMetronome();
    CrosshairMetronome(StreamConductor c);
    ~CrosshairMetronome();
    void Update();
    void Draw();
    float GetErrorRange();
    int CheckInRange();
    void PlayPerfect();
    void PlayGood();
    void PlayBad();
};

