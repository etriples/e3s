#include "../include/e3s_crew.hpp"
#include "../include/e3s_toolset.hpp"
#include "../include/e3s_controller.hpp"

uint32_t e3s_shuttle_t::get_energy() const{return energy;}

uint16_t e3s_shuttle_t::get_food() const{return food;}

uint16_t e3s_shuttle_t::get_water() const{return water;}

uint16_t e3s_shuttle_t::get_oxygen() const{return oxygen;}

uint16_t e3s_shuttle_t::get_crew_size() const{return crew_size;}

uint32_t e3s_shuttle_t::increase_energy(uint32_t i){

    if(i > E3S_SHUTTLE_ENERGY_MAX - energy){
        uint32_t old_energy = energy;
        energy = E3S_SHUTTLE_ENERGY_MAX;
        return (E3S_SHUTTLE_ENERGY_MAX - old_energy);
    }
    else{
        energy += i;
        return i;
    }

}

uint16_t e3s_shuttle_t::increase_food(uint16_t i){


    if(i >= E3S_SHUTTLE_FOOD_MAX - food){
        uint16_t old_food = food;
        food = E3S_SHUTTLE_FOOD_MAX;
        return (E3S_SHUTTLE_FOOD_MAX - old_food);
    }
    else{
        food += i;
        return i;
    }

}

uint16_t e3s_shuttle_t::increase_water(uint16_t i){


    if(i >= E3S_SHUTTLE_WATER_MAX - water){
        uint16_t old_water = water;
        water = E3S_SHUTTLE_WATER_MAX;
        return (E3S_SHUTTLE_WATER_MAX - old_water);
    }
    else{
        water += i;
        return i;
    }

}

uint16_t e3s_shuttle_t::increase_oxygen(uint16_t i){


    if(i >= E3S_SHUTTLE_OXYGEN_MAX - oxygen){
        uint16_t old_oxygen = oxygen;
        oxygen = E3S_SHUTTLE_OXYGEN_MAX;
        return (E3S_SHUTTLE_OXYGEN_MAX - old_oxygen);
    }
    else{
        oxygen += i;
        return i;
    }

}

e3s_shuttle_type_t e3s_shuttle_t::get_shuttle_type() const{
    return this->type;
}

std::vector<e3s_crew_t>& e3s_shuttle_t::get_crew() { return this->crew;}


e3s_shuttle_t::e3s_shuttle_t() {

    

    std::string name;
    std::string surname;
    std::string nationality;
    uint16_t age;
    std::vector <std::string> names;
    std::vector <std::string> surnames;
    std::vector <std::string> nationalities;
    std::vector <uint16_t> ages;
    uint32_t id = rand() % 100000;
    std::string line;
    uint16_t num_of_lines = 0;

    crew_size = rand() % (E3S_SHUTTLE_CREW_MAX - E3S_SHUTTLE_CREW_MIN) + E3S_SHUTTLE_CREW_MIN;
    std::fstream fio;

    fio.open("../res/crew_db/crew_data.txt", std::ios::in);

    if(!(fio.is_open())){
        e3s_toolset_fatal_exit("Crew data cannot be opened\n");
    }

    while(std::getline(fio, line)){
        num_of_lines++;
    }

    fio.clear();
    fio.seekg(std::ios_base::beg);


    names.resize(num_of_lines);
    surnames.resize(num_of_lines);
    nationalities.resize(num_of_lines);
    ages.resize(num_of_lines);


    uint32_t i = 0;
    while(1){
        fio >> name >> surname >> nationality >> age;
        // std::cout << name << surname << nationality << age << std::endl << "\r";
        if(i < num_of_lines){
            names[i] = name;
            surnames[i] = surname;
            nationalities[i] = nationality;
            ages[i] = age;
            i++;
        }else{
            break;
        }

    }


    uint8_t j = 0;
    this->crew.clear();
    while(j < crew_size){
        e3s_crew_t new_crew_member{names[rand() % i], surnames[rand() % i], nationalities[rand() % i], ages[rand() % i], (bool)(rand()%2), id++,(bool)(rand()%2),(bool)(rand()%2),(bool)(rand()%2) };
        this->crew.push_back(new_crew_member);
        j++;
    }


    fio.close();
    energy = (rand() % (E3S_SHUTTLE_ENERGY_MAX - E3S_SHUTTLE_ENERGY_MIN)) + E3S_SHUTTLE_ENERGY_MIN;
    food = (rand() % (E3S_SHUTTLE_FOOD_MAX - E3S_SHUTTLE_FOOD_MIN)) + E3S_SHUTTLE_FOOD_MIN;
    water = (rand() % (E3S_SHUTTLE_WATER_MAX - E3S_SHUTTLE_WATER_MIN)) + E3S_SHUTTLE_WATER_MIN;
    oxygen = (rand() % (E3S_SHUTTLE_OXYGEN_MAX - E3S_SHUTTLE_OXYGEN_MIN)) + E3S_SHUTTLE_OXYGEN_MIN;


    inner_view = (e3s_image_t*)&e3s_controller.get_galery().get_images().at("shuttle_bg.png");

}

uint8_t e3s_shuttle_t::get_park_slot() const {
    return this->park_slot;
}

e3s_shuttle_t::~e3s_shuttle_t(){


}

e3s_image_t* const e3s_shuttle_t::get_outer_view() const {
    return this->outer_view;
}

e3s_image_t* const e3s_shuttle_t::get_inner_view() const {
    return this->inner_view;
}
