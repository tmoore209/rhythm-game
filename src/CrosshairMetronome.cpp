#include "CrosshairMetronome.hpp"
#include "stdio.h"

CrosshairMetronome::CrosshairMetronome() {
}

CrosshairMetronome::~CrosshairMetronome() {
}

CrosshairMetronome::CrosshairMetronome(StreamConductor* c, float offset) {
    lastbeat = offset;
    this->offset = offset;
    conductor = c;
    se_bad = LoadSound("sfx/game_button.mp3");
    se_good = LoadSound("sfx/good.mp3");
    se_perfect = LoadSound("sfx/perfect.mp3");

    rect.width = 40;
    rect.height = 80;

}

// Check for timeout and play missed SE
void CrosshairMetronome::Update() {
    float er = GetErrorRange();
    if (conductor->GetSongTimePosition() > lastbeat + er) {
        lastbeat += er;
    }
}

float interpolate(float a, float b, float p) {
    return (b-a) * p + a;
}

void CrosshairMetronome::Draw() {
    int WIDTH = GetScreenWidth();
    int HEIGHT = GetScreenHeight();
    int x_positions[4] = { 
        WIDTH/2 - rect.width/2, // Center
        WIDTH - rect.width,     // Right
        WIDTH/2 - rect.width/2, // Center
        0                       // left
    };
    float beatpos = conductor->GetSongBeatPosition() + offset;
    int rounddown = (int) beatpos;      // previous/current beat
    int roundup = (int) beatpos + 1;    // next beat
    float fractional = beatpos - rounddown; // Percentage along

    // Interpolate from visual position of previous beat to next beat
    float from_pos = x_positions[rounddown % 4];
    float to_pos = x_positions[roundup % 4];
    float x = interpolate(from_pos, to_pos, fractional);

    rect.x = x;
    rect.y = HEIGHT/2 - rect.height/2;
    DrawRectangleRec(rect, WHITE);
}


float CrosshairMetronome::GetErrorRange() {
    // Accuracy for player is within +/- an eighth note
    return conductor->GetChrotchet() / 2;
}



// TODO: Change this to support perfect/good/Bad
int CrosshairMetronome::CheckInRange() {
    // Some nonsense to do modulo on float
    float beatpos = conductor->GetSongBeatPosition();
    float fractional = beatpos - (int)beatpos;
    float pos = ((int)beatpos % 4) + fractional;

    float e = GetErrorRange();

    if (
        // To clap on 1 and 3...
        (( 0 <= pos && pos <= 1 ) && pos <= 0+e/2) ||
        (( 1 <= pos && pos <= 2 ) && pos >= 2-e/2) ||
        (( 2 <= pos && pos <= 3 ) && pos <= 2+e/2) ||
        (( 3 <= pos && pos <= 4 ) && pos >= 4-e/2)
        
    ) {
        return HIT_PERFECT;
    }
    else if (
        // To clap on 1 and 3...
        (( 0 <= pos && pos <= 1 ) && pos <= 0+e) ||
        (( 1 <= pos && pos <= 2 ) && pos >= 2-e) ||
        (( 2 <= pos && pos <= 3 ) && pos <= 2+e) ||
        (( 3 <= pos && pos <= 4 ) && pos >= 4-e)
        
    ) {
        return HIT_GOOD;
    }
    else {
        return HIT_BAD;
    }

}

void CrosshairMetronome::PlayPerfect() {
    PlaySound(se_perfect);
}

void CrosshairMetronome::PlayGood() {
    PlaySound(se_good);
}

void CrosshairMetronome::PlayBad() {
    PlaySound(se_bad);
}
