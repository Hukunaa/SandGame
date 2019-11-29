#pragma once
#include <Particle.h>
#include <mutex>

class Particle;

struct ArrData
{
    std::mutex mtx;
    Particle* part;
};

