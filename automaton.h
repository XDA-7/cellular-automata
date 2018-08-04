#ifndef AUTOMATON
#define AUTOMATON

#define CELL_COUNT 899
#define CELL_MIDPOINT 449

int gCells[CELL_COUNT];
int gBackCells[CELL_COUNT];
void init_automaton();
void next_iteration();

#endif