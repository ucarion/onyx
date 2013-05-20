#ifndef ONYX_H
#define ONYX_H

#include "ruby.h"
#include "move.h"
#include "board.h"
#include "utils.h"

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
VALUE method_move_flag(VALUE self);
VALUE method_move_promotion(VALUE self);

VALUE method_board_new(VALUE class);
VALUE method_board_set(VALUE self, VALUE positionVal, VALUE pieceName);

void Init_onyx();

#endif