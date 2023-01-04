#ifndef E3S_SHUTTLE_VISITOR_HPP
#define E3S_SHUTTLE_VISITOR_HPP

#include "e3s.hpp"
#include "e3s_shuttle.hpp"

class e3s_shuttle_visitor_t: public e3s_shuttle_t{

public:
    e3s_shuttle_visitor_t(uint8_t park_slot);
    float get_success_rate() const;
    ~e3s_shuttle_visitor_t();
    void launch_action();

};


#endif