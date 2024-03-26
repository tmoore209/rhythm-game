#include <stdio.h>
#include <stdlib.h>
#include "BeatmapWithVisualizer.hpp"
#include <string.h>

BeatmapWithVisualizer::BeatmapWithVisualizer() { }
BeatmapWithVisualizer::~BeatmapWithVisualizer() { }


BeatmapWithVisualizer::BeatmapWithVisualizer(StreamConductor* conductor, char* path) {
    this->conductor = conductor;

    FILE* f = fopen(path, "r");

    // Ignore anything before the header
    while (fgetc(f) != '`');

    // Find size of header
    int start = ftell(f);
    while (fgetc(f) != '`');
    int end = ftell(f);
    int header_size = end-start;
    fseek(f, start, SEEK_SET);

    // Create header array
    char header[header_size + 1];
    header[header_size] = 0;
    fread(header, sizeof(char), header_size, f);

    // Process header array
    char* header_element;
    
    char header_title[32];      // NOT CURRENTLY USED
    int header_bpm;
    char header_composer[32];   // NOT CURRENTLY USED
    char header_vocals[32];     // NOT CURRENTLY USED
    char header_original[32];   // NOT CURRENTLY USED
    char header_mapper[32];     // NOT CURRENTLY USED
    int header_offset = 0;

    if (header_element = strstr(header, "title:")) {
        sscanf(header_element, "title:%s\n", header_title);
    }

    if (header_element = strstr(header, "bpm:")) {
        sscanf(header_element, "bpm: %d\n", &header_bpm);
        conductor->SetBpm(header_bpm);
    }

    if (header_element = strstr(header, "composer:")) {
        sscanf(header_element, "composer:%s\n", header_composer);
    }

    if (header_element = strstr(header, "vocals:")) {
        sscanf(header_element, "vocals:%s\n", header_vocals);
    }

    if (header_element = strstr(header, "original:")) {
        sscanf(header_element, "original:%s\n", header_original);
    }

    if (header_element = strstr(header, "mapper:")) {
        sscanf(header_element, "mapper:%s\n", header_mapper);
    }

    if (header_element = strstr(header, "offset:")) {
        sscanf(header_element, "offset: %d\n", &header_offset);
        // conductor->SetOffset(header_offset);
    }

    // Header over
    /////////////////

    // Find size of data
    start = ftell(f);
    fseek(f, 0, SEEK_END);
    end = ftell(f);
    int data_size = end-start;
    fseek(f, start, SEEK_SET);

    // Create data array
    char data[data_size + 1];
    data[data_size] = 0;
    fread(data, sizeof(char), data_size, f);

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
                notes.push_back(Beatmap_Note {NOTE, (time-header_offset)/1000000, note_type});
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
        // printf("Note at %f\n", notes[i].seconds);
    }
}


void BeatmapWithVisualizer::Update() {
    float er = GetErrorRange();
    if (conductor->GetSongTimePosition() > lastbeat + er) {
        lastbeat += er;
    }
}

void BeatmapWithVisualizer::Draw() {
    float TIME_RANGE = 2;
    float current_time = conductor->GetSongTimePosition();

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
    return conductor->GetChrotchet() / 2;
}

int BeatmapWithVisualizer::CheckInRange() {

    float current_time = conductor->GetSongTimePosition();
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

    // printf("current %f next %f\n", current_time, next_note.seconds );

    // Check if in ranges

    if (abs(current_time - next_note.seconds) < e/2) {
        return HIT_PERFECT;
    }

    if (abs(current_time - next_note.seconds) < e) {
        return HIT_GOOD;
    }

    return HIT_BAD;
}
