#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if (head == NULL) {
        return 0;
    }
    
    struct node *tortoise = head;
    struct node *hare = head;
    
    while (hare != NULL && hare->next != NULL) {
        tortoise = tortoise->next;
        hare = hare->next->next;
        
        if (tortoise == hare) {
            return 1;
        }
    }
    
    return 0;
}
