#include "Visitor.hpp"

Visitor::Visitor() :
    ticket_id(0), ticket_tier(TicketTier::INVALID), arrival_delay(0), status(Status::ARRIVAL_A) {}

Visitor::Visitor(unsigned int ticket_id, TicketTier ticket_tier, unsigned int arrival_timestamp, Status status) :
    ticket_id(ticket_id), ticket_tier(ticket_tier), arrival_delay(arrival_timestamp), status(status) {}

Visitor::Visitor(const Visitor& visitor) :
    ticket_id(visitor.ticket_id), ticket_tier(visitor.ticket_tier), arrival_delay(visitor.arrival_delay), status(visitor.status) {}

Visitor& Visitor::operator=(const Visitor& visitor) {
    ticket_id = visitor.ticket_id;
    ticket_tier = visitor.ticket_tier;
    arrival_delay = visitor.arrival_delay;
    status = visitor.status;
    return *this;
}

ostream& operator<<(ostream& os, const Visitor& visitor) {
    os << "Visitor: " << visitor.ticket_id << " " << visitor.ticket_tier << " " << visitor.arrival_delay;
    return os;
}

unsigned int Visitor::get_arrival_delay() const {
    return arrival_delay;
}

string Visitor::get_status(long long timestamp, unsigned int step) const {
    switch(status) {
        case Status::ARRIVAL_A:
            return "Visitor " + to_string(ticket_id) + " has arrived at A at timestamp " + to_string(timestamp);
        case Status::ARRIVAL_B:
            return "Visitor " + to_string(ticket_id) + " has arrived at B at timestamp " + to_string(timestamp);
        case Status::STEPS:
            return "Visitor " + to_string(ticket_id) + " is at step " + to_string(step) + " at timestamp " + to_string(timestamp);
        case Status::C_GALLERY_1_ENTRANCE:
            return "Visitor " + to_string(ticket_id) + " is at C (entered Gallery 1) at time " + to_string(timestamp);
        case Status::D_GALLERY_1_EXIT:
            return "Visitor " + to_string(ticket_id) + " is at D (exiting Gallery 1) at time " + to_string(timestamp);
        case Status::E_GALLERY_2_ENTRANCE:
            return "Visitor " + to_string(ticket_id) + " is at E (entered Gallery 2) at time " + to_string(timestamp);
        case Status::ENTRY_PHOTO_BOOTH:
            return "Visitor " + to_string(ticket_id) + " is about to enter the photo booth at timestamp " + to_string(timestamp);
        case Status::INSIDE_PHOTO_BOOTH:
            return "Visitor " + to_string(ticket_id) + " is inside the photo booth at timestamp " + to_string(timestamp);
        case Status::F_EXIT:
            return "Visitor " + to_string(ticket_id) + " is at F (exiting Gallery 2) at time " + to_string(timestamp);
        default:
            return "";
    }
}

void Visitor::set_status(Status status) {
    this->status = status;
}

TicketTier Visitor::get_ticket_tier() const {
    return ticket_tier;
}
