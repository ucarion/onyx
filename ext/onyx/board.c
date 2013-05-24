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

BoardRecord* new_record(Board* board) {
    BoardRecord* record = malloc(sizeof(BoardRecord));

    record->fifty_move_rule = board->fifty_move_rule;
    record->en_passant_loc = board->en_passant_loc;
    record->white_castle_k = board->white_castle_k;
    record->white_castle_q = board->white_castle_q;
    record->black_castle_k = board->black_castle_k;
    record->black_castle_q = board->black_castle_q;

    return record;
}

void update_special_bitboards(Board* board) {
    board->white_pieces = 
    board->white_pawns | board->white_knights | board->white_bishops | board->white_rooks | board->white_queens | board->white_king;

    board->black_pieces = 
    board->black_pawns | board->black_knights | board->black_bishops | board->black_rooks | board->black_queens | board->black_king;

    board->all_pieces = board->white_pieces | board->black_pieces;
}

void make_move(Board* board, Move move) {
    char from;
    char to;
    Bitboard from_mask;
    Bitboard to_mask;
    char piece;
    char capt;
    char flag;
    Bitboard move_mask;

    from = get_from(move);
    to = get_to(move);
    from_mask = square_at(from);
    to_mask = square_at(to);
    piece = get_piece(move);
    capt = get_capture(move);
    flag = get_flag(move);
    move_mask = from_mask | to_mask;

    board->movelist[board->end_of_search] = move;
    board->history[board->end_of_search] = *new_record(board);

    board->end_of_search++;
    board->fifty_move_rule++;

    if (capt) {
        char to_remove;
        Bitboard to_remove_mask;

        to_remove = to;

        if (flag == MOVE_FLAG_EP)
            to_remove = board->white_to_move ? to - 8 : to + 8;

        to_remove_mask = square_at(to_remove);

        board->white_pawns &= ~to_remove_mask;
        board->white_knights &= ~to_remove_mask;
        board->white_bishops &= ~to_remove_mask;
        board->white_rooks &= ~to_remove_mask;
        board->white_queens &= ~to_remove_mask;

        board->black_pawns &= ~to_remove_mask;
        board->black_knights &= ~to_remove_mask;
        board->black_bishops &= ~to_remove_mask;
        board->black_rooks &= ~to_remove_mask;
        board->black_queens &= ~to_remove_mask;

        board->fifty_move_rule = 0;
    }

    // though this value may be updated later, it is irrelevant now and should be default
    // be resetted.
    board->en_passant_loc = -1;

    switch (piece) {
        case MOVE_WHITE_PAWN:
            board->fifty_move_rule = 0;
            if (from + 16 == to)
                board->en_passant_loc = from + 8;
            
            switch (flag) {
                case MOVE_FLAG_PROMO_QUEEN:
                    board->white_queens |= to_mask;
                    board->white_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_KNIGHT:
                    board->white_knights |= to_mask;
                    board->white_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_ROOK:
                    board->white_rooks |= to_mask;
                    board->white_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_BISHOP:
                    board->white_bishops |= to_mask;
                    board->white_pawns &= ~from_mask;
                    break;
                default: // so... not a promotion
                    board->white_pawns ^= move_mask;
                    break;
            }
            break;
        
        case MOVE_BLACK_PAWN:
            board->fifty_move_rule = 0;
            if (from - 16 == to)
                board->en_passant_loc = from - 8;

            switch (flag) {
                case MOVE_FLAG_PROMO_QUEEN:
                    board->black_queens |= to_mask;
                    board->black_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_KNIGHT:
                    board->black_knights |= to_mask;
                    board->black_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_ROOK:
                    board->black_rooks |= to_mask;
                    board->black_pawns &= ~from_mask;
                    break;
                case MOVE_FLAG_PROMO_BISHOP:
                    board->black_bishops |= to_mask;
                    board->black_pawns &= ~from_mask;
                    break;
                default:
                    board->white_pawns ^= move_mask;
                    break;
            }
            break;

        case MOVE_WHITE_KNIGHT:
            board->white_knights ^= move_mask;
            break;
        
        case MOVE_BLACK_KNIGHT:
            board->black_knights ^= move_mask;
            break;
        
        case MOVE_WHITE_BISHOP:
            board->white_bishops ^= move_mask;
            break;
        
        case MOVE_BLACK_BISHOP:
            board->black_bishops ^= move_mask;
            break;
        
        case MOVE_WHITE_ROOK:
            board->white_rooks ^= move_mask;
            break;
        
        case MOVE_BLACK_ROOK:
            board->black_rooks ^= move_mask;
            break;
        
        case MOVE_WHITE_QUEEN:
            board->white_queens ^= move_mask;
            break;
        
        case MOVE_BLACK_QUEEN:
            board->black_queens ^= move_mask;
            break;
        
        case MOVE_WHITE_KING:
            if (flag == MOVE_FLAG_OO) {
                Bitboard rook_move_mask = square_at(5) | square_at(7);
                board->white_king = square_at(6);
                board->white_rooks ^= rook_move_mask;
            }
            else if (flag == MOVE_FLAG_OOO) {
                Bitboard rook_move_mask = square_at(0) | square_at(3);
                board->white_king = square_at(2);
                board->white_rooks ^= rook_move_mask;
            }
            else
                board->white_king ^= move_mask;
            break;
        
        case MOVE_BLACK_KING:
            if (flag == MOVE_FLAG_OO) {
                Bitboard rook_move_mask = square_at(5 + 56) | square_at(7 + 56);
                board->black_king = square_at(6 + 56);
                board->black_rooks ^= rook_move_mask;
            }
            else if (flag == MOVE_FLAG_OOO) {
                Bitboard rook_move_mask = square_at(56) | square_at(56 + 3);
                board->black_king = square_at(56 + 2);
                board->black_rooks ^= rook_move_mask;
            }
            else
                board->black_king ^= move_mask;
            break;
        }

        update_special_bitboards(board);

        if (board->white_to_move) {
            if (move_mask & 0x90ULL) // 0x90 = e1 | h1
                board->white_castle_k = 0;
            if (move_mask & 0x11ULL) // 0x11 = e1 | a1
                board->white_castle_q = 0;
        } else {
        if (move_mask & (0x90ULL << 56))
            board->black_castle_k = 0;
        if (move_mask & (0x11ULL << 56))
            board->black_castle_q = 0;
        }

    board->white_to_move = (board->white_to_move ? false : true);
}

void unmake_move(Board* board, Move move) {
    char from;
    char to;
    Bitboard from_mask;
    Bitboard to_mask;
    char piece;
    char capt;
    char flag;
    Bitboard move_mask;

    from = get_from(move);
    to = get_to(move);
    from_mask = 1ULL << from;
    to_mask = 1ULL << to;
    piece = get_piece(move);
    capt = get_capture(move);
    flag = get_flag(move);
    move_mask = from_mask | to_mask;

    switch (piece) {
        case MOVE_WHITE_PAWN:
            // if the last move was a promo, then there is no pawn at TO;
            // thus, this will create a pawn at both FROM and TO. We get
            // rid of this extra pawn in unmake_white_promotion.
            board->white_pawns ^= move_mask;

            if (capt) {
                if (flag == MOVE_FLAG_EP)
                    board->black_pawns |= 1ULL << (to - 8);
                else
                    unmake_capture(board, to_mask, capt);
            }

            if (is_promotion(move))
                unmake_white_promotion(board, to_mask, flag);
            break;
        case MOVE_BLACK_PAWN:
            // see comment for case MOVE_WHITE_PAWN.
            board->black_pawns ^= move_mask;

            if (capt) {
                if (flag == MOVE_FLAG_EP)
                    board->white_pawns |= 1ULL << (to + 8);
                else
                    unmake_capture(board, to_mask, capt);
            }

            if (is_promotion(move))
                unmake_black_promotion(board, to_mask, flag);
            break;
        case MOVE_WHITE_KNIGHT:
            board->white_knights ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_BLACK_KNIGHT:
            board->black_knights ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_WHITE_BISHOP:
            board->white_bishops ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_BLACK_BISHOP:
            board->black_bishops ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_WHITE_ROOK:
            board->white_rooks ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_BLACK_ROOK:
            board->black_rooks ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_WHITE_QUEEN:
            board->white_queens ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_BLACK_QUEEN:
            board->black_queens ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);
            break;
        case MOVE_WHITE_KING:
            board->white_king ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);

            if (flag == MOVE_FLAG_OO) {
                Bitboard rook_move_mask = (1ULL << 5) | (1ULL << 7);
                board->white_rooks ^= rook_move_mask;
            }
            else if (flag == MOVE_FLAG_OOO) {
                Bitboard rook_move_mask = 1ULL | (1ULL << 3);
                board->white_rooks ^= rook_move_mask;
            }
            break;
        case MOVE_BLACK_KING:
            board->black_king ^= move_mask;

            if (capt)
                unmake_capture(board, to_mask, capt);

            if (flag == MOVE_FLAG_OO) {
                Bitboard rook_move_mask = (1ULL << (5 + 56)) | (1ULL << (7 + 56));
                board->black_rooks ^= rook_move_mask;
            }
            else if (flag == MOVE_FLAG_OOO) {
                Bitboard rook_move_mask = (1ULL << 56) | (1ULL << (3 + 56));
                board->black_rooks ^= rook_move_mask;
            }
            break;
    }

    // now go back in time ...
    board->end_of_search--;
    board->white_castle_k = board->history[board->end_of_search].white_castle_k;
    board->white_castle_q = board->history[board->end_of_search].white_castle_q;
    board->black_castle_k = board->history[board->end_of_search].black_castle_k;
    board->black_castle_q = board->history[board->end_of_search].black_castle_q;
    board->en_passant_loc = board->history[board->end_of_search].en_passant_loc;
    board->fifty_move_rule = board->history[board->end_of_search].fifty_move_rule;

    board->white_to_move = (board->white_to_move ? 0 : 1);
}

// handles replacing a captured piece; this won't work for ep captures
void unmake_capture(Board* board, Bitboard sq, char piece) {
    switch (piece) {
        case MOVE_WHITE_PAWN:
            board->white_pawns |= sq;
            break;
        case MOVE_BLACK_PAWN:
            board->black_pawns |= sq;
            break;
        case MOVE_WHITE_KNIGHT:
            board->white_knights |= sq;
            break;
        case MOVE_BLACK_KNIGHT:
            board->black_knights |= sq;
            break;
        case MOVE_WHITE_BISHOP:
            board->white_bishops |= sq;
            break;
        case MOVE_BLACK_BISHOP:
            board->black_bishops |= sq;
            break;
        case MOVE_WHITE_ROOK:
            board->white_rooks |= sq;
            break;
        case MOVE_BLACK_ROOK:
            board->black_rooks |= sq;
            break;
        case MOVE_WHITE_QUEEN:
            board->white_queens |= sq;
            break;
        case MOVE_BLACK_QUEEN:
            board->black_queens |= sq;
            break;
    }
}

// undoes a white promotion; this function assumes there is a white
// pawn at both FROM and TO.
void unmake_white_promotion(Board* board, Bitboard to, char flag) {
    board->white_pawns &= ~to; // remove the pawn that isn't there
    switch (flag) { // remove the promoted piece{
        case MOVE_FLAG_PROMO_KNIGHT:
            board->white_knights &= ~to;
            break;
        case MOVE_FLAG_PROMO_BISHOP:
            board->white_bishops &= ~to;
            break;
        case MOVE_FLAG_PROMO_ROOK:
            board->white_rooks &= ~to;
            break;
        case MOVE_FLAG_PROMO_QUEEN:
            board->white_queens &= ~to;
            break;
    }
}

// undoes a black promotion; this function assumes there is a black
// pawn at both FROM and TO.
void unmake_black_promotion(Board* board, Bitboard to, char flag) {
    board->black_pawns &= ~to;
    switch (flag) {
        case MOVE_FLAG_PROMO_KNIGHT:
            board->black_knights &= ~to;
            break;
        case MOVE_FLAG_PROMO_BISHOP:
            board->black_bishops &= ~to;
            break;
        case MOVE_FLAG_PROMO_ROOK:
            board->black_rooks &= ~to;
            break;
        case MOVE_FLAG_PROMO_QUEEN:
            board->black_queens &= ~to;
            break;
    }
}