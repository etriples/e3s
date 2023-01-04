#ifndef E3S_DISPLAY_DEVICE_HPP
#define E3S_DISPLAY_DEVICE_HPP


// 0-indexed for each row and column, 1 row & 1 col is a font rectangle
#define E3S_DISPLAY_DEVICE_WINDOW_DIM_ROW 40
#define E3S_DISPLAY_DEVICE_WINDOW_DIM_COL 96

// 0-indexed for each pixel
#define E3S_DISPLAY_DEVICE_PIXEL_DIM_ROW 64
#define E3S_DISPLAY_DEVICE_PIXEL_DIM_COL 96


// 1-indexed for cells
#define E3S_DISPLAY_DEVICE_CELL_DIM_ROW 32
#define E3S_DISPLAY_DEVICE_CELL_DIM_COL 96

#include "e3s.hpp"

extern sem_t e3s_display_device_access;

class e3s_image_t;


class e3s_display_device_t{

private:

    uint8_t cell_matrix[E3S_DISPLAY_DEVICE_CELL_DIM_ROW][E3S_DISPLAY_DEVICE_CELL_DIM_COL][2] = {0};
    
public:
    e3s_display_device_t();
    void print_square(uint16_t pixel_row, uint16_t pixel_col, uint8_t code);
    void print_string(uint16_t win_row, uint16_t win_col, uint8_t color_bg, uint8_t color_fg, const char* format, ...);
    void print_image(uint16_t pixel_row, uint16_t pixel_col,const e3s_image_t& img) ;
    void print_image_reverse(uint16_t pixel_row, uint16_t pixel_col,const e3s_image_t& img);
    void print_cmd_output(uint8_t color_bg, uint8_t color_fg, const char* format, ...);
    void clear_cmd_output();
};





#endif