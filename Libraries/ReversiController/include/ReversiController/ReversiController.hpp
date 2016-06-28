
#ifndef REVERSICONTROLLER_REVERSICONTROLLER_HPP
#define REVERSICONTROLLER_REVERSICONTROLLER_HPP

#include <QObject>
#include <QVector>
#include <QList>

#include <QScopedPointer>

#include "CellData.hpp"

namespace rv {
	class Reversi;
}

// http://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html

class ReversiController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(EPlayer currentPlayer READ getCurrentPlayer NOTIFY currentPlayerChanged)
	Q_PROPERTY(QVector<int> currentValidMoves READ getCurrentValidMoves NOTIFY currentValidMovesChanged)
	Q_PROPERTY(int numBlackStones READ getNumBlackStones NOTIFY numBlackStonesChanged)
	Q_PROPERTY(int numWhiteStones READ getNumWhiteStones NOTIFY numWhiteStonesChanged)

	Q_PROPERTY(QList<QObject *> cells READ getCells NOTIFY cellsChanged)

	Q_ENUMS(EPlayer)

public:
	enum EPlayer
	{
		Unknown = -1,
		Black = 0,
		White = 1
	};

public:
	ReversiController();
	~ReversiController();

	EPlayer getCurrentPlayer() const;

	const QVector<int> &getCurrentValidMoves() const;
	int getNumBlackStones() const;
	int getNumWhiteStones() const;

	const QList<QObject *> &getCells() const;

public slots:
	void newGame();
	void makeMove(int idx);

private:
	void setCurrentPlayer(EPlayer currentPlayer);
	void setCurrentValidMoves(const QVector<int> &currentValidMoves);
	void setNumBlackStones(int numBlackStones);
	void setNumWhiteStones(int numWhiteStones);
	void setCells();

signals:
	void currentPlayerChanged();
	void currentValidMovesChanged();
	void numBlackStonesChanged();
	void numWhiteStonesChanged();
	void cellsChanged();

private:
	EPlayer m_currentPlayer;

	QVector<int> m_currentValidMoves;

	int m_numBlackStones;
	int m_numWhiteStones;

	QList<QObject*> m_cells;

	QScopedPointer<rv::Reversi> m_game;
};

#endif
