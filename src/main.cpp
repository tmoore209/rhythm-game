#include <stdio.h>
#include <raylib.h>
#include "StreamConductor.hpp"
#include "Metronome.hpp"
#include "CrosshairMetronome.hpp"
#include "BeatmapWithVisualizer.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


StreamConductor conductor;

// Reactive elements
Rectangle target_rect;

Metronome metronome;
CrosshairMetronome crosshair;
BeatmapWithVisualizer beatmap;
//

void InitAudio(){
    InitAudioDevice();
}

void initialize_demo(){
    // Music
    // char* path = "music/i wanna know.mp3";
    // char* path = "music/146bpm.wav";
    char* path = "music/karateman.wav";
    // float bpm = 146;
    // float bpm = 100;
    float bpm = 120;
    float ratio = 1;
    conductor = StreamConductor(path, bpm * ratio);
    SetMusicPitch(conductor.GetStream(), ratio);

    metronome = Metronome(conductor);
    crosshair = CrosshairMetronome(conductor);
    beatmap = BeatmapWithVisualizer(conductor, "beatmaps/karate.bm");
    
}

int main() {
    target_rect.width = 40;
    target_rect.height = 80;
    target_rect.x = SCREEN_WIDTH/2 - target_rect.width/2;
    target_rect.y = SCREEN_HEIGHT/2 - target_rect.height/2;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "maqo's rhythm game");
    InitAudio();
    initialize_demo();
    SetTargetFPS(60);


    conductor.Start();

    while (!WindowShouldClose()) {
        // Move music forward
        if (conductor.IsPlaying()){
            conductor.Update();
        }

        float vol_change = GetMouseWheelMove();
        if (vol_change != 0)
            conductor.ChangeVolume(vol_change * .05);


        // Update Objects
        metronome.Update();
        beatmap.Update();
        crosshair.Update();

        if (IsKeyPressed(KEY_SPACE)) {
            int result = beatmap.CheckInRange();
            if (result == HIT_PERFECT) {
                crosshair.PlayPerfect();
            }

            else if (result == HIT_GOOD) {
                crosshair.PlayGood();
            }

            else if (result == HIT_BAD){
                crosshair.PlayBad();
            }
        }
    
        if (IsKeyPressed(KEY_M)) {
            SetMusicVolume(conductor.GetStream(), 0);
        }

        BeginDrawing(); 
        // DrawFPS(0,0);

        // Draw background
        ClearBackground(BLUE);

        // Draw Objects
        DrawRectangleRec(target_rect, BLACK);
        crosshair.Draw();
        beatmap.Draw();

        EndDrawing();
    }
    CloseWindow();
}
