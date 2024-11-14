#include "TicketGenerator.hpp"

TicketGenerator* TicketGenerator::ticket_generator = nullptr;

TicketGenerator::TicketGenerator() {
    standard_ticket_id = STANDARD_TICKET_START_ID - 1;
    premium_ticket_id = PREMIUM_TICKET_START_ID - 1;
}

TicketGenerator* TicketGenerator::get_instance() {
    if(ticket_generator == nullptr) {
        ticket_generator = new TicketGenerator();
    }
    return ticket_generator;
}

unsigned int TicketGenerator::get_ticket_id(enum TicketTier tier) {
    if(tier == STANDARD) {
        standard_ticket_id++;
        standard_ticket_id %= (STANDARD_TICKET_END_ID + 1);
        if(!standard_ticket_id) standard_ticket_id = STANDARD_TICKET_START_ID;
        return standard_ticket_id;
    } else if (tier == PREMIUM) {
        premium_ticket_id++;
        premium_ticket_id %= (PREMIUM_TICKET_END_ID + 1);
        if(!premium_ticket_id) premium_ticket_id = PREMIUM_TICKET_START_ID;
        return premium_ticket_id;
    }
    return TicketTier::INVALID;
}

void TicketGenerator::destroy_instance() {
    delete ticket_generator;
    ticket_generator = nullptr;
}
