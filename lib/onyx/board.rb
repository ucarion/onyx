module Onyx
  class Board
    def self.new_from_fen(fen)
      board = Board.new
      args = fen.split

      piecelocs = args.first
      lines = piecelocs.split('/')

      lines.each_with_index do |line, down|
        up = 7 - down
        out = 0
        line.chars do |char|
          if char.is_i?
            out += char.to_i
          else
            board.set(8 * up + out, s_to_piece(char))
            out += 1
          end
        end
      end

      board.white_to_move = args[1].include?('w')

      board.white_castle_k = args[2].include?('K')
      board.white_castle_q = args[2].include?('Q')
      board.black_castle_k = args[2].include?('k')
      board.black_castle_q = args[2].include?('q')

      board.en_passant_loc = (args[3] == '-' ? -1 : args[3].to_position)

      board.fifty_move_rule = args[4].to_i

      board.update_special_bitboards!

      board
    end

    def to_s
      s  = "     1   2   3   4   5   6   7   8  \n"
      s += "   +---+---+---+---+---+---+---+---+\n"

      7.downto(0) do |up|
        s += " #{('a'.ord + up).chr} |"

        0.upto(7) do |out|
          s += " #{piece_to_s(up * 8 + out)} |"
        end

        s += " #{('a'.ord + up).chr} \n"
        s += "   +---+---+---+---+---+---+---+---+\n"
      end
      s += "     1   2   3   4   5   6   7   8  \n";
      s += "\n"
      s += "#{white_to_move? ? "White" : "Black"} to move.\n"
      s += "White can castle:#{" O-O" if white_castle_k?}#{" O-O-O" if white_castle_q?}\n"
      s += "Black can castle:#{" O-O" if black_castle_k?}#{" O-O-O" if black_castle_q?}\n"
      s += "En passant loc: #{en_passant_loc}\n"
      s += "Fifty move rule: #{fifty_move_rule}\n"

      s
    end

    private

    def self.s_to_piece(s)
      case s
      when 'P'
        :white_pawn
      when 'p'
        :black_pawn
      when 'N'
        :white_knight
      when 'n'
        :black_knight
      when 'B'
        :white_bishop
      when 'b'
        :black_bishop
      when 'R'
        :white_rook
      when 'r'
        :black_rook
      when 'Q'
        :white_queen
      when 'q'
        :black_queen
      when 'K'
        :white_king
      when 'k'
        :black_king
      else
        raise "Unknown piece string #{s}"
      end
    end

    def piece_to_s(location)
      case self[location]
      when :white_pawn
        'P'
      when :black_pawn
        'p'
      when :white_knight
        'N'
      when :black_knight
        'n'
      when :white_bishop
        'B'
      when :black_bishop
        'b'
      when :white_rook
        'R'
      when :black_rook
        'r'
      when :white_queen
        'Q'
      when :black_queen
        'q'
      when :white_king
        'K'
      when :black_king
        'k'
      else
        ' '
      end
    end
  end
end

# from http://stackoverflow.com/questions/1235863/test-if-a-string-is-basically-an-integer-in-quotes-using-ruby
class String
  def is_i?
    !!(self =~ /^[-+]?[0-9]+$/)
  end

  # convert string to index (a1 --> 0, h8 --> 63)
  def to_position
    (8 * (self[0].ord - 'a'.ord) + self[1].to_i)
  end
end