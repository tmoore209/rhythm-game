#include "Batter.hpp"
#include "stdio.h"


Batter::Batter() {
    texture = LoadTexture("graphics/baseball/batter.png");
}

Batter::~Batter() {
    UnloadTexture(texture);
}

void Batter::Anim_Reset() {
    frame = 0;
    wait = 0;
    playing = false;
}

void Batter::Update() {
    
}

void Batter::Draw() {
    float scale = 2;

    Rectangle source = size;
    source.x = size.width * frame;
    float x = GetScreenWidth() / 2;
    float y = (GetScreenHeight() / 2) - (scale * size.height / 2);

    DrawTexturePro(texture,
        source,
        {x, y, size.width * scale, size.height * scale},
        {0, 0},     // Origin
        0,          // Rotation
        WHITE
    );

    if (!playing)
        return;

    wait++;

    if(wait == frames_to_wait) {
        frame++;
        wait = 0;
        if (frame == frame_count)
            Anim_Reset();
    }
}

void Batter::Swing() {
    playing = true;
}
