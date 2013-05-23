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
end