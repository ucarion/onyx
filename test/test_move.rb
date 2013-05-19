require_relative 'test_helper'

class MoveTest < Onyx::TestCase
  def test_cannot_call_move_new
    assert_raise(NoMethodError) do
      Onyx::Move.new(0, 0, 0, false, 0)
    end
  end
end