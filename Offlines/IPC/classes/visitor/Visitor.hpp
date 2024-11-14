#ifndef _VISITOR_HPP_
#define _VISITOR_HPP_

#include "../ticket-generator/TicketGenerator.hpp"

class Visitor {
    unsigned int ticket_id;
    TicketTier ticket_tier;
    unsigned int arrival_timestamp;
public:
    Visitor();
    Visitor(unsigned int, TicketTier, unsigned int);
    void visit();
    Visitor(const Visitor&);
    ~Visitor() = default;
    Visitor& operator=(const Visitor&);
};


#endif // _VISITOR_HPP_