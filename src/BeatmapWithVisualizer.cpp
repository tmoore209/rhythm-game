#include <stdio.h>
#include <stdlib.h>
#include "BeatmapWithVisualizer.hpp"

BeatmapWithVisualizer::BeatmapWithVisualizer() { }
BeatmapWithVisualizer::~BeatmapWithVisualizer() { }


BeatmapWithVisualizer::BeatmapWithVisualizer(StreamConductor conductor, char* path, float offset) {
    this->conductor = conductor;

    FILE* f = fopen(path, "r");

    bool header_started = false;
    bool header_ended = false;

    // Ignore anything before the heaver
    while (fgetc(f) != '`');

    // Until the end of the heasver
    while (!header_ended) {
        char c = fgetc(f);
        if (c == '`') {
            header_ended = true;
            continue;
        }
        // TODO: Process header
    }


    // Find size of data
    int start = ftell(f);
    fseek(f, 0, SEEK_END);
    int end = ftell(f);
    int size = end-start;
    fseek(f, start, SEEK_SET);

    // Create data array
    char data[size + 1];
    data[size] = 0;
    int result = fread(data, sizeof(char), size, f);

    // Done with file
    fclose(f);

    char* line = data;
    // Find first non-empty line
    while ((++line)[0] == '\n');

    ///////////////////////
    // Process beatmap data
    bool keep_going = true;
    while (keep_going) {

        int command;
        sscanf(line, "%d", &command);
        switch (command) {

            // MICROSECOND NOTE_TYPE    (consumes 3)
            case NOTE: {
                float time;
                int note_type;
                sscanf(line, "%d %f %d", &command, &time, &note_type);
                notes.push_back(Beatmap_Note {NOTE, (time - offset)/1000000, note_type});
                break;
            }
            
            // NEW_BPM                  (consumes 2)
            case NEW_BPM: {
                int new_bpm;
                sscanf(line, "%d %d", &command, &new_bpm);
                break;
            }
            
            // NEW_TIME_SIG             (consumes 2)
            case NEW_TIME_SIG: {
                int new_timesig;
                sscanf(line, "%d %d", &command, &new_timesig);
                break;
            }

            default:
                break;
        }

        // Find next line
        while ((++line)[0] != '\n') {
            // If end of file, end outer-loop
            if (line[0] == 0) {
                keep_going = false;
                break;
            }
        }
    }

    for (size_t i = 0; i < notes.size(); i++) {
        printf("Note at %f\n", notes[i].seconds);
    }
}


void BeatmapWithVisualizer::Update() {
    float er = GetErrorRange();
    if (conductor.GetSongTimePosition() > lastbeat + er) {
        lastbeat += er;
    }
}

void BeatmapWithVisualizer::Draw() {
    float TIME_RANGE = 2;
    float current_time = conductor.GetSongTimePosition();

    std::vector<Beatmap_Note> upcoming_notes;
    for (Beatmap_Note note : notes) {
        if(note.seconds < current_time)
            continue;

        else if ( note.seconds > current_time + TIME_RANGE)
            break;

        else
            upcoming_notes.push_back(note);
    }
    
    DrawRectangle(0,0,40,80, WHITE);

    for (auto note : upcoming_notes) {
        DrawRectangle(
            GetScreenWidth() * (note.seconds - current_time) / TIME_RANGE,
            0, 40, 80, BLACK
        );
    }
}

float BeatmapWithVisualizer::GetErrorRange() {
    // Accuracy for player is within +/- an eighth note
    return conductor.GetChrotchet() / 2;
}

int BeatmapWithVisualizer::CheckInRange() {

    float current_time = conductor.GetSongTimePosition();
    float e = GetErrorRange();
    Beatmap_Note next_note;
    bool found_note = false;

    // Find next note (if any)
    for (auto note : notes) {
        if (note.seconds > current_time - e) {
            next_note = note;
            found_note = true;
            break;
        }
        
    }
    if (!found_note) {
        return HIT_BAD;
    }

    printf("current %f next %f\n", current_time, next_note.seconds );

    // Check if in ranges

    if (abs(current_time - next_note.seconds) < e/2) {
        return HIT_PERFECT;
    }

    if (abs(current_time - next_note.seconds) < e) {
        return HIT_GOOD;
    }

    return HIT_BAD;
}
