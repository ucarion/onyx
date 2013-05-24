#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdbool.h>

typedef unsigned long long Bitboard;

#include "move.h"
#include "utils.h"

#define MAX_GAME_PLY 1024 // maximum game length
#define MAX_TOTAL_MOVES 4096 // maximum available moves in a position

typedef struct {
    char fifty_move_rule;
    char en_passant_loc;
    bool white_castle_k;
    bool white_castle_q;
    bool black_castle_k;
    bool black_castle_q;
} BoardRecord;

typedef struct {
    Move movelist[MAX_GAME_PLY];
    BoardRecord history[MAX_GAME_PLY];

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

    // move_number is our current ply count in the game
    // end_of_search is the deepest ply reached while searching
    // end_of_search - move_number is how far into the future we've searched.
    int move_number;
    int end_of_search;

    char fifty_move_rule;
    char en_passant_loc;

    bool white_castle_k;
    bool white_castle_q;
    bool black_castle_k;
    bool black_castle_q;

    bool white_to_move;
} Board;

Board* new_empty_board();
void update_special_bitboards(Board* board);
void make_move(Board* board, Move move);
void unmake_move(Board* board, Move move);
void unmake_capture(Board* board, Bitboard sq, char piece);
void unmake_white_promotion(Board* board, Bitboard to, char flag);
void unmake_black_promotion(Board* board, Bitboard to, char flag);

#endif