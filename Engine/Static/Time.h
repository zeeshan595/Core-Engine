#ifndef _TIME
#define _TIME

class Time
{
public:
    static float            last_frame_time;
    static float            current_time;
    static float            delta_time;

};
float           Time::last_frame_time     = 0;
float           Time::current_time        = 0;
float           Time::delta_time          = 0;

#endif