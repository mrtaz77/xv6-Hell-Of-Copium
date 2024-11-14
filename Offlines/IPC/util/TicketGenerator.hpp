#ifndef _ID_GENERATOR_HPP_
#define _ID_GENERATOR_HPP_

#include "Constants.hpp"

enum TicketTier {
    INVALID,
    STANDARD,
    PREMIUM,
};

class TicketGenerator {
private:
    unsigned int standard_ticket_id;
    unsigned int premium_ticket_id;
    static TicketGenerator* ticket_generator;

    TicketGenerator();
public:
    static TicketGenerator* get_instance();
    unsigned int get_ticket_id(enum TicketTier);
    static void destroy_instance();
};

#endif // _ID_GENERATOR_HPP_
