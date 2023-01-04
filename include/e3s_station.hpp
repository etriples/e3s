#ifndef E3S_STATION_HPP
#define E3S_STATION_HPP

#include "e3s.hpp"
#include "e3s_image.hpp"

#define E3S_STATION_SUCCESSFUL_MISSIONS_REQUIRED 30

class e3s_shuttle_t;


class e3s_station_t{

public:
    static const uint32_t E3S_STATION_ENERGY_MAX{10'000'000};
    static const uint16_t E3S_STATION_WATER_MAX{10'000};
    static const uint16_t E3S_STATION_FOOD_MAX{1'000};
    static const uint16_t E3S_STATION_OXYGEN_MAX{10'000};
    static const uint8_t E3S_STATION_SHUTTLES_MAX{6};
    static const uint32_t E3S_STATION_ENERGY_MIN{100'000};
    static const uint16_t E3S_STATION_WATER_MIN{1000};
    static const uint16_t E3S_STATION_FOOD_MIN{100};
    static const uint16_t E3S_STATION_OXYGEN_MIN{1'000};

private:
    e3s_image_t* background;
    std::atomic<uint32_t> energy;
    std::atomic<uint16_t> food;
    std::atomic<uint16_t> water;
    std::atomic<uint16_t> oxygen;
    std::atomic<e3s_shuttle_t**> shuttles; // 6 park slots
    std::atomic<uint16_t> pending_shuttles_amount;
    std::atomic<float> shuttle_interest;
    std::atomic<uint16_t> successful_missions;

public:

    e3s_station_t(uint32_t energy_p,
                  uint16_t food_p,
                  uint16_t water_p,
                  uint16_t oxygen_p);

    uint32_t get_energy() const;
    void increase_energy(uint32_t energy_p);
    void decrease_energy(uint32_t energy_p);

    uint16_t get_food() const;
    void increase_food(uint16_t food_p);
    void decrease_food(uint32_t food_p);

    uint16_t get_water() const;
    void increase_water(uint16_t water_p);
    void decrease_water(uint32_t water_p);

    uint16_t get_oxygen() const;
    void increase_oxygen(uint16_t oxygen_p);
    void decrease_oxygen(uint32_t oxygen_p);

    uint16_t get_successful_missions() const;
    void    increase_successful_missions();

    e3s_shuttle_t**  get_shuttles() ;
    e3s_image_t* const get_background() const;
    float get_shuttle_interest() const;
    void set_shuttle_interest(float interest);
    uint16_t get_pending_shuttles_amount() const;
    void set_pending_shuttles_amount(uint16_t amount);



    ~e3s_station_t();
};


#endif