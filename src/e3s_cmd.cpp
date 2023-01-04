#include "../include/e3s_cmd.hpp"
#include "../include/e3s_controller.hpp"
#include "../include/e3s_toolset.hpp"
#include "../include/e3s_shuttle.hpp"
#include "../include/e3s_menu.hpp"
#include "../include/e3s_shuttle_visitor.hpp"
#include "../include/e3s_shuttle_supply.hpp"
#include "../include/e3s_shuttle_raider.hpp"


e3s_cmd_exception_t::e3s_cmd_exception_t(std::string explanation){
    this->explanation = explanation;
}

std::string e3s_cmd_exception_t::get_explanation(){
    return this->explanation;
}



// Station Wrapper Commands

void e3s_cmd_station_go_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1 || !e3s_toolset_is_shuttle_id(args[0])){
        e3s_cmd_show_error("Invalid command arguments");
        return;
    }

    e3s_cmd_station_go(std::stoi(args[0]));
}

void e3s_cmd_station_load_wrapper(const std::vector<std::string>& args) {  // Didn't check args[1]
// || !e3s_toolset_is_shuttle_id(args[0]) || !e3s_toolset_is_number(args[2])){

    static std::map<std::string,uint8_t> resources = {{"energy",0},{"oxygen",1},{"water",2},{"food",3},{"all",4}};


    if (args.size() != 3){ 
        e3s_cmd_show_error("Invalid command arguments, not enough arguments");
        return;
    }
    if(!e3s_toolset_is_number(args[0]) or !e3s_toolset_is_number(args[2])){
        e3s_cmd_show_error("Invalid command arguments, park slot or source amount is not an integer");
    }

    if(resources.find(args[1]) == resources.end() ){
        e3s_cmd_show_error("Invalid command arguments, resource type not found");
    }

    e3s_cmd_station_load(std::stoi(args[0]), resources.at(args[1]), std::stoul(args[2]));
}

void e3s_cmd_station_approve_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 0){
        e3s_cmd_show_error("Invalid command arguments");
        return;
    }

    e3s_cmd_station_approve();
}

void e3s_cmd_station_launch_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1 || !e3s_toolset_is_shuttle_id(args[0])){
        e3s_cmd_show_error("Invalid command arguments");
    }

    e3s_cmd_station_launch(std::stoi(args[0]));
}

void e3s_cmd_station_supply_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1 || !e3s_toolset_is_shuttle_id(args[0])){
        e3s_cmd_show_error("Invalid command arguments");
    }

    e3s_cmd_station_supply(std::stoi(args[0]));
}




// Shuttle Wrapper Commands

void e3s_cmd_shuttle_select_wrapper(const std::vector<std::string>& args) {

    if (args.size() != 2){  // Do we check crew sizes in wrapper or in real function.
        e3s_cmd_show_error("Invalid command arguments");
    }


    // Sending shuttle reference
    if(!e3s_toolset_is_number(args[0])){
        e3s_cmd_show_error("Invalid command arguments");
    }

    uint8_t park_slot = std::stoi(args[args.size()-1]);
    if(!e3s_toolset_is_park_slot(park_slot)){
        e3s_cmd_show_error("Invalid command arguments");
    }
    e3s_shuttle_t& shuttle = *(e3s_controller.get_station().get_shuttles()[park_slot-1]);



    uint16_t crew_id = std::stoi(args[0]);




    e3s_cmd_shuttle_select(shuttle,crew_id);
}

void e3s_cmd_shuttle_list_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1){
        e3s_cmd_show_error("Invalid command arguments");
    }


    // Sending shuttle reference
    if(!e3s_toolset_is_number(args[args.size()-1])){
        e3s_cmd_show_error("Invalid command arguments");
    }
    uint8_t park_slot = std::stoi(args[args.size()-1]);
    if(!e3s_toolset_is_park_slot(park_slot)){
        e3s_cmd_show_error("Invalid command arguments");
    }
    e3s_shuttle_t& shuttle = *(e3s_controller.get_station().get_shuttles()[park_slot-1]);



    e3s_cmd_shuttle_list(shuttle); 
}

void e3s_cmd_shuttle_rate_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1){
        e3s_cmd_show_error("Invalid command arguments");
    }


    // Sending shuttle reference
    if(!e3s_toolset_is_number(args[args.size()-1])){
        e3s_cmd_show_error("Invalid command arguments");
    }
    uint8_t park_slot = std::stoi(args[args.size()-1]);
    if(!e3s_toolset_is_park_slot(park_slot)){
        e3s_cmd_show_error("Invalid command arguments");
    }
    e3s_shuttle_t& shuttle = *(e3s_controller.get_station().get_shuttles()[park_slot-1]);



    e3s_cmd_shuttle_rate(shuttle);
}

void e3s_cmd_shuttle_report_wrapper(const std::vector<std::string>& args) {
    if (args.size() != 1){
        e3s_cmd_show_error("Invalid command arguments");
    }
    if(!e3s_toolset_is_number(args[0])){
        e3s_cmd_show_error("Invalid command arguments");
    }

    if(!e3s_toolset_is_park_slot(std::stoi(args[0]))){
        e3s_cmd_show_error("Invalid command arguments");
    }

    e3s_cmd_shuttle_report(std::stoi(args[0]));
}




// Common Wrapper Commands

void e3s_cmd_common_clear_wrapper(const std::vector<std::string>& args){

    e3s_cmd_common_clear();
}


// Station Commands
void e3s_cmd_station_go(uint8_t park_slot) { 

    if(e3s_controller.get_station().get_shuttles()[park_slot-1] != nullptr){
        e3s_controller.set_context(e3s_cmd_context_t::SHUTTLE);
        e3s_menu_shuttle(*(e3s_controller.get_station().get_shuttles()[park_slot-1]));
    }else{
        e3s_cmd_show_error("There is no shuttle at that location");
        return;
    }


}

void e3s_cmd_station_load(uint8_t park_slot, uint8_t source_type, uint32_t source_amount) { 

    e3s_shuttle_t** shuttles = e3s_controller.get_station().get_shuttles();

    if(shuttles[park_slot-1] == nullptr){
        e3s_cmd_show_error("There is no shuttle at that location to load resources");
    }

    e3s_shuttle_t& shuttle = *(shuttles[park_slot-1]);
    // {"energy",0},{"oxygen",1},{"water",2},{"food",3}
    switch(source_type){
        case 0:{
            if(e3s_controller.get_station().get_energy() < source_amount){
                e3s_cmd_show_error("Not enough energy to load");
            }
            uint32_t d = shuttle.increase_energy(source_amount);
            e3s_controller.get_station().decrease_energy(d);
            e3s_controller.display_device.print_cmd_output(28,255,"Loaded %u energy to shuttle at park slot %hhu",d,shuttle.get_park_slot());
        }break;
           
        case 1:{
            if(e3s_controller.get_station().get_oxygen() < source_amount){
                e3s_cmd_show_error("Not enough oxygen to load");
            }
            uint16_t d = shuttle.increase_oxygen(source_amount);
            e3s_controller.get_station().decrease_oxygen(d);  
            e3s_controller.display_device.print_cmd_output(28,255,"Loaded %hu oxygen to shuttle at park slot %hhu",d,shuttle.get_park_slot());
       
        }break;

        case 2:{
            if(e3s_controller.get_station().get_water() < source_amount){
                e3s_cmd_show_error("Not enough water to load");
            }
            uint16_t d = shuttle.increase_water(source_amount);
            e3s_controller.get_station().decrease_water(d);    
            e3s_controller.display_device.print_cmd_output(28,255,"Loaded %hu water to shuttle at park slot %hhu",d,shuttle.get_park_slot());
     
        }break;

        case 3:{
            if(e3s_controller.get_station().get_food() < source_amount){
                e3s_cmd_show_error("Not enough food to load");
            }
            uint16_t d = shuttle.increase_food(source_amount);
            e3s_controller.get_station().decrease_food(d);   
            e3s_controller.display_device.print_cmd_output(28,255,"Loaded %hu food to shuttle at park slot %hhu",d,shuttle.get_park_slot());
      
        }break;

        case 4:{
            uint32_t energy_required = e3s_shuttle_t::E3S_SHUTTLE_ENERGY_MAX-shuttle.get_energy();
            uint16_t oxygen_required = e3s_shuttle_t::E3S_SHUTTLE_OXYGEN_MAX-shuttle.get_oxygen();
            uint16_t water_required = e3s_shuttle_t::E3S_SHUTTLE_WATER_MAX-shuttle.get_water();
            uint16_t food_required = e3s_shuttle_t::E3S_SHUTTLE_FOOD_MAX-shuttle.get_food();

            if(e3s_controller.get_station().get_energy() < (energy_required) ){
                e3s_cmd_show_error("Not enough energy for comprehensive load");
            }
            if(e3s_controller.get_station().get_oxygen() < (oxygen_required) ){
                e3s_cmd_show_error("Not enough oxygen for comprehensive load");
            }
            if(e3s_controller.get_station().get_water() < (water_required) ){
                e3s_cmd_show_error("Not enough water for comprehensive load");
            }
            if(e3s_controller.get_station().get_food() < (food_required) ){
                e3s_cmd_show_error("Not enough food for comprehensive load");
            }

            if((energy_required+oxygen_required+water_required+food_required) == 0 ){
                e3s_cmd_show_error("Shuttle is fully loaded");
            }

            e3s_controller.get_station().decrease_energy(food_required);   
            e3s_controller.get_station().decrease_oxygen(oxygen_required);   
            e3s_controller.get_station().decrease_water(water_required);   
            e3s_controller.get_station().decrease_food(food_required);   
            shuttle.increase_energy(energy_required);
            shuttle.increase_oxygen(oxygen_required);
            shuttle.increase_water(water_required);
            shuttle.increase_food(food_required);
            e3s_controller.display_device.print_cmd_output(28,255, "Shuttle at park location %hu has been fully loaded",shuttle.get_park_slot());
            


        }break;

    }

}

void e3s_cmd_station_approve() { 

    uint16_t pending_shuttles_amount = e3s_controller.get_station().get_pending_shuttles_amount();

    if(pending_shuttles_amount == 0){
        e3s_cmd_show_error("There are no shuttles waiting in the queue");
    }    


    uint8_t available_park_slot = 0;

    e3s_shuttle_t** shuttles = e3s_controller.get_station().get_shuttles();

    for(int i = 0; i < 6; i++){
        if(shuttles[i] == nullptr){
            available_park_slot = i+1;
            break;
        }
    }

    if(available_park_slot == 0){
        e3s_cmd_show_error("No available park slot for new shuttle");
    }


    float possibility = (std::rand()/(float)RAND_MAX);

    if(possibility <= 0.60 ){
        // Visitor
        e3s_shuttle_visitor_t* new_visitor = new e3s_shuttle_visitor_t(available_park_slot);
        shuttles[available_park_slot-1] = new_visitor;
        e3s_controller.display_device.print_cmd_output(54,255,"Visitor shuttle has been placed to park slot %hhu",available_park_slot);
    }else if (possibility <=0.95){
        // Supply
        e3s_shuttle_supply_t* new_supply = new e3s_shuttle_supply_t(available_park_slot);
        e3s_controller.display_device.print_cmd_output(54,255,"Supply shuttle has been placed to park slot %hhu",available_park_slot);
        shuttles[available_park_slot-1] = new_supply;
    }else{
        // Raider
        e3s_shuttle_raider_t* new_raider = new e3s_shuttle_raider_t(available_park_slot);
        e3s_controller.display_device.print_cmd_output(232,255,"Raiders have arrived, they are at park slot %hhu, this is bad :( ",available_park_slot);
        shuttles[available_park_slot-1] = new_raider;
    }

    e3s_controller.get_station().set_pending_shuttles_amount(pending_shuttles_amount-1);

    // 0.60 visitor
    // 0.35 supply
    // 0.05 raider

    


}

void e3s_cmd_station_launch(uint8_t park_slot) {

    e3s_shuttle_t** shuttles = e3s_controller.get_station().get_shuttles();

    if(shuttles[park_slot-1] == nullptr){
        e3s_cmd_show_error("There is no shuttle at that location to launch");
    }

    shuttles[park_slot-1]->launch_action();
    delete shuttles[park_slot-1];
    shuttles[park_slot-1] = nullptr;

}

void e3s_cmd_station_supply(uint8_t park_slot){

    e3s_shuttle_supply_t* supply;

    e3s_station_t& station = e3s_controller.get_station();


    if(station.get_shuttles()[park_slot-1] == nullptr){
        e3s_cmd_show_error("There is no shuttle at that park location to supply");
    }

    if(station.get_shuttles()[park_slot-1]->get_shuttle_type() != SUPPLY){
        e3s_cmd_show_error("That is not a supply shuttle");

    }



    supply = static_cast<e3s_shuttle_supply_t*>(e3s_controller.get_station().get_shuttles()[park_slot-1]);



    // Reference
    std::tuple<uint32_t,uint16_t,uint16_t,uint16_t>& supplies = supply->get_supplies();

    
    if(std::get<0>(supplies) == 0 and std::get<1>(supplies) == 0 and std::get<2>(supplies) == 0 and std::get<3>(supplies) == 0){
        e3s_cmd_show_error("Supply shuttle is empty now");
    }

    station.increase_energy(std::get<0>(supplies));
    station.increase_food(std::get<1>(supplies));
    station.increase_water(std::get<2>(supplies));
    station.increase_oxygen(std::get<3>(supplies));

    supplies = {0,0,0,0};

    e3s_controller.display_device.print_cmd_output(28,255,"Station got supplies from supply shuttle from park slot %hhu",supply->get_park_slot());

}



// Shuttle Commands

void e3s_cmd_shuttle_select(e3s_shuttle_t& shuttle, uint8_t crew_id){

    if(crew_id >= shuttle.get_crew().size() or crew_id < 0){
        e3s_cmd_show_error("Invalid crew member id to select");
    }

    e3s_crew_t& crew = shuttle.get_crew()[crew_id];
    e3s_menu_crew(crew);
    return;
}

void e3s_cmd_shuttle_list(e3s_shuttle_t& shuttle){

    uint16_t crew_size = shuttle.get_crew_size();
    if(crew_size){
        e3s_controller.display_device.print_string(5,2,31,255," Crew Member List ");
        for(uint16_t i = 0; i < crew_size; i++){
            e3s_crew_t& crew_member = shuttle.get_crew()[i];
            switch(shuttle.get_shuttle_type()){
                case VISITOR:
                    e3s_controller.display_device.print_string(6+i,2,18,255,"  %2hu) %s %s  ",i,crew_member.get_name().c_str(),crew_member.get_surname().c_str());
                    break;
                case SUPPLY:
                    e3s_controller.display_device.print_string(6+i,2,22,255,"  %2hu) %s %s  ",i,crew_member.get_name().c_str(),crew_member.get_surname().c_str());
                    break;
                case RAIDER:
                    e3s_controller.display_device.print_string(6+i,2,124,255,"  %2hu) %s %s  ",i,crew_member.get_name().c_str(),crew_member.get_surname().c_str());
                    break;
            }
        }

        // Press any key to continue;
        e3s_cmd_common_press_any_key_to_continue("Press any key to continue...");

    }
}

void e3s_cmd_shuttle_rate(e3s_shuttle_t& shuttle){

    e3s_controller.display_device.print_cmd_output(18,255,"Shuttle success rate: %f",shuttle.get_success_rate());
}

void e3s_cmd_shuttle_report(uint8_t park_slot) { 

    e3s_shuttle_t** shuttles = e3s_controller.get_station().get_shuttles();
    if(shuttles[park_slot-1] == nullptr){
        e3s_cmd_show_error("There is no shuttle at that location to report");
    }

    e3s_shuttle_t& shuttle = *(shuttles[park_slot-1]);

    e3s_controller.display_device.print_cmd_output(18,255,"Report[%hhu]: Energy(%u/%u), Oxygen(%u/%u), Water(%u/%u), Food(%u/%u)",park_slot,
                                                    shuttle.get_energy(),
                                                    e3s_shuttle_t::E3S_SHUTTLE_ENERGY_MAX,
                                                    shuttle.get_oxygen(),
                                                    e3s_shuttle_t::E3S_SHUTTLE_OXYGEN_MAX,
                                                    shuttle.get_water(),
                                                    e3s_shuttle_t::E3S_SHUTTLE_WATER_MAX,
                                                    shuttle.get_food(),
                                                    e3s_shuttle_t::E3S_SHUTTLE_FOOD_MAX);


}






// Common Commands

void e3s_cmd_common_clear(){
    e3s_controller.display_device.clear_cmd_output();
}

void e3s_cmd_common_press_any_key_to_continue(const std::string& comment){
    e3s_controller.display_device.print_cmd_output(90,255,"%s",comment.c_str());
    while(!e3s_term_keyboard_hit()){
        usleep(100);
    }
    e3s_controller.display_device.clear_cmd_output();
    e3s_term_getch();
}


// Error Commands

void e3s_cmd_show_error(const std::string& error) {
    throw e3s_cmd_exception_t(error);
}




