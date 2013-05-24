require_relative 'test_helper'

class MoveTest < Onyx::TestCase
  def setup
    @board_to_s = <<-BOARD
     1   2   3   4   5   6   7   8  
   +---+---+---+---+---+---+---+---+
 h | r | n | b | q | k | b | n | r | h 
   +---+---+---+---+---+---+---+---+
 g | p | p | p | p | p | p | p | p | g 
   +---+---+---+---+---+---+---+---+
 f |   |   |   |   |   |   |   |   | f 
   +---+---+---+---+---+---+---+---+
 e |   |   |   |   |   |   |   |   | e 
   +---+---+---+---+---+---+---+---+
 d |   |   |   |   |   |   |   |   | d 
   +---+---+---+---+---+---+---+---+
 c |   |   |   |   |   |   |   |   | c 
   +---+---+---+---+---+---+---+---+
 b | P | P | P | P | P | P | P | P | b 
   +---+---+---+---+---+---+---+---+
 a | R | N | B | Q | K | B | N | R | a 
   +---+---+---+---+---+---+---+---+
     1   2   3   4   5   6   7   8  

White to move.
White can castle: O-O O-O-O
Black can castle: O-O O-O-O
En passant loc: -1
Fifty move rule: 0
BOARD
    @board = Onyx::Board.new_from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
  end

  def test_can_create_board
    assert_nothing_raised do
      Onyx::Board.new
    end
  end

  def test_can_read_from_fen
    assert_equal(@board_to_s, @board.to_s)
  end

  def test_can_use_accessor_methods
    assert_nothing_raised do
      @board.white_castle_k?
      @board.white_castle_q?
      @board.black_castle_k?
      @board.black_castle_q?
    end
  end

  def test_move_change_piece_locs
    @board.do_move(Onyx::Move.new(12, 12 + 16, Onyx::Move::WHITE_PAWN, false, Onyx::Move::FLAG_NO_FLAG))

    assert_equal(nil, @board[12])
    assert_equal(:white_pawn, @board[12 + 16])
  end

  def test_move_update_ep
    @board.do_move(Onyx::Move.new(12, 12 + 16, Onyx::Move::WHITE_PAWN, false, Onyx::Move::FLAG_NO_FLAG))

    assert_equal(12 + 8, @board.en_passant_loc)
  end

  def test_move_change_side_to_move
    assert(@board.white_to_move?)

    @board.do_move(Onyx::Move.new(12, 12 + 16, Onyx::Move::WHITE_PAWN, false, Onyx::Move::FLAG_NO_FLAG))

    assert(!@board.white_to_move?)
  end

  def test_move_castle
    board = Onyx::Board.new_from_fen('r1bqkbnr/ppp2ppp/2np4/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4')

    board.do_move(Onyx::Move.new(4, 6, Onyx::Move::WHITE_KING, false, Onyx::Move::FLAG_OO));

    assert_equal(nil, board[4])
    assert_equal(nil, board[7])
    assert_equal(:white_king, board[6])
    assert_equal(:white_rook, board[5])

    assert(!(board.white_castle_k? || board.white_castle_q?))
  end

  def test_move_promotion
    board = Onyx::Board.new_from_fen('8/8/8/8/8/4k3/p7/4K3 b - - 0 1')

    board.do_move(Onyx::Move.new(8, 0, Onyx::Move::BLACK_PAWN, false, Onyx::Move::FLAG_PROMO_QUEEN))

    assert_equal(nil, board[8])
    assert_equal(:black_queen, board[0])
  end

  def test_lose_castling_rights
    board = Onyx::Board.new_from_fen('r1bqkbnr/ppp2ppp/2np4/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4')

    board.do_move(Onyx::Move.new(7, 6, Onyx::Move::WHITE_ROOK, false, Onyx::Move::FLAG_NO_FLAG))

    assert(!board.white_castle_k?)
    assert(board.white_castle_q?)
  end

  def test_capture
    board = Onyx::Board.new_from_fen('rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1')

    board.do_move(Onyx::Move.new(28, 28 + 7, Onyx::Move::WHITE_PAWN, true, Onyx::Move::FLAG_NO_FLAG))

    assert_equal(:white_pawn, board[28 + 7])
    assert_equal(nil, board[28])
  end

  def test_capture_ep
    board = Onyx::Board.new_from_fen('r1bqkbnr/ppp1pppp/2n5/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1')

    board.do_move(Onyx::Move.new(36, 36 + 7, Onyx::Move::WHITE_PAWN, true, Onyx::Move::FLAG_EP))

    assert_equal(:white_pawn, board[36 + 7])
    assert_equal(nil, board[35])
    assert_equal(nil, board[36])
  end
end