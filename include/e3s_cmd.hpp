#ifndef E3S_CMD_HPP
#define E3S_CMD_HPP

#include "e3s.hpp"
#include "e3s_image.hpp"

class e3s_shuttle_t;

class e3s_cmd_exception_t{
private:
    std::string explanation;

public:
    e3s_cmd_exception_t(std::string explanation);
    std::string get_explanation();

};


enum e3s_cmd_context_t{
    STATION = 1,
    SHUTTLE,
    CREW
};



// Station Commands

void e3s_cmd_station_go_wrapper(const std::vector<std::string>& args);

void e3s_cmd_station_go(uint8_t park_slot);

void e3s_cmd_station_load_wrapper(const std::vector<std::string>& args);

void e3s_cmd_station_load(uint8_t park_slot, uint8_t source_type, uint32_t source_amount);

void e3s_cmd_station_approve_wrapper(const std::vector<std::string>& args);

void e3s_cmd_station_approve();

void e3s_cmd_station_launch_wrapper(const std::vector<std::string>& args);

void e3s_cmd_station_launch(uint8_t park_slot);

void e3s_cmd_station_supply_wrapper(const std::vector<std::string>& args);

void e3s_cmd_station_supply(uint8_t park_slot);


// Shuttle Commands

void e3s_cmd_shuttle_select_wrapper(const std::vector<std::string>& args);

void e3s_cmd_shuttle_select(e3s_shuttle_t& shuttle, uint8_t crew_id);

void e3s_cmd_shuttle_list_wrapper(const std::vector<std::string>& args);

void e3s_cmd_shuttle_list(e3s_shuttle_t& shuttle);

void e3s_cmd_shuttle_rate_wrapper(const std::vector<std::string>& args);

void e3s_cmd_shuttle_rate(e3s_shuttle_t& shuttle);

void e3s_cmd_shuttle_report_wrapper(const std::vector<std::string>& args);

void e3s_cmd_shuttle_report(uint8_t park_slot);





// Crew Commands

void e3s_cmd_crew_give_wrapper(const std::vector<std::string>& args);

void e3s_cmd_crew_give(const std::string& item, bool is_equiped);


// Common Commands

void e3s_cmd_common_clear_wrapper(const std::vector<std::string>& args);

void e3s_cmd_common_clear();

void e3s_cmd_common_press_any_key_to_continue(const std::string& comment);


// Error Commands

void e3s_cmd_show_error(const std::string& error);

#endif