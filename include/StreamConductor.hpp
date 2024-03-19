#pragma once
#include <raylib.h>

class StreamConductor
{
private:
    Music stream;
    float volume = 1.0;
    float bpm;
    float crotchet;  // Length of quarter note
    float offset;    // mp3 only?

    // float met_lastbeat;
    // Sound metronome;

public:
    StreamConductor();
    StreamConductor(char* filename, float bpm);
    ~StreamConductor();
    float GetBpm();
    float GetChrotchet();
    float GetOffset();
    float GetSongTimePosition();
    float GetSongBeatPosition();
    Music GetStream();
    bool IsPlaying();
    void Update();
    void Metronome();
    void Start();
    void Pause();
    void Resume();
    void ChangeVolume(float x);
    void SetVolume(float x);
    int GetInteger();
    float GetFractional();
};
