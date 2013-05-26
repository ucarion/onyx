#include "movegen.h"

Bitboard king_movelocs[64];
Bitboard knight_movelocs[64];
Bitboard rank_masks[64];
Bitboard file_masks[64];
Bitboard a1h8_masks[64];
Bitboard a8h1_masks[64];

void movegen_init(void) {
    init_movegen_kings();
    init_movegen_knights();
    init_movegen_rook_masks();
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

void init_movegen_rook_masks(void) {
    int i;

    for (i = 0; i < 64; i++) {
        int rank, file;

        rank = i / 8;
        file = i % 8;

        rank_masks[i]  = to_bitboard(rank, 1) | to_bitboard(rank, 2) | to_bitboard(rank, 3);
        rank_masks[i] |= to_bitboard(rank, 4) | to_bitboard(rank, 5) | to_bitboard(rank, 6);
        file_masks[i]  = to_bitboard(1, file) | to_bitboard(2, file) | to_bitboard(3, file);
        file_masks[i] |= to_bitboard(4, file) | to_bitboard(5, file) | to_bitboard(6, file);
    }
}

void init_movegen_a1h8_masks(void) {
    int i;

    for (i = 0; i < 64; i++) {
        int rank;
        int file;
        int diag;

        rank = i / 8;
        file = i % 8;
        diag = file - rank;

        a1h8_masks[i] = 0;

        if (diag >= 0) {
            int j;
            for (j = 1; j < 7 - diag; j++)
                a1h8_masks[i] |= to_bitboard(j, diag + j);
        } else {
            int j;
            for (j = 1; j < 7 + diag; j++)
                a1h8_masks[i] |= to_bitboard(j - diag, j);
        }
    }
}

void init_movegen_a8h1_masks(void) {
    int i;

    for (i = 0; i < 64; i++) {
        int rank;
        int file;
        int diag;

        rank = i / 8;
        file = i % 8;
        diag = file + rank;

        a8h1_masks[i] = 0;

        if (diag < 8) {
            int j;
            for (j = 1; j < diag; j++)
                a8h1_masks[i] |= to_bitboard(diag - j, j);
        } else {
            int j;
            for (j = 2; j < 15 - diag; j++)
                a8h1_masks[i] |= to_bitboard(diag + j - 8, 8 - j);
        }
    }
}