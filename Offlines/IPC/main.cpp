#include <iostream>

#include "classes/random-number-generator/PoissonRandom.hpp"
#include "classes/ticket-generator/TicketGenerator.hpp"

using namespace std;

int main() {
    for(int i = 0; i < 10; i++) {
        cout << rand_range(2, 6) << endl;
    }
    TicketGenerator* ticket_generator = TicketGenerator::get_instance();
    for(int i = 0; i < 95; i++) {
        ticket_generator->get_ticket_id(STANDARD);
        ticket_generator->get_ticket_id(PREMIUM);
    }
    for(int i = 0; i < 10; i++) {
        cout << ticket_generator->get_ticket_id(STANDARD) << endl;
        cout << ticket_generator->get_ticket_id(PREMIUM) << endl;
    }

    TicketGenerator::destroy_instance();
}