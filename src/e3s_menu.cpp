#include "../include/e3s_menu.hpp"
#include "../include/e3s_station.hpp"
#include "../include/e3s_shuttle.hpp"
#include "../include/e3s_crew.hpp"
#include "../include/e3s_term.hpp"
#include "../include/e3s_display_device.hpp"
#include "../include/e3s_controller.hpp"
#include "../include/e3s_cmd.hpp"
#include "../include/e3s_scheduler.hpp"

void e3s_menu_start_screen(){

    const e3s_image_t& start_image = e3s_controller.get_galery().get_images().at("start_screen.png");
    e3s_controller.display_device.print_image(0,0,start_image);

    e3s_controller.display_device.print_string(31,1,237,240,"Developers");
    e3s_controller.display_device.print_string(32,1,238,255,"Kaan Baydemir");
    e3s_controller.display_device.print_string(33,1,238,255,"Emre Şahin Demirbaş");
    e3s_controller.display_device.print_string(34,1,238,255,"Tarık Şen");

    e3s_cmd_common_press_any_key_to_continue("Press any key to start the game...");
}

void e3s_menu_station(e3s_station_t& station){


    while(1){
        
        // I AM AMELE
        e3s_controller.display_device.print_image(0,0, *(station.get_background()) );

        // Print shuttles
        e3s_shuttle_t** shuttles = e3s_controller.get_station().get_shuttles();  

        for(size_t i = 0; i < 6; i++){
            if(shuttles[i] != nullptr){
                
                switch(i){
                    case 0:
                        e3s_controller.display_device.print_image(16,23,*(shuttles[i]->get_outer_view()));
                        break;

                    case 1:
                        e3s_controller.display_device.print_image(25,13,*(shuttles[i]->get_outer_view()));
                        break;

                    case 2:
                        e3s_controller.display_device.print_image(37,4,*(shuttles[i]->get_outer_view()));
                        break;

                    case 3:
                        e3s_controller.display_device.print_image_reverse(16,61,*(shuttles[i]->get_outer_view()));
                        break;

                    case 4:
                        e3s_controller.display_device.print_image_reverse(25,67,*(shuttles[i]->get_outer_view()));

                        break;
                    case 5:
                        e3s_controller.display_device.print_image_reverse(37,71,*(shuttles[i]->get_outer_view()));
                        break;

                }
                
            }

        }


        std::string cmd = e3s_term_get_input();

        

        if(cmd == "quit" or cmd == "exit"){
            system("clear");
            return;
        }


        e3s_controller.cmd_interpreter(cmd);
        

    }

    return;
}

void e3s_menu_shuttle(e3s_shuttle_t& shuttle){



    while(1){

        // I AM AMELE
        e3s_controller.display_device.print_image(0,0, *(shuttle.get_inner_view()) );

        e3s_controller.display_device.print_string(4,2,238,255,"Shuttle: %hhu",shuttle.get_park_slot());



        std::string cmd = e3s_term_get_input();
        if(cmd == "return"){
            e3s_controller.set_context(e3s_cmd_context_t::STATION);
            e3s_controller.display_device.clear_cmd_output();
            return;
        }

        cmd = cmd + " ";
        cmd = cmd + (char)(shuttle.get_park_slot()+'0');

        e3s_controller.cmd_interpreter(cmd);



    }


    return;
}

void e3s_menu_crew(e3s_crew_t& crew){
    
    while(1){
        // I AM AMELE
        e3s_controller.display_device.print_image(0,0, *(crew.get_background()) );
        e3s_controller.display_device.print_image(11,7,*(crew.get_body()));

        if(crew.get_helmet()){
            const e3s_image_t& helmet_large = e3s_controller.get_galery().get_images().at("helmet_large.png");
            const e3s_image_t& helmet = e3s_controller.get_galery().get_images().at("helmet.png");
            e3s_controller.display_device.print_image(11,7,helmet_large);
            e3s_controller.display_device.print_image(14,43,helmet);

        }
        if(crew.get_suit()){
            const e3s_image_t& suit_large = e3s_controller.get_galery().get_images().at("suit_large.png");
            const e3s_image_t& suit = e3s_controller.get_galery().get_images().at("suit.png");
            e3s_controller.display_device.print_image(11,7,suit_large);
            e3s_controller.display_device.print_image(28,43,suit);

        }
        if(crew.get_drugs()){
            const e3s_image_t& drugs = e3s_controller.get_galery().get_images().at("drugs.png");
            e3s_controller.display_device.print_image(42,43,drugs);
        }

        //14 64
        e3s_controller.display_device.print_string(10,65,234,238,"Name");
        e3s_controller.display_device.print_string(11,64,235,255,"%s",crew.get_name().c_str());

        e3s_controller.display_device.print_string(13,65,234,238,"Surname");
        e3s_controller.display_device.print_string(14,64,235,255,"%s",crew.get_surname().c_str());

        e3s_controller.display_device.print_string(16,65,234,238,"Age");
        e3s_controller.display_device.print_string(17,64,235,255,"%hu",crew.get_age());

        e3s_controller.display_device.print_string(19,65,234,238,"Nationality");
        e3s_controller.display_device.print_string(20,64,235,255,"%s",crew.get_nationality().c_str());

        e3s_controller.display_device.print_string(22,65,234,238,"Gender");
        if(crew.get_gender()){
            e3s_controller.display_device.print_string(23,64,235,255,"Male");
        }else{
            e3s_controller.display_device.print_string(23,64,235,255,"Female");
        }



        std::string cmd = e3s_term_get_input();
        if(cmd == "return"){
            e3s_controller.set_context(e3s_cmd_context_t::SHUTTLE);
            e3s_controller.display_device.clear_cmd_output();
            return;
        }

        

        e3s_controller.cmd_interpreter(cmd);


    }


    return;
}


void e3s_menu_end_game_win(){
    //pthread_kill(e3s_scheduler_thread,SIGTERM);
    system("clear");

    const e3s_image_t& img = e3s_controller.get_galery().get_images().at("end_game_win.png");
    e3s_controller.display_device.print_string(0,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(1,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(2,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(3,0,234,237,"%96c",' ');

    e3s_controller.display_device.print_string(36,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(37,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(38,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(39,0,234,237,"%96c",' ');




    e3s_controller.display_device.print_image(0,0,img);

    e3s_controller.end();


}

void e3s_menu_end_game_lose(){
    //pthread_kill(e3s_scheduler_thread,SIGTERM);
    system("clear");

    const e3s_image_t& img = e3s_controller.get_galery().get_images().at("end_game_lose.png");
    e3s_controller.display_device.print_string(0,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(1,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(2,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(3,0,234,237,"%96c",' ');

    e3s_controller.display_device.print_string(36,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_string(37,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(38,0,234,243,"%96c",' ');
    e3s_controller.display_device.print_string(39,0,234,237,"%96c",' ');
    e3s_controller.display_device.print_image(0,0,img);


    e3s_controller.end();

}