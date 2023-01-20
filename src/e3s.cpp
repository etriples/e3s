#include "../include/e3s.hpp"
#include "../include/e3s_controller.hpp"
#include "../include/e3s_display_device.hpp"
#include "../include/e3s_shuttle_supply.hpp"
#include "../include/e3s_galery.hpp"


int main(){


    e3s_controller.begin();

    e3s_controller.loop();

    e3s_controller.end();

    return 0;
}

