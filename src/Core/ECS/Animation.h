#pragma once

struct Animation {
    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(int idx, int _frames, int _speed):
        index(idx),
        frames(_frames),
        speed(_speed)
    {}
};