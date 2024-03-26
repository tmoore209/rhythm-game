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
    
    Rectangle source = size;
    source.x = size.width * frame;
    int x = GetScreenWidth() / 2;
    int y = GetScreenHeight() / 2;
    Vector2 position = {x, y};
    DrawTextureRec(texture, source, position, WHITE);

    // Probably use this one for the baseball
    // void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters

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
