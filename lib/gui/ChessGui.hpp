// ChessGui.hpp
#ifndef CHESSGUI_HPP
#define CHESSGUI_HPP

#include <QObject>
#include <QString>
#include <QVector>
#include <QQmlEngine>
#include "../ChessBoard.hpp"

class ChessGUI : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isWhiteTurn READ isWhiteTurn NOTIFY turnChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
    Q_PROPERTY(QVector<QVector<QString>> boardState READ boardState NOTIFY boardUpdated)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)

public:
    explicit ChessGUI(QObject *parent = nullptr);
    ~ChessGUI();

    bool isWhiteTurn() const;
    QString statusMessage() const;
    QVector<QVector<QString>> boardState() const;
    bool gameOver() const { return m_gameOver; }

    Q_INVOKABLE void handleSquareClick(int row, int col);
    Q_INVOKABLE void resetGame();

signals:
    void boardUpdated();
    void turnChanged();
    void statusMessageChanged();
    void gameOverChanged();
    void checkMateOccurred(bool isWhiteWinner);

private slots:
    void onCheckOccurred(bool isWhiteInCheck);
    void onCheckMateOccurred(bool whiteWins);

private:
    ChessBoard board;
    bool m_isWhiteTurn;
    QString m_statusMessage;
    bool m_gameOver;

    bool isPieceSelected;
    int selectedRow;
    int selectedCol;

    void updateBoardState();
    QString getPieceSymbol(Piece* piece) const;
    void connectSignals();
};

#endif // CHESSGUI_HPP
