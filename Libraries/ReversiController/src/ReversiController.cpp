
#include "ReversiController/ReversiController.hpp"

#include <Reversi/Reversi.hpp>


ReversiController::ReversiController()
	: QObject()
	, m_currentPlayer(Black)
	, m_numBlackStones(0)
	, m_numWhiteStones(0)
{
	for (int idx=0; idx<64; ++idx)
	{
		m_cells.append(new CellData("transparent"));
	}

	newGame();
}

ReversiController::~ReversiController()
{

}

void ReversiController::newGame()
{
	m_game.reset(new rv::Reversi);

	setCurrentPlayer(Black);
	setCurrentValidMoves(QVector<int>());
	setNumBlackStones(2);
	setNumWhiteStones(2);
	setCells();
}

void ReversiController::makeMove(int idx)
{
	const int x = idx % 8;
	const int y = std::floor(idx / 8);

	rv::ETile currentTile = static_cast<rv::ETile>(m_currentPlayer);
	std::vector<Eigen::Vector2i> validMoves;

	if (m_game->makeMove(x, y, currentTile))
	{
		currentTile = rv::Reversi::opponent(currentTile);
		validMoves = m_game->getValidMoves(currentTile);

		if (validMoves.empty())
		{
			currentTile = rv::Reversi::opponent(currentTile);
			validMoves = m_game->getValidMoves(currentTile);

			if (validMoves.empty())
			{
				currentTile = rv::ETile::Unknown;
			}
		}

		EPlayer newPlayer = static_cast<EPlayer>(currentTile);
		setCurrentPlayer(newPlayer);
		QVector<int> currentValidMoves;
		for (const Eigen::Vector2i& move: validMoves)
		{
			currentValidMoves.push_back(move(0)+move(1)*8);
		}
		setCurrentValidMoves(currentValidMoves);

		std::map<rv::ETile, int> score = m_game->getScore();
		setNumBlackStones(score[rv::ETile::Black]);
		setNumWhiteStones(score[rv::ETile::White]);

		setCells();
	}
}

ReversiController::EPlayer ReversiController::getCurrentPlayer() const
{
	return m_currentPlayer;
}

void ReversiController::setCurrentPlayer(EPlayer currentPlayer)
{
	if (currentPlayer != m_currentPlayer) {
		m_currentPlayer = currentPlayer;
		emit currentPlayerChanged();
	}
}

const QVector<int> &ReversiController::getCurrentValidMoves() const
{
	return m_currentValidMoves;
}

void ReversiController::setCurrentValidMoves(const QVector<int> &currentValidMoves)
{
	if (currentValidMoves != m_currentValidMoves) {
		m_currentValidMoves = currentValidMoves;
		emit currentValidMovesChanged();
	}
}

int ReversiController::getNumBlackStones() const
{
	return m_numBlackStones;
}

void ReversiController::setNumBlackStones(int numBlackStones)
{
	if (numBlackStones != m_numBlackStones) {
		m_numBlackStones = numBlackStones;
		emit numBlackStonesChanged();
	}
}

int ReversiController::getNumWhiteStones() const
{
	return m_numWhiteStones;
}

void ReversiController::setNumWhiteStones(int numWhiteStones)
{
	if (numWhiteStones != m_numWhiteStones) {
		m_numWhiteStones = numWhiteStones;
		emit numWhiteStonesChanged();
	}
}

void ReversiController::setCells()
{
	const rv::TMatrix &tiles = m_game->getTiles();

	for (int x=0; x<8; ++x)
	{
		for (int y=0; y<8; ++y)
		{
			const int idx = y*8+x;
			CellData* cell = static_cast<CellData*>(m_cells[idx]);

			if (tiles(x, y) == rv::ETile::White)
				cell->setColor("white");
			else if (tiles(x, y) == rv::ETile::Black)
				cell->setColor("black");
			else
				cell->setColor("transparent");
		}
	}

	emit cellsChanged();
}

const QList<QObject *> &ReversiController::getCells() const
{
	return m_cells;
}
