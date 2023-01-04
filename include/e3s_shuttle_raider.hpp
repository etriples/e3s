#ifndef E3S_SHUTTLE_RAIDER_HPP
#define E3S_SHUTTLE_RAIDER_HPP

#include "e3s.hpp"
#include "e3s_shuttle.hpp"

class e3s_shuttle_raider_t: public e3s_shuttle_t{

public:
    void launch_action();
    e3s_shuttle_raider_t(uint8_t park_slot);
    float get_success_rate() const;
};



#endif