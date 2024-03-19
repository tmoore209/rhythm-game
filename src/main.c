#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct rect {
    int x;
    int y;
    int w;
    int h;
} rect;

rect target_rect;
rect moving_rect;

Sound se_met;
Sound se_bad;
Sound se_good;
Sound se_perfect;

void InitAudio(){
    InitAudioDevice();
    se_met = LoadSound("sfx/metronome.wav");
    se_bad = LoadSound("sfx/game_button.mp3");
    se_good = LoadSound("sfx/good.mp3");
    se_perfect = LoadSound("sfx/perfect.mp3");
}

int main() {
    float metronome_per_beat = 4;
    float BPM = 20;
    float BPS = BPM/60;
    float FPS = 60;
    int FPB = FPS/(BPS);
    int frame_per_met = FPS / (BPS * metronome_per_beat);

    int current_beatframe = 0;

    target_rect.w = 40;
    target_rect.h = 80;
    target_rect.x = SCREEN_WIDTH/2 - target_rect.w/2;
    target_rect.y = SCREEN_HEIGHT/2 - target_rect.h/2;

    moving_rect.w = 40;
    moving_rect.h = 80;
    moving_rect.y = target_rect.y;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "words");
    InitAudio();
    SetTargetFPS(FPS);
    char pos_text[256];

    int foo = 1;

    //PlaySound(se_met);

    while (!WindowShouldClose()) {
        BeginDrawing();
        //DrawFPS(0,0);

        if (foo)
        {
            // Do Sounds
            if ((current_beatframe % frame_per_met) == 0) {
                printf("Beep\n");
                PlaySound(se_met);
                //foo = 0;
            }
        }

        // Draw Background
        if ((current_beatframe - 1) % FPB == 0) {
            ClearBackground(RED);
        }
        else if ((current_beatframe) % FPB == 0) {
            ClearBackground(GREEN);
        }
        else if ((current_beatframe + 1) % FPB == 0) {
            ClearBackground(RED);
        }
        else {
            ClearBackground(BLUE);
        }

        // Draw Objects
        //moving_rect.x = SCREEN_WIDTH * (current_beatframe / (2*FPB) - FPB);
        moving_rect.x = ((SCREEN_WIDTH/FPB) * ((current_beatframe + FPB/2)% FPB));
        moving_rect.x += moving_rect.w/2;
        DrawRectangle(target_rect.x, target_rect.y, target_rect.w, target_rect.h, BLACK);
        DrawRectangle(moving_rect.x, moving_rect.y, moving_rect.w, moving_rect.h, WHITE);

        sprintf(pos_text, "%d", current_beatframe % FPB);
        DrawText(pos_text, 0, 0, 12, WHITE);

        EndDrawing();
        current_beatframe++;
    }
    CloseWindow();
    printf("FPB = %d\n", FPB);
}
