#include "Visitor.hpp"

Visitor::Visitor() :
    ticket_id(0), ticket_tier(TicketTier::INVALID), arrival_timestamp(0) {}

Visitor::Visitor(unsigned int ticket_id, TicketTier ticket_tier, unsigned int arrival_timestamp) :
    ticket_id(ticket_id), ticket_tier(ticket_tier), arrival_timestamp(arrival_timestamp) {}

void Visitor::visit() {

}

Visitor::Visitor(const Visitor& visitor) :
    ticket_id(visitor.ticket_id), ticket_tier(visitor.ticket_tier), arrival_timestamp(visitor.arrival_timestamp) {}

Visitor& Visitor::operator=(const Visitor& visitor) {
    ticket_id = visitor.ticket_id;
    ticket_tier = visitor.ticket_tier;
    arrival_timestamp = visitor.arrival_timestamp;
    return *this;
}