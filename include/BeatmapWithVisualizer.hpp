#pragma once
#include <vector>
#include "StreamConductor.hpp"

#define HIT_PERFECT 0
#define HIT_GOOD 1
#define HIT_BAD 2

enum BEATMAP_EVENT_TYPE {
    NOTE,
    NEW_BPM,
    NEW_TIME_SIG
};

// TODO: Probably make a subclass of events (also make an event struct)
struct Beatmap_Note {
    int type;           // always 0
    float seconds;      // time to trigger this note
    int note_type;      // for now, always 1 (would be 2/3 for a hold/other button)
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
    void Update();
    void Draw();
    float GetErrorRange();
    int CheckInRange();
    float GetMetronomeOffset();
};