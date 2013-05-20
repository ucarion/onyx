#include "board.h"

Board* new_empty_board() {
    Board* board = malloc(sizeof(Board));

    board->white_pawns = 0;
    board->white_knights = 0;
    board->white_bishops = 0;
    board->white_rooks = 0;
    board->white_queens = 0;
    board->white_king = 0;

    board->black_pawns = 0;
    board->black_knights = 0;
    board->black_bishops = 0;
    board->black_rooks = 0;
    board->black_queens = 0;
    board->black_king = 0;

    board->white_pieces = 0;
    board->black_pieces = 0;
    board->all_pieces = 0;

    board->white_castle_k = false;
    board->white_castle_q = false;
    board->black_castle_k = false;
    board->black_castle_q = false;

    board->fifty_move_rule = 0;
    board->en_passant_loc = -1;

    board->white_to_move = false;

    return board;
}