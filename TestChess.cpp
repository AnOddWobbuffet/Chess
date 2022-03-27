#include "classes.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

using namespace chessClasses;

Board board;

TEST(King, movementKing) {
	King* king = new King(1, 1, Color::White, board.squares);
	//piece pour verifier la capture de piece adverse
	Bishop* bishop1 = new Bishop(0, 0, Color::Black, board.squares);
	Bishop* bishop2 = new Bishop(1, 2, Color::White, board.squares);
	EXPECT_EQ(king->getColor(), Color::White);
	EXPECT_EQ(king->getX(), 1);
	EXPECT_EQ(king->getY(), 1);
	EXPECT_EQ(king->getPieceType(), PieceType::King);
	EXPECT_EQ(king->getPieceLetter(), "K");
	EXPECT_EQ(king->kingCounter, 1);
	EXPECT_EQ(king->isChecked(board.squares), true);
	
	king->move(2, 2, board.squares);
	
	king->move(0, 0, board.squares);
	king->move(1, 1, board.squares);
	
	king->move(2, 0, board.squares);
	king->move(1, 1, board.squares);

	king->move(1, 2, board.squares);
	king->move(1, 0, board.squares);
	king->move(1, 1, board.squares);
	
	king->move(2, 1, board.squares);
	king->move(1, 1, board.squares);

	king->move(5, 5, board.squares);
	EXPECT_EQ(king->isChecked(board.squares), false);

	King* king2 = new King(7, 2, Color::Black, board.squares);
	King* king3 = new King(5, 5, Color::Black, board.squares);

	board.squares[1][1] = nullptr;
	board.squares[1][2] = nullptr;
	board.squares[7][2] = nullptr;

	delete king;
	delete bishop2;
	delete king2;
	delete king3;
}

TEST(Knight, movementKnight) {
	Knight* knight = new Knight(4, 4, Color::White, board.squares);
	//piece pour verifier la capture de piece adverse
	King* king1 = new King(3, 2, Color::Black, board.squares);
	King* king2 = new King(5, 2, Color::White, board.squares);
	EXPECT_EQ(knight->getColor(), Color::White);
	EXPECT_EQ(knight->getX(), 4);
	EXPECT_EQ(knight->getY(), 4);
	EXPECT_EQ(knight->getPieceType(), PieceType::Knight);
	EXPECT_EQ(knight->getPieceLetter(), "N");
	knight->move(3, 2, board.squares);
	knight->move(4, 4, board.squares);

	knight->move(5, 2, board.squares);
	knight->move(3, 6, board.squares);
	knight->move(4, 4, board.squares);

	knight->move(6, 5, board.squares);
	knight->move(4, 4, board.squares);

	knight->move(6, 3, board.squares);
	knight->move(4, 4, board.squares);

	knight->move(5, 5, board.squares);

	Bishop* bishop = new Bishop(4, 1, Color::Black, board.squares);
	knight->move(3, 2, board.squares);

	board.squares[4][4] = nullptr;
	board.squares[5][2] = nullptr;
	board.squares[4][1] = nullptr;
	delete knight;
	delete king2;
	delete bishop;
}

TEST(Bishop, movementBishop) {
	Bishop* bishop = new Bishop(4, 4, Color::White, board.squares);
	//piece pour verifier la capture de piece adverse
	King* king1 = new King(7, 7, Color::Black, board.squares);
	King* king2 = new King(5, 2, Color::White, board.squares);
	Knight* knight = new Knight(6, 1, Color::Black, board.squares);
	EXPECT_EQ(bishop->getColor(), Color::White);
	EXPECT_EQ(bishop->getX(), 4);
	EXPECT_EQ(bishop->getY(), 4);
	EXPECT_EQ(bishop->getPieceType(), PieceType::Bishop);
	EXPECT_EQ(bishop->getPieceLetter(), "B");

	bishop->move(7, 7, board.squares);
	bishop->move(4, 4, board.squares);

	bishop->move(0, 7, board.squares);
	bishop->move(4, 4, board.squares);

	bishop->move(4, 0, board.squares);

	Bishop* bishop2 = new Bishop(4, 1, Color::Black, board.squares);

	bishop->move(7, 7, board.squares);

	board.squares[4][4] = nullptr;
	board.squares[5][2] = nullptr;
	board.squares[6][1] = nullptr;
	board.squares[4][1] = nullptr;
	delete bishop;
	delete king2;
	delete knight;
	delete bishop2;
}





#endif