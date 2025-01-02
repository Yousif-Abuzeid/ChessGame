// gui.cpp
#include "/home/youssef-abuzeid/Projects/ChessGame/ChessGame/lib/gui/ChessGui.hpp"

ChessGUI::ChessGUI(QObject *parent)
    : QObject(parent)
    , m_isWhiteTurn(true)
    , isPieceSelected(false)
    , m_gameOver(false)
{
    m_statusMessage = "White's turn";
    connectSignals();
    updateBoardState();
}

void ChessGUI::connectSignals() {
    connect(&board, &ChessBoard::checkOccurred, this, &ChessGUI::onCheckOccurred);
    connect(&board, &ChessBoard::checkMateOccurred, this, &ChessGUI::onCheckMateOccurred);
    connect(&board, &ChessBoard::boardUpdated, this, &ChessGUI::updateBoardState);
}

ChessGUI::~ChessGUI() {}

bool ChessGUI::isWhiteTurn() const {
    return m_isWhiteTurn;
}

QString ChessGUI::statusMessage() const {
    return m_statusMessage;
}

QVector<QVector<QString>> ChessGUI::boardState() const {
    QVector<QVector<QString>> state(8, QVector<QString>(8));
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            state[row][col] = getPieceSymbol(board.board[row][col]);
        }
    }
    return state;
}

QString ChessGUI::getPieceSymbol(Piece* piece) const {
    if (!piece) return "";

    QString symbol;
    switch (piece->GetType()) {
    case PieceType::PAWN:
        symbol = piece->isWhitePiece() ? "♙" : "♟";
        break;
    case PieceType::ROOK:
        symbol = piece->isWhitePiece() ? "♖" : "♜";
        break;
    case PieceType::KNIGHT:
        symbol = piece->isWhitePiece() ? "♘" : "♞";
        break;
    case PieceType::BISHOP:
        symbol = piece->isWhitePiece() ? "♗" : "♝";
        break;
    case PieceType::QUEEN:
        symbol = piece->isWhitePiece() ? "♕" : "♛";
        break;
    case PieceType::KING:
        symbol = piece->isWhitePiece() ? "♔" : "♚";
        break;
    default: return "";
    }

    return symbol;
}

void ChessGUI::handleSquareClick(int row, int col) {
    if (m_gameOver) return;  // Prevent moves after game is over

    if (!isPieceSelected) {
        // First click - select a piece
        if (board.board[row][col] &&
            board.board[row][col]->isWhitePiece() == m_isWhiteTurn) {
            isPieceSelected = true;
            selectedRow = row;
            selectedCol = col;
            m_statusMessage = QString("Selected piece at %1, %2").arg(row + 1).arg(char('A' + col));
            emit statusMessageChanged();
        }
    } else {
        // Second click - move the piece
        if (board.move(selectedRow, selectedCol, row, col, m_isWhiteTurn)) {
            m_isWhiteTurn = !m_isWhiteTurn;
            if (!m_gameOver) {  // Only update turn message if game isn't over
                m_statusMessage = m_isWhiteTurn ? "White's turn" : "Black's turn";
            }
            emit turnChanged();
        }
        isPieceSelected = false;
    }

    updateBoardState();
}


// In gui.cpp, update the resetGame function:
void ChessGUI::resetGame() {
    // Clear all pieces from the current board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.board[i][j]) {
                delete board.board[i][j];
                board.board[i][j] = nullptr;
            }
        }
    }

    // Reinitialize the pieces
    // White pieces
    for (int i = 0; i < 8; i++) {
        board.board[1][i] = new Pawn(1, i, true);
        board.board[6][i] = new Pawn(6, i, false);
    }

    // White pieces back row
    board.board[0][0] = new Rook(0, 0, true);
    board.board[0][7] = new Rook(0, 7, true);
    board.board[0][1] = new Knight(0, 1, true);
    board.board[0][6] = new Knight(0, 6, true);
    board.board[0][2] = new Bishop(0, 2, true);
    board.board[0][5] = new Bishop(0, 5, true);
    board.board[0][3] = new Queen(0, 3, true);
    board.board[0][4] = new King(0, 4, true);

    // Black pieces back row
    board.board[7][0] = new Rook(7, 0, false);
    board.board[7][7] = new Rook(7, 7, false);
    board.board[7][1] = new Knight(7, 1, false);
    board.board[7][6] = new Knight(7, 6, false);
    board.board[7][2] = new Bishop(7, 2, false);
    board.board[7][5] = new Bishop(7, 5, false);
    board.board[7][3] = new Queen(7, 3, false);
    board.board[7][4] = new King(7, 4, false);

    // Reset game state
    m_isWhiteTurn = true;
    m_gameOver = false;
    isPieceSelected = false;
    m_statusMessage = "White's turn";

    // Update UI
    updateBoardState();
    emit gameOverChanged();
    emit turnChanged();
    emit statusMessageChanged();
}

void ChessGUI::onCheckOccurred(bool isWhiteInCheck) {
    QString color = isWhiteInCheck ? "White" : "Black";
    m_statusMessage = QString("%1 is in check! %2's turn")
                          .arg(color)
                          .arg(m_isWhiteTurn ? "White" : "Black");
    emit statusMessageChanged();
}

void ChessGUI::onCheckMateOccurred(bool whiteWins) {
    m_gameOver = true;
    m_statusMessage = QString("Checkmate! %1 wins!")
                          .arg(whiteWins ? "White" : "Black");
    emit statusMessageChanged();
    emit gameOverChanged();
    emit checkMateOccurred(whiteWins);
}

void ChessGUI::updateBoardState() {
    emit boardUpdated();
    emit statusMessageChanged();
}
