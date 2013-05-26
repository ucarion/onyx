#include "utils.h"

Bitboard FILES[8];
Bitboard RANKS[8];

void init_utils(void) {
    int i;

    for (i = 0; i < 8; i++) {
        FILES[i] = RANKS[i] = 0;
    }

    for (i = 0; i < 64; i++) {
        FILES[i % 8] |= square_at(i);
        RANKS[i / 8] |= square_at(i);
    }
}

Bitboard square_at(int position) {
    return 1ULL << position;
}

Bitboard to_bitboard(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}