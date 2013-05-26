#ifndef UTILS_H
#define UTILS_H

#include "board.h"

extern Bitboard FILES[8];
extern Bitboard RANKS[8];

void init_utils(void);

Bitboard square_at(int position);
Bitboard to_bitboard(int rank, int file);

#endif