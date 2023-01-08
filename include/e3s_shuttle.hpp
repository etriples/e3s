#ifndef E3S_SHUTTLE_HPP
#define E3S_SHUTTLE_HPP

#include "e3s.hpp"
#include "e3s_crew.hpp"
#include "e3s_image.hpp"

enum e3s_shuttle_type_t{
    VISITOR,
    SUPPLY,
    RAIDER
};


class e3s_shuttle_t {


protected:
    e3s_image_t* outer_view;
    e3s_image_t* inner_view;
    uint32_t energy;
    uint16_t food;
    uint16_t water;
    uint16_t oxygen;
    std::vector <e3s_crew_t> crew;
    uint16_t crew_size;
    uint8_t park_slot; // implement
    e3s_shuttle_type_t type;

public:
    static const uint32_t E3S_SHUTTLE_ENERGY_MAX{1'000'000};
    static const uint16_t E3S_SHUTTLE_WATER_MAX{1'000};
    static const uint16_t E3S_SHUTTLE_FOOD_MAX{100};
    static const uint16_t E3S_SHUTTLE_OXYGEN_MAX{1'000};
    static const uint16_t E3S_SHUTTLE_CREW_MAX{20};
    static const uint32_t E3S_SHUTTLE_ENERGY_MIN{10'000};
    static const uint16_t E3S_SHUTTLE_WATER_MIN{100};
    static const uint16_t E3S_SHUTTLE_FOOD_MIN{10};
    static const uint16_t E3S_SHUTTLE_OXYGEN_MIN{100};
    static const uint16_t E3S_SHUTTLE_CREW_MIN{5};
    uint32_t get_energy() const;
    uint32_t increase_energy(uint32_t i);

    uint16_t get_food() const;
    uint16_t increase_food(uint16_t i);

    uint16_t get_water() const;
    uint16_t increase_water(uint16_t i);

    std::vector<e3s_crew_t>& get_crew();

    uint16_t get_crew_size() const;

    uint16_t get_oxygen() const;
    uint16_t increase_oxygen(uint16_t i);

    e3s_shuttle_type_t get_shuttle_type() const;

    virtual float get_success_rate() const = 0;

    virtual void launch_action() = 0;


    e3s_shuttle_t(); // randomizes energy, food and water with minimal values

    virtual ~e3s_shuttle_t(); // deallocates crew pointer

    e3s_image_t* const get_outer_view() const;
    e3s_image_t* const get_inner_view() const;

    uint8_t get_park_slot() const;


};

#endif
