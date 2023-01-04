#ifndef E3S_MENU_HPP
#define E3S_MENU_HPP

#include "e3s.hpp"

class e3s_station_t;
class e3s_shuttle_t;
class e3s_crew_t;

void e3s_menu_start_screen();

void e3s_menu_end_game_win();

void e3s_menu_end_game_lose();

void e3s_menu_station(e3s_station_t& station);

void e3s_menu_shuttle(e3s_shuttle_t& shuttle);

void e3s_menu_crew(e3s_crew_t& crew);

#endif