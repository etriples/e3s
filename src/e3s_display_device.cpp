#include "../include/e3s_display_device.hpp"
#include "../include/e3s_term.hpp"
#include "../include/e3s_image.hpp"
#include "../include/e3s_controller.hpp"


sem_t e3s_display_device_access;

// 0-indexed
void e3s_display_device_t::print_square(uint16_t pixel_row, uint16_t pixel_col, uint8_t color){
    if(color == 15){
        return;
    }
    sem_wait(&e3s_display_device_access);


    uint16_t cell_row = pixel_row / 2;
    uint16_t cell_col = pixel_col;
    uint16_t cell_pos = pixel_row % 2;
    uint16_t cell_pos_other = (pixel_row + 1) % 2;
    
    uint8_t cell_pos_other_code = cell_matrix[cell_row][cell_col][cell_pos_other];

    // cell_pos = 0 -> upper
    // cell_pos = 1 -> lower

    // code 0 is transparent, but printf understands -1 for transparent

    if(cell_pos_other_code == 15){
        // cell_pos_other is zero, then only printing this location is enough

        if(!cell_pos){
            // upper
            e3s_term_print_cell_up(cell_row+1+4, pixel_col+1, 0, color);
        }else{
            // lower
            e3s_term_print_cell_down(cell_row+1+4, pixel_col+1, 0, color);
        }

    }else{
        // cel_pos_other is not zero, this means further processing
        // cel_pos_other_code is stored, so it will be printed as background;

        if(!cell_pos){
            // upper
            e3s_term_print_cell_up(cell_row+1+4,pixel_col+1,cell_pos_other_code,color);
        }else{
            // lower
            e3s_term_print_cell_down(cell_row+1+4,pixel_col+1,cell_pos_other_code,color);
        }

    }
    cell_matrix[cell_row][cell_col][cell_pos] = color;
    fflush(stdout);
    sem_post(&e3s_display_device_access);
}


void e3s_display_device_t::print_string(uint16_t win_row, uint16_t win_col, uint8_t color_bg, uint8_t color_fg, const char* format, ...){
    sem_wait(&e3s_display_device_access);

    e3s_term_cursor_set(win_row+1,win_col+1);
    va_list vlist;
    va_start(vlist,format);
    if(color_bg){
        printf("\033[48;5;%um",color_bg);
    }else{
        printf("\033[49m");
    }
    printf("\033[38;5;%um",color_fg);
    vprintf(format,vlist);
    va_end(vlist);
    printf("\033[0m");
    e3s_term_cursor_reset();
    fflush(stdout);    
    sem_post(&e3s_display_device_access);

}

void e3s_display_device_t::print_image(uint16_t pixel_row, uint16_t pixel_col,const e3s_image_t& img){

    uint32_t image_width = img.get_width();
    uint32_t image_height = img.get_height();

    uint32_t** image_matrix = img.get_matrix();

    for(uint32_t i = 0; i < image_height; i++){
        for(uint32_t j = 0; j < image_width; j++){
            this->print_square(i+pixel_row,j+pixel_col,(uint8_t)image_matrix[i][j]);
        }
    }

}

void e3s_display_device_t::print_image_reverse(uint16_t pixel_row, uint16_t pixel_col,const e3s_image_t& img){
    uint32_t image_width = img.get_width();
    uint32_t image_height = img.get_height();

    uint32_t** image_matrix = img.get_matrix();

    for(uint32_t i = 0; i < image_height; i++){
        for(uint32_t j = 0; j < image_width; j++){
            this->print_square(i+pixel_row,image_width-1-j+pixel_col,(uint8_t)image_matrix[i][j]);
        }
    }

}


e3s_display_device_t::e3s_display_device_t(){
    for(size_t i = 0; i < E3S_DISPLAY_DEVICE_CELL_DIM_ROW; i++){
        for(size_t j = 0; j < E3S_DISPLAY_DEVICE_CELL_DIM_COL; j++){

            this->cell_matrix[i][j][0] = 15;
            this->cell_matrix[i][j][1] = 15;

        }
    }
}

// use when access to display
void e3s_display_device_t::print_cmd_output(uint8_t color_bg, uint8_t color_fg, const char* format, ...){
    
    
    this->clear_cmd_output();

    char buffer[1024] = {0};
    va_list vlist;

    va_start(vlist,format);
    vsprintf(buffer,format,vlist);

    this->print_string(38,0,color_bg,color_fg," %-95s", buffer);

    va_end(vlist);
}

// use when access to display
void e3s_display_device_t::clear_cmd_output(){
    this->print_string(38,0,240,255,"%-96c",' ');
}
