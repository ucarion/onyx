#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "utils.h"
#include "magicmoves.h"

extern Bitboard king_movelocs[64];
extern Bitboard knight_movelocs[64];

void movegen_init(void);
void init_movegen_kings(void);
void init_movegen_knights(void);

#endif