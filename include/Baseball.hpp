#pragma once
#include "StreamConductor.hpp"
#include <vector>
#include "BeatmapNoteType.hpp"

#define BB_STATE_REST 0
#define BB_STATE_SHORT_LAUNCH 1
#define BB_STATE_LONG_LAUNCH 2
#define BB_STATE_PERFECT 3
#define BB_STATE_GOOD 4
#define BB_STATE_MISS 5

class Baseball
{

typedef struct {
    float timestamp;
    Vector2 position;
} path_node;

typedef struct {
    std::vector<path_node> nodes;

    float get_total_time() {
        return nodes.back().timestamp;
    }
} path;

private:
    Texture texture;
    Rectangle size = {0, 0, 16, 16}; // Width and height of a single drawing
    float elapsed_time = 0;

    // seconds per beat = 0.5714285714285714
    path short_launch = { {
        path_node {0,                  Vector2 {285, 404} },
        path_node {0.2857142857142857, Vector2 {370, 197} },
        path_node {0.5714285714285714, Vector2 {402, 285} },
    } };
    path long_launch = {{
        path_node {0,                  Vector2 {285, 404} },
        path_node {0.5714285714285714, Vector2 {370, 16} },
        path_node {1.1428571428571428, Vector2 {402, 285} },
    } };
    // Path perfect;
    // Path good;
    // Path miss;

    // int state = BB_STATE_SHORT_LAUNCH;
    int state = BB_STATE_REST;
    void Anim_Reset();
    void _Draw_launch();
    void _Draw_perfect();
    void _Draw_good();
    void _Draw_miss();
    Vector2 FindPosition();

public:
    Baseball();
    ~Baseball();
    void Update(Beatmap_Note_Type cue);
    void Draw();
    void PlayPerfect();
    void PlayGood();
    void PlayBad();
};

