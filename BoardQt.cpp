#include "BoardQt.h"
#pragma warning(push, 0)
#include <QString>
#include <QPushButton>
#pragma pop()

namespace BoardGUI {

    BoardQt::BoardQt(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);
        std::array<std::array<QPushButton*, 8>, 8> temp = { {
        { ui.b00, ui.b01, ui.b02, ui.b03, ui.b04, ui.b05, ui.b06, ui.b07 },
        { ui.b10, ui.b11, ui.b12, ui.b13, ui.b14, ui.b15, ui.b16, ui.b17 },
        { ui.b20, ui.b21, ui.b22, ui.b23, ui.b24, ui.b25, ui.b26, ui.b27 },
        { ui.b30, ui.b31, ui.b32, ui.b33, ui.b34, ui.b35, ui.b36, ui.b37 },
        { ui.b40, ui.b41, ui.b42, ui.b43, ui.b44, ui.b45, ui.b46, ui.b47 },
        { ui.b50, ui.b51, ui.b52, ui.b53, ui.b54, ui.b55, ui.b56, ui.b57 },
        { ui.b60, ui.b61, ui.b62, ui.b63, ui.b64, ui.b65, ui.b66, ui.b67 },
        { ui.b70, ui.b71, ui.b72, ui.b73, ui.b74, ui.b75, ui.b76, ui.b77 }
        } };

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                QtBoard[x][y] = temp[x][y];
                QObject::connect(QtBoard[x][y], SIGNAL(clicked()), this, SLOT(checkClick()));
            }
        }
        
        connect(ui.startOriginal, SIGNAL(clicked()), this, SLOT(start1()));
        connect(ui.startPosition2, SIGNAL(clicked()), this, SLOT(start2()));
        connect(ui.startPosition3, SIGNAL(clicked()), this, SLOT(start3()));
    }



    void BoardQt::setPosition(chessClasses::Piece* piece) {
        if (piece->getColor() == Color::White)
            QtBoard[piece->getX()][piece->getY()]->setText("W" + QString::fromStdString(piece->getPieceLetter()));
        else
            QtBoard[piece->getX()][piece->getY()]->setText("B" + QString::fromStdString(piece->getPieceLetter()));
    }
    
    void BoardQt::moveNewPosition(chessClasses::Piece*& piece, int oldX, int oldY) {
        QtBoard[oldX][oldY]->text().clear();
        setPosition(piece);
    }

    std::pair<int, int> BoardQt::getCoordinates(QPushButton* pushButton) {
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (QtBoard[x][y] == pushButton) {
                    return std::pair<int, int>(x, y);
                }
            }
        }
        // ne devrait jamais retourner cette ligne, mais sert a eliminer le warning
        return std::pair<int, int>(0, 0);
    }

    void BoardQt::checkClick() {
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        isClicked = !isClicked;
        int x = getCoordinates(clickedButton).first;
        int y = getCoordinates(clickedButton).second;
        if (isClicked) {
            // si on clique une piece, sauvegarde la piece cliquee, demande a l'utilisateur ou la deplacer
            if (!clickedButton->text().isEmpty()) {
                //sauvegarde le bouton appuye
                lastPushed = clickedButton;
                //clickedButton->setText("Move to?");
                ui.MoveValidation->setText("Move to?");
                //sauvegarde la piece en cas de deplacement
                piece_ = board_.squares[x][y];
            }
            // si on clique une case vide
            else {
                isClicked = false;
                return;
            }
        }
        else {
            // si le second clique ce est la meme case, retour a l'affichage original
            if (clickedButton == lastPushed) {
                ui.MoveValidation->setText("");
                lastPushed = nullptr;
            }
            // si la case n'est pas vide
            else {
                int oldX = piece_->getX();
                int oldY = piece_->getY();
                // verifie si c'est le tour du joueur blanc
                if (piece_->getColor() == Color::White) {
                    if (chessClasses::Board::playerTurn == Color::White) {
                        piece_->move(x, y, board_.squares);
                        // verifie si le mouvement a ete effectue
                        if (piece_->getX() != oldX || piece_->getY() != oldY) {
                            moveNewPosition(piece_, oldX, oldY);
                            lastPushed->setText("");
                            chessClasses::Board::playerTurn = Color::Black;
                            ui.MoveValidation->setText("Black's Turn");
                        }
                        else 
                            ui.MoveValidation->setText("INVALID MOVE");
                    }
                    // sinon, le mouvement n'est pas effectue
                    else 
                        ui.MoveValidation->setText("You can't move during Black's turn!");
                }
                // verifie si c'est le tour du joueur noir
                else {
                    if (chessClasses::Board::playerTurn == Color::Black) {
                        piece_->move(x, y, board_.squares);
                        // verifie si le mouvement a ete effectue
                        if (piece_->getX() != oldX || piece_->getY() != oldY) {
                            moveNewPosition(piece_, oldX, oldY);
                            lastPushed->setText("");
                            chessClasses::Board::playerTurn = Color::White;
                            ui.MoveValidation->setText("White's Turn");
                        }
                        else
                            ui.MoveValidation->setText("INVALID MOVE");
                    }
                    // sinon, le mouvement n'est pas effectue
                    else
                        ui.MoveValidation->setText("You can't move during White's turn!");
                }

                lastPushed = nullptr;
                piece_ = nullptr;
            }
        }
    }

    void BoardQt::start1() {

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                QtBoard[x][y]->setText("");
                if (board_.squares[x][y] != nullptr) {
                    delete board_.squares[x][y];
                    board_.squares[x][y] = nullptr;
                }
            }
        }

        chessClasses::King* whiteKing = new chessClasses::King(7, 4, Color::White, board_.squares);
        chessClasses::King* blackKing = new chessClasses::King(0, 4, Color::Black, board_.squares);
        chessClasses::Knight* whiteKnight1 = new chessClasses::Knight(7, 1, Color::White, board_.squares);
        chessClasses::Knight* whiteKnight2 = new chessClasses::Knight(7, 6, Color::White, board_.squares);
        chessClasses::Knight* blackKnight1 = new chessClasses::Knight(0, 1, Color::Black, board_.squares);
        chessClasses::Knight* blackKnight2 = new chessClasses::Knight(0, 6, Color::Black, board_.squares);
        chessClasses::Bishop* whiteBishop1 = new chessClasses::Bishop(7, 2, Color::White, board_.squares);
        chessClasses::Bishop* whiteBishop2 = new chessClasses::Bishop(7, 5, Color::White, board_.squares);
        chessClasses::Bishop* blackBishop1 = new chessClasses::Bishop(0, 2, Color::Black, board_.squares);
        chessClasses::Bishop* blackBishop2 = new chessClasses::Bishop(0, 5, Color::Black, board_.squares);

        setPosition(whiteKing);
        setPosition(blackKing);
        setPosition(whiteKnight1);
        setPosition(whiteKnight2);
        setPosition(blackKnight1);
        setPosition(blackKnight2);
        setPosition(whiteBishop1);
        setPosition(whiteBishop2);
        setPosition(blackBishop1);
        setPosition(blackBishop2);

        chessClasses::Board::playerTurn = Color::White;
        ui.MoveValidation->setText("White's Turn");
    }

    void BoardQt::start2() {

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                QtBoard[x][y]->setText("");
                if (board_.squares[x][y] != nullptr) {
                    delete board_.squares[x][y];
                    board_.squares[x][y] = nullptr;
                }
            }
        }

        chessClasses::King* whiteKing = new chessClasses::King(7, 0, Color::White, board_.squares);
        chessClasses::King* blackKing = new chessClasses::King(0, 0, Color::Black, board_.squares);
        chessClasses::Knight* whiteKnight1 = new chessClasses::Knight(7, 1, Color::White, board_.squares);
        chessClasses::Knight* whiteKnight2 = new chessClasses::Knight(6, 0, Color::White, board_.squares);
        chessClasses::Knight* blackKnight1 = new chessClasses::Knight(0, 1, Color::Black, board_.squares);
        chessClasses::Knight* blackKnight2 = new chessClasses::Knight(1, 0, Color::Black, board_.squares);
        chessClasses::Bishop* whiteBishop1 = new chessClasses::Bishop(6, 3, Color::White, board_.squares);
        chessClasses::Bishop* whiteBishop2 = new chessClasses::Bishop(4, 1, Color::White, board_.squares);
        chessClasses::Bishop* blackBishop1 = new chessClasses::Bishop(3, 1, Color::Black, board_.squares);
        chessClasses::Bishop* blackBishop2 = new chessClasses::Bishop(1, 3, Color::Black, board_.squares);

        setPosition(whiteKing);
        setPosition(blackKing);
        setPosition(whiteKnight1);
        setPosition(whiteKnight2);
        setPosition(blackKnight1);
        setPosition(blackKnight2);
        setPosition(whiteBishop1);
        setPosition(whiteBishop2);
        setPosition(blackBishop1);
        setPosition(blackBishop2);

        chessClasses::Board::playerTurn = Color::White;
        ui.MoveValidation->setText("White's Turn");
    }

    void BoardQt::start3() {

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                QtBoard[x][y]->setText("");
                if (board_.squares[x][y] != nullptr) {
                    delete board_.squares[x][y];
                    board_.squares[x][y] = nullptr;
                }
            }
        }

        chessClasses::King* whiteKing = new chessClasses::King(3, 0, Color::White, board_.squares);
        chessClasses::King* blackKing = new chessClasses::King(4, 7, Color::Black, board_.squares);
        chessClasses::Knight* whiteKnight1 = new chessClasses::Knight(1, 1, Color::White, board_.squares);
        chessClasses::Knight* whiteKnight2 = new chessClasses::Knight(6, 1, Color::White, board_.squares);
        chessClasses::Knight* blackKnight1 = new chessClasses::Knight(6, 6, Color::Black, board_.squares);
        chessClasses::Knight* blackKnight2 = new chessClasses::Knight(1, 6, Color::Black, board_.squares);
        chessClasses::Bishop* whiteBishop1 = new chessClasses::Bishop(0, 0, Color::White, board_.squares);
        chessClasses::Bishop* whiteBishop2 = new chessClasses::Bishop(7, 0, Color::White, board_.squares);
        chessClasses::Bishop* blackBishop1 = new chessClasses::Bishop(0, 7, Color::Black, board_.squares);
        chessClasses::Bishop* blackBishop2 = new chessClasses::Bishop(7, 7, Color::Black, board_.squares);

        setPosition(whiteKing);
        setPosition(blackKing);
        setPosition(whiteKnight1);
        setPosition(whiteKnight2);
        setPosition(blackKnight1);
        setPosition(blackKnight2);
        setPosition(whiteBishop1);
        setPosition(whiteBishop2);
        setPosition(blackBishop1);
        setPosition(blackBishop2);

        chessClasses::Board::playerTurn = Color::White;
        ui.MoveValidation->setText("White's Turn");
    }

}