#include <iostream>
#include <vector>

int** memory(int** array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		array[i] = new int[columns];
	}
	return array;
}

int** first_gen(int** array, int rows, int columns) {
	for (int i = 0 ; i < rows; i++) {
		for (int  j = 0; j < columns; j++) {
			array[i][j] = (int)(rand()) / RAND_MAX;
		}
	}
	return array;
}

int count_lifes(int** array, int row, int column) {
	int cnt = 0;
	for (int tmp1 = -1; tmp1 <= 1; tmp1++) {
		for (int tmp2 = -1; tmp2 <= 1; tmp2++) {
			if (*(array[row + tmp1, column + tmp2]) == 1) {
				cnt++;
			}
		}
	}
	return cnt;
}

int** generation(int** array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (array[i][j] == 0) {
				if (count_lifes(array, i, j) == 3) {
					array[i][j] = 1;
				}
		
		    }
			else{
				if (count_lifes(array, i, j) < 2 || count_lifes(array, i, j) > 3) {
					array[i][j] = 0;
				}
			}
	
		}
	 }
	return array;
}

void demo(int** array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			std::cout << array[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

bool game_over(int** array, int rows, int columns){
	int** cur_universe{ new int* [rows] {}};
	int sum_cells = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			sum_cells += array[i][j];
		}
	}
	if (sum_cells == 0) {
		return false;
	}
	else if (array == generation(array, rows, columns)) {
		return false;
	}
	return true;
}


int main() {
	srand(time(nullptr));
	int rows = 50, columns = 50;
	int** universe{ new int* [rows] {}};
	int** prev_universe{ new int* [rows] {}};
	bool flag = true;
	universe = memory(universe, rows, columns);
	universe = first_gen(universe, rows, columns);
	
	while(flag) {
		prev_universe = universe;

		universe = generation(universe, rows, columns);
		if (game_over(universe, rows, columns)){
			std::cout << "Game over" << std::endl;
			flag = false; 
			break;

		}
		else {
			demo(universe, rows, columns);
		}

	}
	return 0;
}