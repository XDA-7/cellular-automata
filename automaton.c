#include <stdio.h>
#include "automaton.h"

void init_automaton() {
    for (int i = 0; i < CELL_COUNT; i++) {
        gBackCells[i] = 0;
        gCells[i] = 0;
    }

    gBackCells[CELL_MIDPOINT] = 1;
    gCells[CELL_MIDPOINT] = 1;
}

int rule_30(int left, int center, int right) {
    int combined_value = (left << 2) | (center << 1) | right;
    switch (combined_value)
    {
        case 0:
            return 0;
            break;
        
        case 1:
            return 1;
            break;
        
        case 2:
            return 1;
            break;
        
        case 3:
            return 1;
            break;
        
        case 4:
            return 1;
            break;
        
        case 5:
            return 0;
            break;
        
        case 6:
            return 0;
            break;
        
        case 7:
            return 0;
            break;
    
        default:
            break;
    }
}

void next_iteration() {
    for (int i = 1; i < CELL_COUNT - 1; i++) {
        gCells[i] = rule_30(gBackCells[i - 1], gBackCells[i], gBackCells[i + 1]);
    }

    for (int i = 1; i < CELL_COUNT - 1; i++) {
        gBackCells[i] = gCells[i];
    }
}