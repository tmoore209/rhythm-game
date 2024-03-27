#include <stdio.h>
#include <raylib.h>
#include "StreamConductor.hpp"
#include "Metronome.hpp"
#include "CrosshairMetronome.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Batter.hpp"
#include "Baseball.hpp"

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
#include <stdlib.h>
void initialize_demo(){
    // Music
    char* path = "music/airbatter.ogg";
    conductor = StreamConductor(path);
    beatmap = BeatmapWithVisualizer(&conductor, "beatmaps/airbatter-shortlong-quantized.bm");

    metronome = Metronome(&conductor, beatmap.GetMetronomeOffset());
    crosshair = CrosshairMetronome(&conductor, beatmap.GetMetronomeOffset());
    
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

    Batter batter;
    Baseball baseball;

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
        Beatmap_Note_Type cue = beatmap.Update();
        crosshair.Update();
        batter.Update();
        baseball.Update(cue);

        if (IsKeyPressed(KEY_SPACE)) {
            batter.Swing();

            int result = beatmap.CheckInRange();
            if (result == HIT_PERFECT) {
                crosshair.PlayPerfect();
                baseball.PlayPerfect();
            }

            else if (result == HIT_GOOD) {
                crosshair.PlayGood();
                baseball.PlayGood();
            }

            else if (result == HIT_BAD){
                crosshair.PlayBad();
                baseball.PlayBad();
            }
        }
    
        if (IsKeyPressed(KEY_M)) {
            SetMusicVolume(conductor.GetStream(), 0);
        }

        BeginDrawing(); 
        // DrawFPS(0,0);

        char mousepos[16] = {};
        int mx = GetMouseX();
        int my = GetMouseY();
        sprintf(mousepos, "%d %d", mx, my);
        DrawText(mousepos, 0, 100, 16, WHITE);

        // Draw background
        ClearBackground(BLUE);

        // Draw Objects
        DrawRectangleRec(target_rect, BLACK);
        crosshair.Draw();
        beatmap.Draw();
        batter.Draw();
        baseball.Draw();

        EndDrawing();
    }
    CloseWindow();
}
