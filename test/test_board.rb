require_relative 'test_helper'

class MoveTest < Onyx::TestCase
  def test_can_create_board
    assert_nothing_raised do
      Onyx::Board.new
    end
  end
end