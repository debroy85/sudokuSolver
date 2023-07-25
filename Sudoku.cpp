#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

class Sudoku {

	int matrix[9][9];
public:
	Sudoku() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> matrix[i][j];
			}
		}
	}

	int get(int i, int j) {
		return matrix[i][j];
	}

	void set(int id, int i, int j) {
		matrix[i][j] = id;
	}

	bool isInRow(int value, int row) {
		for (int i = 0; i < 9; ++i) {
			if (matrix[row][i] == value) return true;
		}
		return false;
	}

	bool isInCol(int value, int col) {
		for (int i = 0; i < 9; ++i) {
			if (matrix[i][col] == value) return true;
		}
		return false;
	}

	bool isInCell(int value, int x, int y) {
		int leftx = x / 3;
		int topy = y / 3;
		for (int i = leftx * 3; i < leftx * 3 + 3; ++i) {
			for (int j = topy * 3; j < topy * 3 + 3; ++j) {
				if (matrix[i][j] == value) return true;
			}
		}
		return false;
	}

	bool isEmpty(int x, int y) {
		return (matrix[x][y] == 0);
	}

	bool isSafe(int x, int y, int value) {
		if (matrix[x][y] != 0) return false;
		return (!isInCol(value, y) and !isInRow(value, x) and !isInCell(value, x, y));
	}

	bool isDone() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (matrix[i][j] == 0) return false;
			}
		}
		return true;
	}

	void print() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout <<  matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
};



bool Solver(Sudoku &S, int i = 0) {
	if (i > 80) return true;
	int x = i / 9, y = i % 9;
	if (!S.isEmpty(x, y)) return Solver(S, i + 1);
	
	for (int k = 1; k < 10; k++) {
		if (S.isSafe(x, y, k)) {
			S.set(k, x, y);
			if (Solver(S, i + 1)) return true;
			S.set(0, x, y);
		}
	}
	return false;
}

int main() {
	Sudoku S;
	Solver(S);
	if (!S.isDone()) {
		cout << "Not Possible" << endl;
	}
	else S.print();
	return 0;
}
