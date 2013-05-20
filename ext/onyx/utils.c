#include "utils.h"

Bitboard square_at(int position) {
    return 1ULL << position;
}

Bitboard to_bitboard(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}