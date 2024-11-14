#include "Id_generator.h"

static Id_Generator* instance = NULL;

void update_id_generator_instance(enum TicketTier tier) {
    if(instance == NULL) {
        instance = (Id_Generator*) malloc(sizeof(Id_Generator));

        instance->standard_ticket_id = STANDARD_TICKET_START_ID - 1 ;
        instance->premium_ticket_id = PREMIUM_TICKET_START_ID - 1;
    }

    if (tier == STANDARD) {
        instance->standard_ticket_id++;
        instance->standard_ticket_id %= (STANDARD_TICKET_END_ID + 1);
        if(!instance->standard_ticket_id) instance->standard_ticket_id = STANDARD_TICKET_START_ID;
    }
    else if (tier == PREMIUM) {
        instance->premium_ticket_id++;
        instance->premium_ticket_id %= (PREMIUM_TICKET_END_ID + 1);
        if(!instance->premium_ticket_id) instance->premium_ticket_id = PREMIUM_TICKET_START_ID;
    }
}

unsigned int get_ticket_id(enum TicketTier tier) {
    update_id_generator_instance(tier);

    if(tier == STANDARD) {
        return instance->standard_ticket_id;
    } else {
        return instance->premium_ticket_id;
    }
}

void clear_id_generator_instance() {
    if(instance != NULL) {
        free(instance);
        instance = NULL;
    }
}