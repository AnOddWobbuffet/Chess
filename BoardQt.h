#pragma once

#include "classes.h"
#pragma warning(push, 0)
#include <QMainWindow>
#include "ui_BoardQt.h"
#include <QLabel>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QList>
#pragma pop()

namespace BoardGUI {

    class BoardQt : public QMainWindow
    {
        Q_OBJECT

    public:
        BoardQt(QWidget* parent = nullptr);
        ~BoardQt() override = default;
        std::pair<int, int> getCoordinates(QPushButton* pushButton);

    public slots:
        void checkClick();
        void start1();
        void start2();
        void start3();
        void setPosition(chessClasses::Piece* piece);
        void moveNewPosition(chessClasses::Piece*& piece, int oldX, int oldY);

    private:
        Ui::BoardQtClass ui;
        QPushButton* QtBoard[8][8];
        bool isClicked = false;
        std::pair<int, int> coordinates;

        chessClasses::Board board_;
        chessClasses::Piece* piece_ = nullptr;
        QPushButton* lastPushed = nullptr;
    };

}