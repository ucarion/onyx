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

void update_special_bitboards(Board* board) {
    board->white_pieces = 
        board->white_pawns | board->white_knights | board->white_bishops | board->white_rooks | board->white_queens | board->white_king;

    board->black_pieces = 
        board->black_pawns | board->black_knights | board->black_bishops | board->black_rooks | board->black_queens | board->black_king;

    board->all_pieces = board->white_pieces | board->black_pieces;
}