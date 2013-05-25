#include "onyx.h"

void Init_onyx() {
    mOnyx = rb_define_module("Onyx");
    cMove = rb_define_class_under(mOnyx, "Move", rb_cObject);
    cBoard = rb_define_class_under(mOnyx, "Board", rb_cObject);

    rb_define_singleton_method(cMove, "new", method_move_new, 5);
    rb_define_method(cMove, "from", method_move_from, 0);
    rb_define_method(cMove, "to", method_move_to, 0);
    rb_define_method(cMove, "piece", method_move_piece, 0);
    rb_define_method(cMove, "capture?", method_move_capture, 0);
    rb_define_method(cMove, "captured", method_move_get_capture, 0);
    rb_define_method(cMove, "flag", method_move_flag, 0);
    rb_define_method(cMove, "promotion?", method_move_promotion, 0);
    rb_define_const(cMove, "NO_PIECE", INT2NUM(MOVE_NO_PIECE));
    rb_define_const(cMove, "WHITE_PAWN", INT2NUM(MOVE_WHITE_PAWN));
    rb_define_const(cMove, "BLACK_PAWN", INT2NUM(MOVE_BLACK_PAWN));
    rb_define_const(cMove, "WHITE_KNIGHT", INT2NUM(MOVE_WHITE_KNIGHT));
    rb_define_const(cMove, "BLACK_KNIGHT", INT2NUM(MOVE_BLACK_KNIGHT));
    rb_define_const(cMove, "WHITE_BISHOP", INT2NUM(MOVE_WHITE_BISHOP));
    rb_define_const(cMove, "BLACK_BISHOP", INT2NUM(MOVE_BLACK_BISHOP));
    rb_define_const(cMove, "WHITE_ROOK", INT2NUM(MOVE_WHITE_ROOK));
    rb_define_const(cMove, "BLACK_ROOK", INT2NUM(MOVE_BLACK_ROOK));
    rb_define_const(cMove, "WHITE_QUEEN", INT2NUM(MOVE_WHITE_QUEEN));
    rb_define_const(cMove, "BLACK_QUEEN", INT2NUM(MOVE_BLACK_QUEEN));
    rb_define_const(cMove, "WHITE_KING", INT2NUM(MOVE_WHITE_KING));
    rb_define_const(cMove, "BLACK_KING", INT2NUM(MOVE_BLACK_KING));
    rb_define_const(cMove, "FLAG_NO_FLAG", INT2NUM(MOVE_FLAG_NO_FLAG));
    rb_define_const(cMove, "FLAG_OO", INT2NUM(MOVE_FLAG_OO));
    rb_define_const(cMove, "FLAG_OOO", INT2NUM(MOVE_FLAG_OOO));
    rb_define_const(cMove, "FLAG_EP", INT2NUM(MOVE_FLAG_EP));
    rb_define_const(cMove, "FLAG_PROMO_KNIGHT", INT2NUM(MOVE_FLAG_PROMO_KNIGHT));
    rb_define_const(cMove, "FLAG_PROMO_BISHOP", INT2NUM(MOVE_FLAG_PROMO_BISHOP));
    rb_define_const(cMove, "FLAG_PROMO_ROOK", INT2NUM(MOVE_FLAG_PROMO_ROOK));
    rb_define_const(cMove, "FLAG_PROMO_QUEEN", INT2NUM(MOVE_FLAG_PROMO_QUEEN));

    rb_define_singleton_method(cBoard, "new", method_board_new, 0);
    rb_define_method(cBoard, "set", method_board_set, 2);
    rb_define_method(cBoard, "[]", method_board_get, 1);
    rb_define_method(cBoard, "white_to_move?", method_board_white_to_move, 0);
    rb_define_method(cBoard, "white_to_move=", method_board_set_white_to_move, 1);
    rb_define_method(cBoard, "white_castle_k?", method_board_w_oo, 0);
    rb_define_method(cBoard, "white_castle_k=", method_board_set_w_oo, 1);
    rb_define_method(cBoard, "white_castle_q?", method_board_w_ooo, 0);
    rb_define_method(cBoard, "white_castle_q=", method_board_set_w_ooo, 1);
    rb_define_method(cBoard, "black_castle_k?", method_board_b_oo, 0);
    rb_define_method(cBoard, "black_castle_k=", method_board_set_b_oo, 1);
    rb_define_method(cBoard, "black_castle_q?", method_board_b_ooo, 0);
    rb_define_method(cBoard, "black_castle_q=", method_board_set_b_ooo, 1);
    rb_define_method(cBoard, "en_passant_loc", method_board_ep, 0);
    rb_define_method(cBoard, "en_passant_loc=", method_board_set_ep, 1);
    rb_define_method(cBoard, "fifty_move_rule", method_board_fmr, 0);
    rb_define_method(cBoard, "fifty_move_rule=", method_board_set_fmr, 1);
    rb_define_method(cBoard, "do_move", method_board_do_move, 1);
    rb_define_method(cBoard, "undo_move", method_board_undo, 1);
}

int unwrap_move(VALUE move) {
    MoveWrapper *wrapped;
    Data_Get_Struct(move, MoveWrapper, wrapped);
    return wrapped->val;
}

VALUE method_move_new(VALUE class, VALUE from, VALUE to, VALUE piece, VALUE capture, VALUE flag) {
    VALUE moveWrapper;
    MoveWrapper *one;
    int move;

    char capt = (capture == Qfalse ? MOVE_NO_PIECE : NUM2INT(capture));

    move = new_move(NUM2INT(from), NUM2INT(to), NUM2INT(piece), capt, NUM2INT(flag));
    moveWrapper = Data_Make_Struct(cMove, MoveWrapper, 0, free, one);

    one->val = move;

    rb_obj_call_init(moveWrapper, 0, 0);
    
    return moveWrapper;
}

// Move methods
VALUE method_move_from(VALUE self) {
    int move = unwrap_move(self);
    return INT2NUM(get_from(move));
}

VALUE method_move_to(VALUE self) {
    int move = unwrap_move(self);
    return INT2NUM(get_to(move));
}
VALUE method_move_piece(VALUE self) {
    int move = unwrap_move(self);
    switch (INT2NUM(get_piece(move))) {
    case MOVE_WHITE_PAWN:
    case MOVE_BLACK_PAWN:
        return ID2SYM(rb_intern("pawn"));
    case MOVE_WHITE_KNIGHT:
    case MOVE_BLACK_KNIGHT:
        return ID2SYM(rb_intern("knight"));
    case MOVE_WHITE_BISHOP:
    case MOVE_BLACK_BISHOP:
        return ID2SYM(rb_intern("bishop"));
    case MOVE_WHITE_ROOK:
    case MOVE_BLACK_ROOK:
        return ID2SYM(rb_intern("rook"));
    case MOVE_WHITE_QUEEN:
    case MOVE_BLACK_QUEEN:
        return ID2SYM(rb_intern("queen"));
    case MOVE_WHITE_KING:
    case MOVE_BLACK_KING:
        return ID2SYM(rb_intern("king"));
    default:
        return ID2SYM(rb_intern("unknown piece"));
    }
}

VALUE method_move_capture(VALUE self) {
    int move = unwrap_move(self);
    if (get_capture(move))
        return Qtrue;
    return Qfalse;
}

VALUE method_move_get_capture(VALUE self) {
    int move = unwrap_move(self);
    return INT2NUM(get_capture(move));
}

VALUE method_move_flag(VALUE self) {
    int move = unwrap_move(self);
    return INT2NUM(get_flag(move));
}

VALUE method_move_promotion(VALUE self) {
    int move = unwrap_move(self);
    if (is_promotion(move))
        return Qtrue;
    return Qfalse;
}

// Board methods
VALUE method_board_new(VALUE class) {
    VALUE rb_board;
    Board *board = new_empty_board();

    rb_board = Data_Make_Struct(cBoard, Board, 0, free, board);

    rb_obj_call_init(rb_board, 0, 0);

    return rb_board;
}

VALUE method_board_set(VALUE self, VALUE positionVal, VALUE pieceName) {
    Board* board;
    char *piece;
    int position;
    Bitboard bitmap;

    Data_Get_Struct(self, Board, board);
    piece = RSTRING_PTR(rb_inspect(pieceName));
    position = NUM2INT(positionVal);
    bitmap = square_at(position);

    if (!strcmp(piece, ":white_pawn"))
        board->white_pawns |= bitmap;
    else if (!strcmp(piece, ":black_pawn"))
        board->black_pawns |= bitmap;
    else if (!strcmp(piece, ":white_knight"))
        board->white_knights |= bitmap;
    else if (!strcmp(piece, ":black_knight"))
        board->black_knights |= bitmap;
    else if (!strcmp(piece, ":white_bishop"))
        board->white_bishops |= bitmap;
    else if (!strcmp(piece, ":black_bishop"))
        board->black_bishops |= bitmap;
    else if (!strcmp(piece, ":white_rook"))
        board->white_rooks |= bitmap;
    else if (!strcmp(piece, ":black_rook"))
        board->black_rooks |= bitmap;
    else if (!strcmp(piece, ":white_queen"))
        board->white_queens |= bitmap;
    else if (!strcmp(piece, ":black_queen"))
        board->black_queens |= bitmap;
    else if (!strcmp(piece, ":white_king"))
        board->white_king |= bitmap;
    else if (!strcmp(piece, ":black_king"))
        board->black_king |= bitmap;
    else
        rb_raise(rb_eStandardError, "Unknown piece");

    return Qnil;
}

VALUE method_board_get(VALUE self, VALUE positionVal) {
    Board* board;
    int position;
    Bitboard bitmap;

    Data_Get_Struct(self, Board, board);
    position = NUM2INT(positionVal);
    bitmap = square_at(position);

    if (board->white_pawns & bitmap)
        return ID2SYM(rb_intern("white_pawn"));
    else if (board->black_pawns & bitmap)
        return ID2SYM(rb_intern("black_pawn"));
    else if (board->white_knights & bitmap)
        return ID2SYM(rb_intern("white_knight"));
    else if (board->black_knights & bitmap)
        return ID2SYM(rb_intern("black_knight"));
    else if (board->white_bishops & bitmap)
        return ID2SYM(rb_intern("white_bishop"));
    else if (board->black_bishops & bitmap)
        return ID2SYM(rb_intern("black_bishop"));
    else if (board->white_rooks & bitmap)
        return ID2SYM(rb_intern("white_rook"));
    else if (board->black_rooks & bitmap)
        return ID2SYM(rb_intern("black_rook"));
    else if (board->white_queens & bitmap)
        return ID2SYM(rb_intern("white_queen"));
    else if (board->black_queens & bitmap)
        return ID2SYM(rb_intern("black_queen"));
    else if (board->white_king & bitmap)
        return ID2SYM(rb_intern("white_king"));
    else if (board->black_king & bitmap)
        return ID2SYM(rb_intern("black_king"));
    else
        return Qnil;
}

VALUE method_board_white_to_move(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (board->white_to_move)
        return Qtrue;
    return Qfalse;
}

VALUE method_board_set_white_to_move(VALUE self, VALUE whiteToMove) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (RTEST(whiteToMove))
        board->white_to_move = true;
    else
        board->white_to_move = false;

    return Qnil;
}

VALUE method_board_w_oo(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (board->white_castle_k)
        return Qtrue;
    return Qfalse;
}

VALUE method_board_set_w_oo(VALUE self, VALUE w_oo) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (RTEST(w_oo))
        board->white_castle_k = true;
    else
        board->white_castle_k = false;

    return Qnil;
}

VALUE method_board_w_ooo(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (board->white_castle_q)
        return Qtrue;
    return Qfalse;
}

VALUE method_board_set_w_ooo(VALUE self, VALUE w_ooo) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (RTEST(w_ooo))
        board->white_castle_q = true;
    else
        board->white_castle_q = false;

    return Qnil;
}

VALUE method_board_b_oo(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (board->black_castle_k)
        return Qtrue;
    return Qfalse;
}

VALUE method_board_set_b_oo(VALUE self, VALUE b_oo) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (RTEST(b_oo))
        board->black_castle_k = true;
    else
        board->black_castle_k = false;

    return Qnil;
}

VALUE method_board_b_ooo(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (board->black_castle_q)
        return Qtrue;
    return Qfalse;
}

VALUE method_board_set_b_ooo(VALUE self, VALUE b_ooo) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    if (RTEST(b_ooo))
        board->black_castle_q = true;
    else
        board->black_castle_q = false;

    return Qnil;
}

VALUE method_board_ep(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    return INT2NUM(board->en_passant_loc);
}

VALUE method_board_set_ep(VALUE self, VALUE ep) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    board->en_passant_loc = NUM2INT(ep);

    return Qnil;
}

VALUE method_board_fmr(VALUE self) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    return INT2NUM(board->fifty_move_rule);    
}

VALUE method_board_set_fmr(VALUE self, VALUE fmr) {
    Board* board;

    Data_Get_Struct(self, Board, board);

    board->fifty_move_rule = NUM2INT(fmr);

    return Qnil;
}

VALUE method_board_do_move(VALUE self, VALUE aMove) {
    Board* board;
    int move;

    Data_Get_Struct(self, Board, board);
    move = unwrap_move(aMove);

    make_move(board, move);

    return Qnil;
}

VALUE method_board_undo(VALUE self, VALUE aMove) {
    Board* board;
    int move;

    Data_Get_Struct(self, Board, board);
    move = unwrap_move(aMove);

    unmake_move(board, move);

    return Qnil;
}