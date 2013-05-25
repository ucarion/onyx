require_relative 'test_helper'

class MoveTest < Onyx::TestCase
  def test_move_accessors
    move = Onyx::Move.new(12, 12 + 16, Onyx::Move::WHITE_PAWN, false, Onyx::Move::FLAG_NO_FLAG)

    assert_equal(12, move.from)
    assert_equal(12 + 16, move.to)
    assert_equal(Onyx::Move::WHITE_PAWN, move.piece)
    assert_equal(Onyx::Move::NO_PIECE, move.captured)
    assert(!move.capture?)
    assert_equal(Onyx::Move::NO_PIECE, move.captured)
    assert_equal(Onyx::Move::FLAG_NO_FLAG, move.flag)
    assert(!move.promotion?)
  end

  def test_promotion
    move = Onyx::Move.new(8, 0, Onyx::Move::BLACK_PAWN, false, Onyx::Move::FLAG_PROMO_QUEEN)

    assert(move.promotion?)

    move = Onyx::Move.new(4, 6, Onyx::Move::WHITE_KING, false, Onyx::Move::FLAG_OO)

    assert(!move.promotion?)
  end

  def test_move_capture
    move = Onyx::Move.new(36, 36 + 7, Onyx::Move::WHITE_PAWN, Onyx::Move::BLACK_PAWN, Onyx::Move::FLAG_EP)

    assert(move.capture?)
    assert_equal(Onyx::Move::BLACK_PAWN, move.captured)
  end
end