#ifndef E3S_CONTROLLER_HPP
#define E3S_CONTROLLER_HPP

#include "e3s.hpp"
#include "e3s_term.hpp"
#include "e3s_cmd.hpp"
#include "e3s_station.hpp"
#include "e3s_display_device.hpp"
#include "e3s_galery.hpp"

class e3s_controller_t{

private:


    e3s_cmd_context_t context;
    e3s_galery_t galery;
    e3s_station_t* station;
public:

    std::map<std::string, void(*)(const std::vector<std::string>& args)> station_cmd_map;
    std::map<std::string, void(*)(const std::vector<std::string>& args)> shuttle_cmd_map;
    std::map<std::string, void(*)(const std::vector<std::string>& args)> crew_cmd_map;

    e3s_display_device_t display_device;

    e3s_controller_t();

    void begin();
    void loop();
    void end();
    bool cmd_interpreter(std::string cmd);

    const e3s_galery_t& get_galery() const;

    e3s_cmd_context_t get_context() const;
    void set_context(e3s_cmd_context_t context);

    e3s_station_t& get_station() const;

    ~e3s_controller_t();
};

extern e3s_controller_t e3s_controller;


#endif