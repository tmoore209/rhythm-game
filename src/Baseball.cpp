#include "Baseball.hpp"
#include <raymath.h>
#include "stdio.h"

Baseball::Baseball() {
    texture = LoadTexture("graphics/baseball/ball.png");
}

Baseball::~Baseball() {
    UnloadTexture(texture);
}

void Baseball::Anim_Reset() {
    state = BB_STATE_REST;
    elapsed_time = 0;
}

void Baseball::Update(Beatmap_Note_Type cue) {
    if (cue.main != -1)
        printf("bb cue %d\n", cue.sub);
        
    if (cue.sub == 0) {
        state = BB_STATE_SHORT_LAUNCH;
        elapsed_time = 0;
    }
    else if (cue.sub == 1)
    {
        state = BB_STATE_LONG_LAUNCH;
        elapsed_time = 0;
    }
    
}

float normalize(float a, float b, float x) {
    return (x-a) / (b-a);
}

Vector2 Baseball::FindPosition() {
    // Get relevent path
    path p;
    // printf("state is %d\n", state);
    switch (state)
    {
    case BB_STATE_SHORT_LAUNCH:
        p = short_launch;
        break;

    case BB_STATE_LONG_LAUNCH:
        p = long_launch;
        break;

    default:
        return {0, 0};
        break;
    }

    // Find next point (default to final)
    path_node next = p.nodes.back();
    path_node previous = p.nodes.back();

    for (int i = 0; i < p.nodes.size(); i++) {
        // printf("loop %d\n", i);
        if (p.nodes[i].timestamp > elapsed_time) {
            next = p.nodes[i];
            if (i == 0)
                previous = p.nodes[0];
            else
                previous = p.nodes[i-1];
            break;
        }
    }

    // interpolate between previous and next
    float t = normalize(previous.timestamp, next.timestamp, elapsed_time);
    // printf("t is %f next is %f %f\n", t, next.position.x, next.position.y);
    return Vector2Lerp(previous.position, next.position, t);
}

void Baseball::Draw() {
    
    elapsed_time += GetFrameTime();
    switch (state) {
    case BB_STATE_REST: {
        return;
        break;
    }

    case BB_STATE_SHORT_LAUNCH: {
        if (elapsed_time > short_launch.get_total_time()) {
            elapsed_time -= short_launch.get_total_time();
            // probably transition state here too
            state = BB_STATE_REST;
            printf("reset\n");
        }
        break;
    }
    
    case BB_STATE_LONG_LAUNCH: {
        if (elapsed_time > long_launch.get_total_time()) {
            elapsed_time -= long_launch.get_total_time();
            // probably transition state here too
            state = BB_STATE_REST;
            printf("reset\n");
        }
        break;
    }

    case BB_STATE_PERFECT: {
        return;
        break;
    }

    case BB_STATE_GOOD: {
        return;
        break;
    }

    case BB_STATE_MISS: {
        return;
        break;
    }

    default:
        printf("Invalid BB state\n");
        exit(1);
        break;
    }

    Vector2 pos = FindPosition();
    float SCALE = 2;

    // printf("drawing %f %f\n", pos.x, pos.y);
    DrawTexturePro(texture,
        {0,0,16,16},
        {pos.x, pos.y, size.width * SCALE, size.height * SCALE},
        {0, 0},     // Origin
        0,          // Rotation
        WHITE
    );
}

void Baseball::_Draw_launch() {

}

void Baseball::_Draw_perfect() {

}

void Baseball::_Draw_good() {

}

void Baseball::_Draw_miss() {

}

void Baseball::PlayPerfect() {

}

void Baseball::PlayGood() {

}

void Baseball::PlayBad() {

}
