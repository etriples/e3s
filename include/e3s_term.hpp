#ifndef E3S_TERM_HPP
#define E3S_TERM_HPP

// Rows and columns are 1-indexex in the terminal

#include "e3s.hpp"

#define E3S_TERM_INPUT_BUFFER_MAX 512
#define E3S_TERM_INPUT_ENTRY_ROW 38
#define E3S_TERM_INPUT_ENTRY_COL 4
#define E3S_TERM_INPUT_ENTRY_INDICATOR ">"

#define COLOR "\033["
	#define RESET "0;"
	#define BOLD "1;"
	#define UNDERLINE "4;"
	#define INVERSE "7;"
	#define CLEAR "\033[0m"
	
	#define BLACK "30m"
	#define RED "31m"
	#define GREEN "32m"
	#define YELLOW "33m"
	#define BLUE "34m"
	#define MAGENTA "35m"
	#define CYAN "36m"
	#define WHITE "37m"

	#define RGB(r,g,b) "38;2;"#r";"#g";"#b"m"
	#define RGB_B(r,g,b) "48;2;"#r";"#g";"#b";"

	#define BLACK_B "40;"
	#define RED_B "41;"
	#define GREEN_B "42;"
	#define YELLOW_B "43;"
	#define BLUE_B "44;"
	#define MAGENTA_B "45;"
	#define CYAN_B "46;"
	#define WHITE_B "47;"
	#define GRAY_B "100;"
	#define LRED_B "101;"
	#define LGREEN_B "102;"
	#define LYELLOW_B "103;"
	#define LBLUE_B "104;"
	#define LPURPLE "105;"
	#define TEAL_B "106;"

extern termios e3s_termios_original;

extern sem_t e3s_display_device_access;


void e3s_term_reset_terminal_mode();

void e3s_term_set_terminal_mode();

int e3s_term_keyboard_hit();

int e3s_term_getch();

void e3s_term_cursor_set(uint16_t cell_row, uint16_t cell_col);

void e3s_term_cursor_reset();

void e3s_term_print_color(uint16_t cell_row, uint16_t cell_col, uint8_t color);

void e3s_term_print_string(uint16_t cell_row, uint16_t cell_col, const char* format, ...);

void e3s_term_window_resize(uint16_t win_row, uint16_t win_col);

void e3s_term_print_cell_up(uint16_t cell_row, uint16_t cell_col, uint8_t color_bg, uint8_t color_fg);

void e3s_term_print_cell_down(uint16_t cell_row, uint16_t cell_col, uint8_t color_bg, uint8_t color_fg);

void e3s_term_print_char(uint16_t cell_row, uint16_t cell_col, char ch);

void e3s_term_color_set(uint8_t color_bg, uint8_t color_fg);

void e3s_term_color_reset();

std::string e3s_term_get_input();


#endif
