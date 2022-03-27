#include "classes.h"

namespace chessClasses {

	int King::kingCounter = 0;
	Color Board::playerTurn = Color::White;

	Board::Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				squares[x][y] = nullptr;
			}
		}
	}

	Board::~Board() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (squares[x][y] != nullptr) {
					delete squares[x][y];
					squares[x][y] = nullptr;
				}
			}
		}
		return;
	}

	King::King(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board) { 
		
		try {
			if (kingCounter + 1 >= 3)
				throw InvalidValueException("The board already contains 2 Kings");
			kingCounter++;
			this->color = color;
			this->x = x;
			this->y = y;
			board[x][y] = this;
		}
		catch (InvalidValueException& e) {
			std::cout << "Attempt to create a King: " << e.what() << std::endl << "This King won't be created\n";
		}
	};

	PieceType King::getPieceType() const
	{
		return pieceType;
	}

	Color King::getColor() const
	{
		return color;
	}

	void King::changePosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	std::vector<std::pair<int, int>> King::getValidMoves(std::array<std::array<Piece*, 8>, 8>& board)
	{
		validMoves.clear();
		// mouvement a droite
		if (x + 1 <= 7) {
			if ((board[x + 1][y] == nullptr) || (board[x + 1][y]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 1, y));
		}
		// mouvement a gauche
		if (x - 1 >= 0) {
			if ((board[x - 1][y] == nullptr) || (board[x - 1][y]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 1, y));
		}
		// mouvement en haut
		if (y + 1 <= 7) {
			if ((board[x][y + 1] == nullptr) || (board[x][y + 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x, y + 1));
		}
		// mouvement en bas
		if (y - 1 >= 0) {
			if ((board[x][y - 1] == nullptr) || (board[x][y - 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x, y - 1));
		}
		//mouvement en diagonal droite-haut
		if ((x + 1 <= 7) && (y + 1 <= 7)) {
			if ((board[x + 1][y + 1] == nullptr) || (board[x + 1][y + 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 1, y + 1));
		}
		//mouvement en diagonal droite-bas
		if ((x + 1 <= 7) && (y - 1 >= 0)) {
			if ((board[x + 1][y - 1] == nullptr) || (board[x + 1][y - 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 1, y - 1));
		}
		//mouvement en diagonal gauche-haut
		if ((x - 1 >= 0) && (y + 1 <= 7)) {
			if ((board[x - 1][y + 1] == nullptr) || (board[x - 1][y + 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 1, y + 1));
		}
		//mouvement en diagonal gauche-bas
		if ((x - 1 >= 0) && (y - 1 >= 0)) {
			if ((board[x - 1][y - 1] == nullptr) || (board[x - 1][y - 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 1, y - 1));
		}
		return validMoves;
	}

	void King::move(int x, int y, std::array<std::array<Piece*, 8>, 8>& board)
	{
		std::vector<std::pair<int, int>> moves = getValidMoves(board);
		for (auto&& p : moves) {
			if (x == p.first && y == p.second) {
				Piece* oldPiece = board[x][y];
				King* original = this;
				board[this->x][this->y] = nullptr;
				//reduit temporairement le nombre de rois
				kingCounter--;
				King tempKing(x, y, getColor(), board);

				if (!tempKing.isChecked(board)) {
					board[x][y] = oldPiece;
					if (board[x][y] != nullptr && board[x][y] != this) {
						delete board[x][y];
						std::cout << "Capture d'une piece adverse\n";
					}
					changePosition(x, y);
					board[x][y] = this;
					kingCounter++;
					return;
				}
				//undo si roi en echec
				std::cout << "Ce mouvement causerait un echec sur votre roi\n";
				board[this->x][this->y] = original;
				board[x][y] = oldPiece;
				kingCounter++;
				return;
			}
		}
		std::cout << "Cette piece ne peut pas effectuer ce mouvement\n";
	}

	bool King::isChecked(std::array<std::array<Piece*, 8>, 8>& board) {
		bool check = false;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j] != nullptr && board[i][j]->getColor() != this->getColor()) {
					for (auto&& possibleMove : board[i][j]->getValidMoves(board)) {
						if (possibleMove.first == this->x && possibleMove.second == this->y) {
							check = true;
						}
					}
				}
			}
		}
		return check;
	}

	Knight::Knight(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board) {
		this->color = color;
		this->x = x;
		this->y = y;
		board[x][y] = this;
	};

	PieceType Knight::getPieceType() const
	{
		return pieceType;
	}

	Color Knight::getColor() const
	{
		return color;
	}

	void Knight::changePosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	std::vector<std::pair<int, int>> Knight::getValidMoves(std::array<std::array<Piece*, 8>, 8>& board)
	{
		validMoves.clear();
		//mouvement L
		if ((x + 1 <= 7) && (y - 2 >= 0)) {
			if ((board[x + 1][y - 2] == nullptr) || (board[x + 1][y - 2]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 1, y - 2));
		}
		//mouvement L inverse
		if ((x - 1 >= 0) && (y - 2 >= 0)) {
			if ((board[x - 1][y - 2] == nullptr) || (board[x - 1][y - 2]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 1, y - 2));
		}
		//mouvement L 90 degres
		if ((x - 2 >= 0) && (y - 1 >= 0)) {
			if ((board[x - 2][y - 1] == nullptr) || (board[x - 2][y - 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 2, y - 1));
		}
		//mouvement L inverse 90 degres
		if ((x - 2 >= 0) && (y + 1 <= 7)) {
			if ((board[x - 2][y + 1] == nullptr) || (board[x - 2][y + 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 2, y + 1));
		}
		//mouvement L 180 degres
		if ((x - 1 >= 0) && (y + 2 <= 7)) {
			if ((board[x - 1][y + 2] == nullptr) || (board[x - 1][y + 2]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x - 1, y + 2));
		}
		//mouvement L inverse 180 degres
		if ((x + 1 <= 7) && (y + 2 <= 7)) {
			if ((board[x + 1][y + 2] == nullptr) || (board[x + 1][y + 2]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 1, y + 2));
		}
		//mouvement L 270 degres
		if ((x + 2 <= 7) && (y + 1 <= 7)) {
			if ((board[x + 2][y + 1] == nullptr) || (board[x + 2][y + 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 2, y + 1));
		}
		//mouvement L inverse 270 degres
		if ((x + 2 <= 7) && (y - 1 >= 0)) {
			if ((board[x + 2][y - 1] == nullptr) || (board[x + 2][y - 1]->getColor() != getColor()))
				validMoves.push_back(std::pair<int, int>(x + 2, y - 1));
		}
		return validMoves;
	}

	void Knight::move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board)
	{
		std::vector<std::pair<int, int>> moves = getValidMoves(board);
		for (auto&& p : moves) {
			if (x == p.first && y == p.second) {
				// retrouver notre roi pour verifier que le deplacement ne le mettrait pas en echec
				King* ourKing = nullptr;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (board[i][j] != nullptr) {
							if (board[i][j]->getPieceType() == PieceType::King && board[i][j]->getColor() == this->getColor()) {
								ourKing = dynamic_cast<King*>(board[i][j]);
							}

						}
					}
				}

				Piece* oldPiece = board[x][y];
				Knight* original = this;
				Knight tempKnight(x, y, getColor(), board);
				board[this->x][this->y] = nullptr;

				if (!ourKing->isChecked(board)) {
					board[x][y] = oldPiece;
					if (board[x][y] != nullptr && board[x][y] != this) {
						delete board[x][y];
						std::cout << "Capture d'une piece adverse\n";
					}
					changePosition(x, y);
					board[x][y] = this;
					//emit pieceMoved(this, original->getX(), original->getY());
					return;
				}
				//undo si roi en echec
				std::cout << "Ce mouvement causerait un echec sur votre roi\n";
				board[this->x][this->y] = original;
				board[x][y] = oldPiece;
				return;
			}
		}
		std::cout << "Cette piece ne peut pas effectuer ce mouvement\n";
	}

	Bishop::Bishop(int x, int y, Color color, std::array<std::array<Piece*, 8>, 8>& board) {
		this->color = color;
		this->x = x;
		this->y = y;
		board[x][y] = this;
	};

	PieceType Bishop::getPieceType() const
	{
		return pieceType;
	}

	Color Bishop::getColor() const
	{
		return color;
	}

	void Bishop::changePosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	std::vector<std::pair<int, int>> Bishop::getValidMoves(std::array<std::array<Piece*, 8>, 8>& board)
	{
		validMoves.clear();
		int square = 1;
		//diagonale droite-haut
		while ((x + square <= 7) && (y + square <= 7)) {
			if ((board[x + square][y + square] == nullptr)) {
				validMoves.push_back(std::pair<int, int>(x + square, y + square));
			}
			else if ((board[x + square][y + square]->getColor() != getColor())) {
				validMoves.push_back(std::pair<int, int>(x + square, y + square));
				break;
			}
			square++;
		}
		//diagonale gauche-haut
		square = 1;
		while ((x - square >= 0) && (y + square <= 7)) {
			if ((board[x - square][y + square] == nullptr)) {
				validMoves.push_back(std::pair<int, int>(x - square, y + square));
			}
			else if ((board[x - square][y + square]->getColor() != getColor())) {
				validMoves.push_back(std::pair<int, int>(x - square, y + square));
				break;
			}
			square++;
		}
		//diagonale droite-bas
		square = 1;
		while ((x + square <= 7) && (y - square >= 0)) {
			if ((board[x + square][y - square] == nullptr)) {
				validMoves.push_back(std::pair<int, int>(x + square, y - square));
			}
			else if ((board[x + square][y - square]->getColor() != getColor())) {
				validMoves.push_back(std::pair<int, int>(x + square, y - square));
				break;
			}
			square++;
		}
		//diagonale gauche-bas
		square = 1;
		while ((x - square >= 0) && (y - square >= 0)) {
			if ((board[x - square][y - square] == nullptr)) {
				validMoves.push_back(std::pair<int, int>(x - square, y - square));
			}
			else if ((board[x - square][y - square]->getColor() != getColor())) {
				validMoves.push_back(std::pair<int, int>(x - square, y - square));
				break;
			}
			square++;
		}
		return validMoves;
	}

	void Bishop::move(const int x, const int y, std::array<std::array<Piece*, 8>, 8>& board)
	{
		std::vector<std::pair<int, int>> moves = getValidMoves(board);
		for (auto&& p : moves) {
			if (x == p.first && y == p.second) {
				// retrouver notre roi pour verifier que le deplacement ne le mettrait pas en echec
				King* ourKing = nullptr;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (board[i][j] != nullptr) {
							if (board[i][j]->getPieceType() == PieceType::King && board[i][j]->getColor() == this->getColor()) {
								ourKing = dynamic_cast<King*>(board[i][j]);
							}

						}
					}
				}

				Piece* oldPiece = board[x][y];
				Bishop* original = this;
				Bishop tempBishop(x, y, getColor(), board);
				board[this->x][this->y] = nullptr;

				if (!ourKing->isChecked(board)) {
					board[x][y] = oldPiece;
					if (board[x][y] != nullptr && board[x][y] != this) {
						delete board[x][y];
						std::cout << "Capture d'une piece adverse\n";
					}
					changePosition(x, y);
					board[x][y] = this;
					//emit pieceMoved(this, original->getX(), original->getY());
					return;
				}
				//undo si roi en echec
				std::cout << "Ce mouvement causerait un echec sur votre roi\n";
				board[this->x][this->y] = original;
				board[x][y] = oldPiece;
				return;
			}
		}
		std::cout << "Cette piece ne peut pas effectuer ce mouvement\n";
	}

}