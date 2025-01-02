#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "/home/youssef-abuzeid/Projects/ChessGame/ChessGame/lib/ChessBoard.hpp"
#include "/home/youssef-abuzeid/Projects/ChessGame/ChessGame/lib/gui/ChessGui.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register the ChessBoard type for QML, if needed
    qmlRegisterType<ChessGUI>("Chess", 1, 0, "ChessGUI");  // Ensure correct registration of the ChessGUI class

    // Create ChessBoard object (handles the game logic)
    ChessBoard chessBoard;

    // Create ChessGui object (communicates with ChessBoard)
    ChessGUI chessGui(&chessBoard);  // Passing ChessBoard to ChessGui

    // Expose ChessGui to QML (as chessGame)
    engine.rootContext()->setContextProperty("chessGame", &chessGui);  // "chessGame" will be used in QML

    // Load QML file
    engine.load(QUrl::fromLocalFile("/home/youssef-abuzeid/qtWorkspace/untitled/Main.qml"));

    // Check if QML is loaded properly
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
