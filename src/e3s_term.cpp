#include "../include/e3s_term.hpp"

struct termios e3s_termios_original;



void e3s_term_reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &e3s_termios_original);
}

// re-call this function with different configuration


void e3s_term_set_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &e3s_termios_original);
    memcpy(&new_termios, &e3s_termios_original, sizeof(new_termios));
    atexit(e3s_term_reset_terminal_mode);

    /* register cleanup handler, and set the new terminal mode */
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}


int e3s_term_keyboard_hit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}


int e3s_term_getch()
{
    int r;
    unsigned char c;
    if ((r = read(STDIN_FILENO, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void e3s_term_cursor_set(uint16_t cell_row, uint16_t cell_col){
    printf("\033[%d;%dH",cell_row,cell_col);
    fflush(stdout);
}

void e3s_term_cursor_reset(){
    printf("\033[0;0H");
    fflush(stdout);
}

// 256 color printing
void e3s_term_print_color(uint16_t cell_row, uint16_t cell_col, uint8_t color){
    e3s_term_cursor_set(cell_row,cell_col);
    printf("\033[48;5;%dm \033[0m",color);
    e3s_term_cursor_reset();
    fflush(stdout);
}

// 1-indexed
void e3s_term_print_cell_up(uint16_t cell_row, uint16_t cell_col, uint8_t color_bg, uint8_t color_fg){
    e3s_term_cursor_set(cell_row,cell_col);
    if(color_bg){
        printf("\033[48;5;%um",color_bg);
    }else{
        printf("\033[49m");
    }
    printf("\033[38;5;%um▀\033[0m", color_fg);
    e3s_term_cursor_reset();
    fflush(stdout);    
}

// 1-indexed
void e3s_term_print_cell_down(uint16_t cell_row, uint16_t cell_col, uint8_t color_bg, uint8_t color_fg){
    e3s_term_cursor_set(cell_row,cell_col);
    if(color_bg){
        printf("\033[48;5;%um",color_bg);
    }else{
        printf("\033[49m");
    }
    printf("\033[38;5;%um▄\033[0m", color_fg);
    e3s_term_cursor_reset();
    fflush(stdout);    
}


void e3s_term_color_set(uint8_t color_bg, uint8_t color_fg){

    printf("\033[48;5;%um\033[38;5;%um",color_bg,color_fg);
    fflush(stdout);
}
void e3s_term_color_reset(){
    printf("\033[0m");
    fflush(stdout);
}


// code_bg = -1 -> no background
void e3s_term_print_string(uint16_t cell_row, uint16_t cell_col, const char* format, ...){
    e3s_term_cursor_set(cell_row,cell_col);
    va_list vlist;
    va_start(vlist,format);
    vprintf(format,vlist);
    va_end(vlist);
    printf("\033[0m");
    e3s_term_cursor_reset();
    fflush(stdout);
}

void e3s_term_print_char(uint16_t cell_row, uint16_t cell_col, char ch){
    e3s_term_cursor_set(cell_row,cell_col);
    printf("%c",ch);
    e3s_term_cursor_reset();
    fflush(stdout);
}

void e3s_term_window_resize(uint16_t dim_row, uint16_t dim_col){
    printf("\e[8;%d;%dt",dim_row,dim_col);
    fflush(stdout);
}

void e3s_term_window_resize_event(int sig){
    e3s_term_window_resize(48,192);
    printf("Window resized");
}

std::string e3s_term_get_input(){

    char     e3s_term_input_buffer[E3S_TERM_INPUT_BUFFER_MAX] = {0};
    uint16_t e3s_term_input_cursor = E3S_TERM_INPUT_ENTRY_COL;
    
    sem_wait(&e3s_display_device_access);
    e3s_term_color_set(243,255);
    e3s_term_print_string(E3S_TERM_INPUT_ENTRY_ROW,E3S_TERM_INPUT_ENTRY_COL-2,E3S_TERM_INPUT_ENTRY_INDICATOR);
    e3s_term_color_reset();
    sem_post(&e3s_display_device_access);

    while(1){


        int c = e3s_term_getch();

        if(c == 3){
            exit(EXIT_FAILURE);
        }

        sem_wait(&e3s_display_device_access);
        e3s_term_color_set(243,255);
        switch(c){
            case 10: case 13:{
                std::string ret(e3s_term_input_buffer);

                e3s_term_print_string(E3S_TERM_INPUT_ENTRY_ROW,E3S_TERM_INPUT_ENTRY_COL,"%93c", ' ');

                sem_post(&e3s_display_device_access);
                e3s_term_color_reset();
                return ret;
            }break;

            case 127:{
                if(e3s_term_input_cursor > E3S_TERM_INPUT_ENTRY_COL){
                    e3s_term_input_cursor--;
                }
                e3s_term_input_buffer[e3s_term_input_cursor-E3S_TERM_INPUT_ENTRY_COL] = '\0';
                e3s_term_print_string(E3S_TERM_INPUT_ENTRY_ROW,e3s_term_input_cursor," ");
            }break;

            default:{
                //printf("Printable pressed!\n");
                e3s_term_input_buffer[e3s_term_input_cursor-E3S_TERM_INPUT_ENTRY_COL] = c;
                e3s_term_print_string(E3S_TERM_INPUT_ENTRY_ROW,e3s_term_input_cursor,COLOR UNDERLINE WHITE "%c" CLEAR ,c);
                e3s_term_input_cursor++;
            }break;
        }
        e3s_term_color_reset();
        sem_post(&e3s_display_device_access);

    }
    return "";
}
