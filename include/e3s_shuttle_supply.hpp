#ifndef E3S_SHUTTLE_SUPPLY_HPP
#define E3S_SHUTTLE_SUPPLY_HPP

#include "e3s.hpp"
#include "e3s_shuttle.hpp"

class e3s_shuttle_supply_t: public e3s_shuttle_t{

private:

    std::tuple<uint32_t, uint16_t, uint16_t, uint16_t> supplies;

public:

    float get_success_rate() const;
    std::tuple<uint32_t, uint16_t, uint16_t, uint16_t>& get_supplies();
    void launch_action();
    e3s_shuttle_supply_t(uint8_t park_slot);
    ~e3s_shuttle_supply_t();

};

#endif