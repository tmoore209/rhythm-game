#pragma once
#include <vector>
#include "StreamConductor.hpp"
#include "BeatmapNoteType.hpp"

#define HIT_PERFECT 0
#define HIT_GOOD 1
#define HIT_BAD 2

enum BEATMAP_EVENT_TYPE {
    NOTE,
    CUE_A,
    CUE_B,
    CUE_C,
    CUE_D,
    NEW_BPM,
    NEW_TIME_SIG
};

// TODO: Probably make a subclass of events (also make an event struct)
struct Beatmap_Note {
    float seconds; // time to trigger this note
    Beatmap_Note_Type type;
    bool triggered = false;
};

class BeatmapWithVisualizer
{
private:
    // Credits type stuff
    char* header_title;
    char* header_composer;
    char* header_vocals;
    char* header_original;
    char* header_mapper;

    // Important type stuff
    // float header_bpm;
    // float header_offset;
    float metronome_offset;
    // TODO: Probably change to events
    std::vector<Beatmap_Note> notes;

    StreamConductor* conductor;
    float lastbeat;

public:
    BeatmapWithVisualizer();
    BeatmapWithVisualizer(StreamConductor* conductor, char* path);
    ~BeatmapWithVisualizer();
    Beatmap_Note_Type Update(); // Return any cues (i.e. launch ball)
    void Draw();
    float GetErrorRange();
    int CheckInRange();
    float GetMetronomeOffset();
};