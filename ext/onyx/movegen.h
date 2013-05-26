#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "utils.h"

extern Bitboard king_movelocs[64];

void movegen_init(void);
void init_movegen_kings(void);

#endif