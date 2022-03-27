#pragma once
#pragma warning(push, 0)
#include <QObject>
#pragma pop()
#include <iostream>
#include <vector>
#include <array>

enum class Color { Default, White, Black };
enum class PieceType { Default, King, Knight, Bishop };

namespace chessClasses {

	class InvalidValueException : public std::logic_error {
	public:
		using logic_error::logic_error;
	};

	class Piece {
	public:
		Piece() = default;
		virtual ~Piece() = default;
		virtual PieceType getPieceType() const = 0;
		virtual Color getColor() const = 0;
		virtual int getX() const = 0;
		virtual int getY() const = 0;
		virtual std::string getPieceLetter() const = 0;
		virtual std::vector<std::pair<int, int>> getValidMoves(std::array<std::array<Piece*, 8>, 8>& board) = 0;
		std::vector<std::pair<int, int>> validMoves;
		virtual void changePosition(int x, int y) = 0;
		virtual void move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board) = 0;

	private:
		static const Color color = Color::Default;
		static const PieceType pieceType = PieceType::Default;
		int x = -1;
		int y = -1;
		std::string pieceLetter;
	};

	class Board {
	public:
		Board();
		~Board();
		std::array<std::array<Piece*, 8>, 8> squares;
		static Color playerTurn;
	};

	class King : public Piece {
	public:
		King(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board);
		~King() { kingCounter--; }
		PieceType getPieceType() const override;
		Color getColor() const override;
		int getX() const override { return x; };
		int getY() const override { return y; };
		std::string getPieceLetter() const override { return pieceLetter; };
		std::vector<std::pair<int, int>> getValidMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
		void changePosition(int x, int y) override;
		void move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board) override;

		bool isChecked(std::array<std::array<Piece*, 8>, 8>& board);
		static int kingCounter;
		
	private:
		Color color;
		PieceType pieceType = PieceType::King;
		int x, y;
		std::string pieceLetter = "K";
	};

	class Knight : public Piece {
	public:
		Knight(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board);
		PieceType getPieceType() const override;
		Color getColor() const override;
		int getX() const override { return x; };
		int getY() const override { return y; };
		virtual std::string getPieceLetter() const override { return pieceLetter; };
		std::vector<std::pair<int, int>> getValidMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
		void changePosition(int x, int y) override;
		void move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board) override;

	private:
		Color color;
		PieceType pieceType = PieceType::Knight;
		int x, y;
		std::string pieceLetter = "N";
	};

	class Bishop : public Piece {
	public:
		Bishop(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board);
		PieceType getPieceType() const override;
		Color getColor() const override;
		int getX() const override { return x; };
		int getY() const override { return y; };
		virtual std::string getPieceLetter() const override { return pieceLetter; };
		std::vector<std::pair<int, int>> getValidMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
		void changePosition(int x, int y) override;
		void move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board) override;

	private:
		Color color;
		PieceType pieceType = PieceType::Bishop;
		int x, y;
		std::string pieceLetter = "B";
	};

}