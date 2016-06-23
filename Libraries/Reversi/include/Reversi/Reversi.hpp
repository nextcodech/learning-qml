
#ifndef OTHELLO_GAME_BOARD_HPP
#define OTHELLO_GAME_BOARD_HPP

#include <Eigen/Dense>

#include <vector>
#include <map>

namespace rev
{
	enum ETile {
		Unknown = 0,
		Black = 1,
		White = 2
	};

	typedef Eigen::Matrix<ETile, 8, 8> TMatrix;

	typedef Eigen::Vector2i TPos;

	class Reversi
	{
	public:

	public:
		Reversi();

		// Returns True if the coordinates are located on the board.
		static bool isOnBoard(int x, int y);

		// Returns True if the position is in one of the four corners.
		static bool isOnCorner(int x, int y);

		// Returns False if the player's move on space r, c is invalid.
		bool isValidMove(int x, int y, ETile tile) const;

		// Returns a list of [x,y] lists of valid moves for the given player on the given board.
		std::vector<Eigen::Vector2i> getValidMoves(ETile tile) const;

		// Place the tile on the board at x, y, and flip any of the opponent's pieces.
		// Returns False if this is an invalid move, True if it is valid.
		bool makeMove(int x, int y, ETile tile);

		// Determine the score by counting the tiles. Returns a dictionary with keys 'X' and 'O'.
		std::map<ETile, int> getScore() const;

		// returns the tiles on the board
		const TMatrix &getTiles() const;
		
		//static ETile opponent(const ETile tile);

	private:
		TMatrix m_tiles;
	};
}

#endif
