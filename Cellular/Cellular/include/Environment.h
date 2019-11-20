#pragma once
class Environment
{
public:
    struct particle_args
    {
        float m_temperature;
        float m_fusion_point;
        float m_viscosity;
        float m_AirDrag;
    };

    static float ambient_temp;
    static float gravity_value;
};

