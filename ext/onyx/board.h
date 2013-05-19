#ifndef BOARD_H
#define BOARD_H

typedef unsigned long long Bitboard;

typedef struct {
    Bitboard white_pawns;
    Bitboard white_knights;
    Bitboard white_bishops;
    Bitboard white_rooks;
    Bitboard white_queens;
    Bitboard white_king;

    Bitboard black_pawns;
    Bitboard black_knights;
    Bitboard black_bishops;
    Bitboard black_rooks;
    Bitboard black_queens;
    Bitboard black_king;

    Bitboard white_pieces;
    Bitboard black_pieces;
    Bitboard all_pieces;

    char fifty_move_rule;
    char en_passant_loc;

    bool white_castle_k;
    bool white_castle_q;
    bool black_castle_k;
    bool black_castle_q;

    bool white_to_move;
} Board;

#endif