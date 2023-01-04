#include "../include/e3s_scheduler.hpp"
#include "../include/e3s_controller.hpp"
#include "../include/e3s_menu.hpp"

pthread_t e3s_scheduler_thread;

void* e3s_scheduler(void* arg){

    time_t start_time = time(NULL);
    time_t current_time;
    time_t shuttle_arrival_period;
    time_t check_arrival_time = time(NULL);
    e3s_station_t& station = e3s_controller.get_station();
    uint16_t pending_shuttle_amount;
    uint16_t turns_without_arrival = 0;

    while(1){
        current_time = time(NULL);

        pending_shuttle_amount = station.get_pending_shuttles_amount();

        if( station.get_shuttle_interest() < 0.05 or pending_shuttle_amount == 100){
            
            // GAME OVER
            e3s_menu_end_game_lose();
        }

        if(e3s_controller.get_station().get_successful_missions() >= E3S_STATION_SUCCESSFUL_MISSIONS_REQUIRED){
            // YOU WIN
            e3s_menu_end_game_win();

        }


        shuttle_arrival_period = (time_t)(60.0 - ( station.get_shuttle_interest()*50.0 )  ) ;
        // shuttle interest below 0.01 is game over

        e3s_controller.display_device.print_string(1,2,226,232," Energy: %11u ",station.get_energy());
        e3s_controller.display_device.print_string(1,23,87,232," Oxygen: %6u ",station.get_oxygen());
        e3s_controller.display_device.print_string(1,39,26,255," Water: %6u ",station.get_water());
        e3s_controller.display_device.print_string(1,54,94,255," Food: %6u ",station.get_food());
        e3s_controller.display_device.print_string(1,68,93,255," Pending Shuttles: %6u ", pending_shuttle_amount);
        e3s_controller.display_device.print_string(2,2,22,255," Shuttle Interest: %17f ",  station.get_shuttle_interest());
        e3s_controller.display_device.print_string(2,39,69,255," Successful Missions: %6ld ", station.get_successful_missions());
        //                                                                      

        // (shuttle_interest * 100) * shuttle_arrival_period = K
        // (1 * 100) * 10 = 1000 
        // K = 1000
        // shuttle_arrival_period = K/(shuttle_interest*100);


        // Calculate possibility for new shuttle request
        if( (current_time-check_arrival_time) > shuttle_arrival_period ){
            check_arrival_time = current_time;
            
            // Calculate possibility of new shuttle
            if(((std::rand() / (float)RAND_MAX ) + pending_shuttle_amount*0.02) <=  (station.get_shuttle_interest() + 0.07*turns_without_arrival) ){
                // new shuttle got interested
                turns_without_arrival = 0;
                station.set_pending_shuttles_amount(pending_shuttle_amount + ((rand()% (int)(6*station.get_shuttle_interest()+1) )+1) );
            }else{
                // new shuttle is ignoring the station
                // If there are no comers, then the waiting shuttle will think that
                // this place is boring and will decide on whether it should leave
                // the queue.
                // So it will evaluate the 'shuttle_interest' and decide whether it should leave
                if( ((std::rand() / (float)RAND_MAX ) + pending_shuttle_amount*0.02) >  station.get_shuttle_interest() and (pending_shuttle_amount > 0) ){
                    station.set_pending_shuttles_amount(pending_shuttle_amount-1);
                    // this shuttle being leaving, decreases the shuttle interest
                    station.set_shuttle_interest( station.get_shuttle_interest() - (logf(station.get_shuttle_interest()+1.0)/2.0) - pending_shuttle_amount*0.02  ) ;

                }
                turns_without_arrival++;
            }


        }

        e3s_controller.get_station().set_shuttle_interest( station.get_shuttle_interest() - (0.05/(float)shuttle_arrival_period));
        e3s_controller.display_device.print_string(2,68,31,255," Next Arrival: %10ld ", shuttle_arrival_period - (current_time-check_arrival_time));




        sleep(1);
    }
    return NULL;
}