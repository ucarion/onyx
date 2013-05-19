#include "onyx.h"

void Init_onyx() {
    mOnyx = rb_define_module("Onyx");
    cMove = rb_define_class_under(mOnyx, "Move", rb_cObject);

    rb_define_singleton_method(cMove, "new", method_move_new, 5);
    rb_define_method(cMove, "from", method_move_from, 0);
    rb_define_method(cMove, "to", method_move_to, 0);
    rb_define_method(cMove, "piece", method_move_piece, 0);
    rb_define_method(cMove, "capture?", method_move_capture, 0);
    rb_define_method(cMove, "flag", method_move_flag, 0);
    rb_define_method(cMove, "promotion?", method_move_promotion, 0);
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

    printf("%d\n", RTEST(capture));

    move = new_move(NUM2INT(from), NUM2INT(to), NUM2INT(piece), RTEST(capture),  NUM2INT(flag));
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