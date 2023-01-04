#ifndef E3S_SCHEDULER_HPP
#define E3S_SCHEDULER_HPP

#include "e3s.hpp"

extern pthread_t e3s_scheduler_thread;

void* e3s_scheduler(void* arg);


#endif