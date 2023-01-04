#include "../include/e3s_shuttle_raider.hpp"
#include "../include/e3s_controller.hpp"

e3s_shuttle_raider_t::e3s_shuttle_raider_t(uint8_t park_slot){

    this->type = RAIDER;

    this->park_slot = park_slot;

    switch((park_slot-1)  % 3){

        case 0:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_raider_small.png");
            break;
        case 1:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_raider_medium.png");
            break;
        case 2:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_raider_large.png");
            break;

    }
}

void e3s_shuttle_raider_t::launch_action(){

    if((std::rand()/(float)RAND_MAX) <= this->get_success_rate() ){
        // This is bad
        e3s_controller.get_station().decrease_energy(rand() % e3s_station_t::E3S_STATION_ENERGY_MIN );
        e3s_controller.get_station().decrease_oxygen(rand() % e3s_station_t::E3S_STATION_OXYGEN_MIN );
        e3s_controller.get_station().decrease_water(rand() % e3s_station_t::E3S_STATION_WATER_MIN );
        e3s_controller.get_station().decrease_food(rand() % e3s_station_t::E3S_STATION_FOOD_MIN );
        e3s_controller.display_device.print_cmd_output(232,255,"Raiders have stolen some of your resources :(");

    }else{
        e3s_controller.display_device.print_cmd_output(28,255,"Raiders are kicked out without a harm to the station");
    }


}

// They being successful is bad for the station :)
float e3s_shuttle_raider_t::get_success_rate() const {

    float shuttle_interest = e3s_controller.get_station().get_shuttle_interest();

    return (1.0 - shuttle_interest);
}