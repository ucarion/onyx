#include "move.h"

Move new_move(char from, char to, char piece, char capture, char flag) 
{
    return (from) | (to << 6) | (piece << 12) | (capture << 16) | (flag << 20);
}

char get_from(Move move)
{
    return move & 0x3f;
}

char get_to(Move move)
{
    return (move >> 6) & 0x3f;
}

char get_piece(Move move)
{
    return (move >> 12) & 0xf;
}

char get_capture(Move move)
{
    return (move >> 16) & 0xf;
}

char get_flag(Move move)
{
    return (move >> 20) & 0x7;
}

bool is_promotion(Move move)
{
    return get_flag(move) >= MOVE_FLAG_PROMO_KNIGHT;
}