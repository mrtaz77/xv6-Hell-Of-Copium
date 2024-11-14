#ifndef _VISITOR_HPP_
#define _VISITOR_HPP_

#include <iostream>

#include "../ticket-generator/TicketGenerator.hpp"

using namespace std;

enum class Status {
    ARRIVAL_A,
    ARRIVAL_B,
    STEPS,
    C_GALLERY_1_ENTRANCE,
    D_GALLERY_1_EXIT,
    E_GALLERY_2_ENTRANCE,
    ENTRY_PHOTO_BOOTH,
    INSIDE_PHOTO_BOOTH,
    EXIT_F
};

class Visitor {
    unsigned int ticket_id;
    TicketTier ticket_tier;
    unsigned int arrival_delay;
    Status status;
public:
    Visitor();
    Visitor(unsigned int, TicketTier, unsigned int, Status);
    Visitor(const Visitor&);
    ~Visitor() = default;
    Visitor& operator=(const Visitor&);
    friend ostream& operator<<(ostream&, const Visitor&);
    unsigned int get_arrival_delay() const;
    void set_status(Status);
    string get_status(long long timestamp, unsigned int step = -1) const;
};


#endif // _VISITOR_HPP_