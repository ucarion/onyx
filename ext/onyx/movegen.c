#include "movegen.h"

Bitboard king_movelocs[64];
Bitboard knight_movelocs[64];

void movegen_init(void) {
    init_movegen_kings();
    init_movegen_knights();
    initmagicmoves();
}

void init_movegen_kings(void) {
    int i;

    for (i = 0; i < 64; i++) {
        int rank;
        int file;
        rank = i / 8;
        file = i % 8;

        king_movelocs[i] = 0;

        if (file > 0) {
            if (rank > 0)
                king_movelocs[i] |= to_bitboard(rank - 1, file - 1);

            king_movelocs[i] |= to_bitboard(rank, file - 1);

            if (rank < 7)
                king_movelocs[i] |= to_bitboard(rank + 1, file - 1);
        }

        if (rank > 0)
            king_movelocs[i] |= to_bitboard(rank - 1, file);

        if (rank < 7)
            king_movelocs[i] |= to_bitboard(rank + 1, file);

        if (file < 7) {
            if (rank > 0)
                king_movelocs[i] |= to_bitboard(rank - 1, file + 1);

            king_movelocs[i] |= to_bitboard(rank, file + 1);

            if (rank < 7)
                king_movelocs[i] |= to_bitboard(rank + 1, file + 1);
        }
    }
}

void init_movegen_knights(void) {
    int i;

    for (i = 0; i < 64; i++) {
        int rank;
        int file;
        rank = i / 8;
        file = i % 8;

        knight_movelocs[i] = 0;

        if (file > 0) {
            if (rank > 1)
                knight_movelocs[i] |= to_bitboard(rank - 2, file - 1);
            if (rank < 6)
                knight_movelocs[i] |= to_bitboard(rank + 2, file - 1);
        }

        if (file > 1) {
            if (rank > 0)
                knight_movelocs[i] |= to_bitboard(rank - 1, file - 2);
            if (rank < 7)
                knight_movelocs[i] |= to_bitboard(rank + 1, file - 2);
        }

        if (file < 6) {
            if (rank > 0)
                knight_movelocs[i] |= to_bitboard(rank - 1, file + 2);
            if (rank < 7)
                knight_movelocs[i] |= to_bitboard(rank + 1, file + 2);
        }

        if (file < 7) {
            if (rank > 1)
                knight_movelocs[i] |= to_bitboard(rank - 2, file + 1);
            if (rank < 6)
                knight_movelocs[i] |= to_bitboard(rank + 2, file + 1);
        }
    }
}