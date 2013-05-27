#ifndef ONYX_H
#define ONYX_H

#include "ruby.h"
#include "move.h"
#include "board.h"
#include "utils.h"
#include "movegen.h"

VALUE mOnyx; // the Onyx module
VALUE cMove; // the Onyx::Move class
VALUE cBoard; // the Onyx::Board class

typedef struct {
    int val;
} MoveWrapper;

int unwrap_move(VALUE move);

VALUE method_move_new(VALUE class, VALUE from, VALUE to, VALUE piece, VALUE capture, VALUE flag);
VALUE method_move_from(VALUE self);
VALUE method_move_to(VALUE self);
VALUE method_move_piece(VALUE self);
VALUE method_move_capture(VALUE self);
VALUE method_move_get_capture(VALUE self);
VALUE method_move_flag(VALUE self);
VALUE method_move_promotion(VALUE self);

VALUE method_board_new(VALUE class);
VALUE method_board_kingmoves(VALUE class, VALUE at);
VALUE method_board_knightmoves(VALUE class, VALUE at);
VALUE method_board_set(VALUE self, VALUE positionVal, VALUE pieceName);
VALUE method_board_get(VALUE self, VALUE positionVal);
VALUE method_board_update_special_bitboards(VALUE self);
VALUE method_board_white_to_move(VALUE self);
VALUE method_board_set_white_to_move(VALUE self, VALUE whiteToMove);
VALUE method_board_w_oo(VALUE self);
VALUE method_board_set_w_oo(VALUE self, VALUE w_oo);
VALUE method_board_w_ooo(VALUE self);
VALUE method_board_set_w_ooo(VALUE self, VALUE w_oo);
VALUE method_board_b_oo(VALUE self);
VALUE method_board_set_b_oo(VALUE self, VALUE b_oo);
VALUE method_board_b_ooo(VALUE self);
VALUE method_board_set_b_ooo(VALUE self, VALUE b_oo);
VALUE method_board_ep(VALUE self);
VALUE method_board_set_ep(VALUE self, VALUE ep);
VALUE method_board_fmr(VALUE self);
VALUE method_board_set_fmr(VALUE self, VALUE fmr);
VALUE method_board_do_move(VALUE self, VALUE move);
VALUE method_board_undo(VALUE self, VALUE aMove);
VALUE method_board_attacked(VALUE self, VALUE positionVal);

void Init_onyx();

#endif