#include <stdio.h>
#include "util/Id_generator.h"

int main() {
    for(int i = 0; i < 95; i++) {
        get_ticket_id(STANDARD);get_ticket_id(PREMIUM);
    }
    for(int i = 0; i < 10; i++) {
        printf("Standard Ticket ID: %u\n", get_ticket_id(STANDARD));
        printf("Premium Ticket ID: %u\n", get_ticket_id(PREMIUM));
    }
    clear_id_generator_instance();
}