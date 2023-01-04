#include "../include/e3s_station.hpp"
#include "../include/e3s_galery.hpp"
#include "../include/e3s_controller.hpp"
#include "../include/e3s_shuttle.hpp"
#include "../include/e3s_image.hpp"

uint32_t e3s_station_t::get_energy() const{return energy;}

uint16_t e3s_station_t::get_food() const{return food;}

uint16_t e3s_station_t::get_water() const{return water;}

uint16_t e3s_station_t::get_oxygen() const{return oxygen;}

void e3s_station_t::increase_energy(uint32_t energy_p){

    if(energy_p >= E3S_STATION_ENERGY_MAX - energy){
        energy = E3S_STATION_ENERGY_MAX;
    }else{
        energy += energy_p;
    }

}

void e3s_station_t::increase_food(uint16_t food_p){

    if(food_p >= E3S_STATION_FOOD_MAX - food){
        food = E3S_STATION_FOOD_MAX;
    }else{
        food += food_p;
    }

}

void e3s_station_t::increase_water(uint16_t water_p){

    if(water_p >= E3S_STATION_WATER_MAX - water){
        water = E3S_STATION_WATER_MAX;
    }else{
        water += water_p;
    }

}

void e3s_station_t::increase_oxygen(uint16_t oxygen_p){

    if(oxygen_p >= E3S_STATION_OXYGEN_MAX - oxygen){
        oxygen = E3S_STATION_OXYGEN_MAX;
    }else{
        oxygen += oxygen_p;
    }
}

void e3s_station_t::decrease_energy(uint32_t energy_p){

    if(energy < energy_p){
        energy = 0;
    }else{
        energy -= energy_p;
    }

}

void e3s_station_t::decrease_food(uint32_t food_p){

    if(food < food_p){
        food = 0;
    }else{
        food -= food_p;
    }

}

void e3s_station_t::decrease_water(uint32_t water_p){

    if(water < water_p){
        water = 0;
    }else{
        water -= water_p;
    }

}

void e3s_station_t::decrease_oxygen(uint32_t oxygen_p){

    if(oxygen < oxygen_p){
        oxygen = 0;
    }else{
        oxygen -= oxygen_p;
    }

}


uint16_t e3s_station_t::get_pending_shuttles_amount() const{
    return this->pending_shuttles_amount;
}

void e3s_station_t::set_pending_shuttles_amount(uint16_t amount){
    this->pending_shuttles_amount = amount;
}

float e3s_station_t::get_shuttle_interest() const{
    return this->shuttle_interest;
}

void e3s_station_t::set_shuttle_interest(float interest){
    if(interest < 0)
        this->shuttle_interest = 0;
    else if(interest > 1)
        this->shuttle_interest = 1;
    else
        this->shuttle_interest = interest;
}


uint16_t e3s_station_t::get_successful_missions() const{
    return this->successful_missions;
}

void e3s_station_t::increase_successful_missions(){
    this->successful_missions++;
}


e3s_station_t::e3s_station_t(uint32_t energy_p,
                            uint16_t food_p,
                            uint16_t water_p,
                            uint16_t oxygen_p): /*e3s_drawable_t({"station_bg.png"}, 0),*/ energy{energy_p}, food{food_p}, water{water_p}, oxygen{oxygen_p} {

    this->successful_missions = 0;
    this->pending_shuttles_amount = rand()%5+2;
    this->shuttle_interest = 0.5;

    this->shuttles = new e3s_shuttle_t*[E3S_STATION_SHUTTLES_MAX];

    for(uint8_t i = 0; i < E3S_STATION_SHUTTLES_MAX; i++){
        shuttles[i] = nullptr;
    }

    this->background = (e3s_image_t*)&(e3s_controller.get_galery().get_images().at("station_bg.png"));

}

e3s_station_t::~e3s_station_t(){

    for(uint8_t i = 0; i < E3S_STATION_SHUTTLES_MAX; i++){
        delete shuttles[i];
    }
    delete[] shuttles;

}


e3s_image_t* const e3s_station_t::get_background() const {
    return this->background;
}

e3s_shuttle_t** e3s_station_t::get_shuttles() {
    return this->shuttles;
}


