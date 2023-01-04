#include "../include/e3s_controller.hpp"
#include "../include/e3s_cmd.hpp"
#include "../include/e3s_menu.hpp"
#include "../include/e3s_toolset.hpp"
#include "../include/e3s_scheduler.hpp"

e3s_controller_t e3s_controller;

/**
 


station help:
    - go <SHUTTLE_ID>                                   
    - load <SHUTTLE_ID> <SOURCE_TYPE> <SOURCE_AMOUNT>       
    - launch <SHUTTLE_ID>
    - approve <SHUTTLE_TYPE>
    - report <SHUTTLE_ID>

shuttle help:
    - select <CREW_ID>
    - print
    - rate #Returns the possibility of success
    - return

 crew help:
    - give <ITEM_TYPE>
    - take <ITEM_TYPE>
    - dance
    - back    

 
  
 */
e3s_controller_t::e3s_controller_t() {

    srand(time(NULL));

    this->galery.load("../res/images");

    this->context = e3s_cmd_context_t::STATION;

    this->station = new e3s_station_t{ (uint32_t)(rand() % (e3s_station_t::E3S_STATION_ENERGY_MAX - e3s_station_t::E3S_STATION_ENERGY_MIN) + e3s_station_t::E3S_STATION_ENERGY_MIN),
                                       (uint16_t)(rand() % (e3s_station_t::E3S_STATION_FOOD_MAX - e3s_station_t::E3S_STATION_FOOD_MIN) + e3s_station_t::E3S_STATION_FOOD_MIN), 
                                       (uint16_t)(rand() % (e3s_station_t::E3S_STATION_WATER_MAX - e3s_station_t::E3S_STATION_WATER_MIN) + e3s_station_t::E3S_STATION_WATER_MIN),
                                       (uint16_t)(rand() % (e3s_station_t::E3S_STATION_OXYGEN_MAX - e3s_station_t::E3S_STATION_OXYGEN_MIN) + e3s_station_t::E3S_STATION_OXYGEN_MIN) };

    


    // Station};
    this->station_cmd_map["go"] = e3s_cmd_station_go_wrapper;
    this->station_cmd_map["load"] = e3s_cmd_station_load_wrapper;
    this->station_cmd_map["launch"] = e3s_cmd_station_launch_wrapper;
    this->station_cmd_map["approve"] = e3s_cmd_station_approve_wrapper;
    this->station_cmd_map["supply"] = e3s_cmd_station_supply_wrapper;
    this->station_cmd_map["clear"] = e3s_cmd_common_clear_wrapper;

    // Shuttle
    this->shuttle_cmd_map["select"] = e3s_cmd_shuttle_select_wrapper;
    this->shuttle_cmd_map["list"] = e3s_cmd_shuttle_list_wrapper;
    this->shuttle_cmd_map["rate"] = e3s_cmd_shuttle_rate_wrapper;
    this->shuttle_cmd_map["report"] = e3s_cmd_shuttle_report_wrapper;
    this->shuttle_cmd_map["clear"] = e3s_cmd_common_clear_wrapper;

    // Crew
    this->crew_cmd_map["clear"] = e3s_cmd_common_clear_wrapper;


}

e3s_station_t& e3s_controller_t::get_station() const {
    return *(this->station);
}


void e3s_controller_t::begin(){



    e3s_term_set_terminal_mode();
    e3s_term_window_resize(40,96);
    printf("\033[?25l");
    sem_init(&e3s_display_device_access,false,1);
    setlocale(LC_ALL,"en_US.UTF-8");
    


    e3s_controller.display_device.print_string(0,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(1,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(2,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(3,0,234,237,"%96c",' ');

    e3s_controller.display_device.print_string(36,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(37,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(38,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(39,0,234,237,"%96c",' ');

    e3s_menu_start_screen();

    e3s_controller.display_device.print_string(0,0,237,237,"%96c",' ');
    e3s_controller.display_device.print_string(1,0,243,243,"%96c",' ');
    e3s_controller.display_device.print_string(2,0,243,243,"%96c",' ');
    e3s_controller.display_device.print_string(3,0,237,237,"%96c",' ');

    e3s_controller.display_device.print_string(36,0,237,237,"%96c",' ');
    e3s_controller.display_device.print_string(37,0,243,243,"%96c",' ');
    e3s_controller.display_device.print_string(38,0,240,243,"%96c",' ');
    e3s_controller.display_device.print_string(39,0,237,237,"%96c",' ');

    pthread_create(&e3s_scheduler_thread,NULL,e3s_scheduler,NULL);

    // press any key to continue
}

void e3s_controller_t::loop(){



    e3s_menu_station(e3s_controller.get_station());

}

void e3s_controller_t::end(){
    e3s_term_reset_terminal_mode();
    printf("\033[?25h");
    exit(EXIT_SUCCESS);
}

const e3s_galery_t& e3s_controller_t::get_galery() const {
    return this->galery;
}

e3s_cmd_context_t e3s_controller_t::get_context() const {
    return this->context;
}

void e3s_controller_t::set_context(e3s_cmd_context_t context){
    this->context = context;
}

bool e3s_controller_t::cmd_interpreter(std::string cmd){

    std::vector<std::string> args = e3s_toolset_tokenize(cmd, ' ');
    std::string cmd_tokenized = args[0];
    args.erase(args.begin());


    switch(e3s_controller.get_context()){

        case e3s_cmd_context_t::STATION: // Station context
            try{
                auto iter = e3s_controller.station_cmd_map.find(cmd_tokenized);
                if(iter == e3s_controller.station_cmd_map.end()){
                    throw e3s_cmd_exception_t("Command not found");
                }else{
                    (iter->second)(args);
                }

            }catch(e3s_cmd_exception_t& exception){
                e3s_controller.display_device.print_cmd_output(1,255,exception.get_explanation().c_str());
            }

        break;
        
        case e3s_cmd_context_t::SHUTTLE: // Shuttle context
            try{
                auto iter = e3s_controller.shuttle_cmd_map.find(cmd_tokenized);
                if(iter == e3s_controller.shuttle_cmd_map.end()){
                    throw e3s_cmd_exception_t("Command not found");
                }else{
                    (iter->second)(args);
                }

            }catch(e3s_cmd_exception_t& exception){
                e3s_controller.display_device.print_cmd_output(1,255,exception.get_explanation().c_str());
            }
        break;
        
        case e3s_cmd_context_t::CREW: // Crew context
            try{
                auto iter = e3s_controller.crew_cmd_map.find(cmd_tokenized);
                if(iter == e3s_controller.crew_cmd_map.end()){
                    throw e3s_cmd_exception_t("Command not found");
                }else{
                    (iter->second)(args);
                }

            }catch(e3s_cmd_exception_t& exception){
                e3s_controller.display_device.print_cmd_output(1,255,exception.get_explanation().c_str());
            }
        break;


    }

    return 0;
}


e3s_controller_t::~e3s_controller_t(){
    delete this->station;
}




