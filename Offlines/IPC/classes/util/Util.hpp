#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <iostream>
#include <chrono>
#include <unistd.h>
#include <pthread.h>
#include<semaphore.h>

#include "../ticket-generator/TicketGenerator.hpp"
#include "../visitor/Visitor.hpp"
#include "../random-number-generator/PoissonRandom.hpp"

using namespace std;

extern unsigned int N, M, w, x, y, z;

void input_params();
void output_params();
void open_museum();
void* visit(void* arg);
void init_output_lock();
void init_clock();
long long get_time();
void log(const string&);
void init_step_locks();
void init_gallery_semaphore();
void init_glass_corridor_semaphore();
bool is_valid_params(int, int, int, int, int, int);
void init_locks_and_semaphores();
void init_visitors();
void standard_ticket_holder(Visitor*);
void premium_ticket_holder(Visitor*);
void init_photo_booth_locks();

#endif // _UTIL_HPP_