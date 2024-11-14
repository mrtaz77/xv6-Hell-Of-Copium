#ifndef _ID_GENERATOR_H_
#define _ID_GENERATOR_H_

#include "Constants.h"
#include <stdlib.h>

enum TicketTier {
    STANDARD,
    PREMIUM,
};

typedef struct {
    unsigned int standard_ticket_id;
    unsigned int premium_ticket_id;
} Id_Generator;

void update_id_generator_instance(enum TicketTier);
void clear_id_generator_instance();
unsigned int get_ticket_id(enum TicketTier);

#endif // _ID_GENERATOR_H_
