#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "utils.h"

extern Bitboard king_movelocs[64];
extern Bitboard knight_movelocs[64];
extern Bitboard rank_masks[64];
extern Bitboard file_masks[64];

void movegen_init(void);
void init_movegen_kings(void);
void init_movegen_knights(void);
void init_movegen_rook_masks(void);

#endif