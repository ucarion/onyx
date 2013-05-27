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

// TODO: This could be done faster if we assume there's only one bit set in the passed Bitboard.
int to_index(Bitboard i) {
    int x, y;
    if (i == 0) return 64;
    int n = 63;
    y = (int)i; if (y != 0) { n = n -32; x = y; } else x = (int)(i>>32);
    y = x <<16; if (y != 0) { n = n -16; x = y; }
    y = x << 8; if (y != 0) { n = n - 8; x = y; }
    y = x << 4; if (y != 0) { n = n - 4; x = y; }
    y = x << 2; if (y != 0) { n = n - 2; x = y; }
    return n - ((x << 1) >> 31);
}