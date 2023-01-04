#include "../include/e3s_shuttle_supply.hpp"
#include "../include/e3s_controller.hpp"

e3s_shuttle_supply_t::e3s_shuttle_supply_t(uint8_t park_slot){

    this->type = SUPPLY;
    this->park_slot = park_slot;


    supplies = std::tuple<uint32_t,uint16_t,uint16_t,uint16_t>(  (rand() % (E3S_SHUTTLE_ENERGY_MAX - E3S_SHUTTLE_ENERGY_MIN))  + E3S_SHUTTLE_ENERGY_MIN,\
                                 (rand() % (E3S_SHUTTLE_FOOD_MAX -  E3S_SHUTTLE_FOOD_MIN)) + E3S_SHUTTLE_FOOD_MIN , \
                                 (rand() % (E3S_SHUTTLE_WATER_MAX - E3S_SHUTTLE_WATER_MIN)) + E3S_SHUTTLE_WATER_MIN, \
                                 (rand() % (E3S_SHUTTLE_OXYGEN_MAX - E3S_SHUTTLE_OXYGEN_MIN)) + E3S_SHUTTLE_OXYGEN_MIN);

    switch((park_slot-1)  % 3){

        case 0:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_supply_small.png");
            break;
        case 1:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_supply_medium.png");
            break;
        case 2:
            outer_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_supply_large.png");
            break;

    }


}

std::tuple<uint32_t, uint16_t, uint16_t, uint16_t>& e3s_shuttle_supply_t::get_supplies(){return supplies;}

float e3s_shuttle_supply_t::get_success_rate() const{

    return  (get_energy()/ (float)E3S_SHUTTLE_ENERGY_MAX)*0.50 + (get_food()/ (float)E3S_SHUTTLE_FOOD_MAX)*0.10 + (get_water() / (float)E3S_SHUTTLE_WATER_MAX)*0.15 + (get_oxygen()/(float)E3S_SHUTTLE_OXYGEN_MAX)*0.25;
}

e3s_shuttle_supply_t::~e3s_shuttle_supply_t(){


}

void e3s_shuttle_supply_t::launch_action(){
    float shuttle_interest = e3s_controller.get_station().get_shuttle_interest();

    if((std::rand()/(float)RAND_MAX) <= this->get_success_rate() ){
        e3s_controller.display_device.print_cmd_output(28,255,"Supply shuttle has finished its mission successfully after launch");
        e3s_controller.get_station().set_shuttle_interest(shuttle_interest + 0.05);
        e3s_controller.get_station().increase_successful_missions();
    }else{
        e3s_controller.display_device.print_cmd_output(160,255,"Supply shuttle has failed its mission after launch");
        e3s_controller.get_station().set_shuttle_interest(shuttle_interest - ((logf(shuttle_interest+1.0)/2.0)  ));

    }
}