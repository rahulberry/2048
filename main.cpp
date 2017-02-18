#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(){
	void printgrid(vector<int> grid);
	void AddLeft(vector<int>& grid);
	void MoveLeft(vector<int>& grid);
	void MoveRight(vector<int>& grid);
	void AddRight(vector<int>& grid);
	void RotateGrid(vector <int>& grid);
	void GenTwo(vector<int> &grid);
	void MoveDir(vector<int>& grid, char direction);
	bool GameOver(vector<int>& grid);

	ifstream infile;

	cout << "enter initial configuration file name:" << endl;
	string infilename;
	cin >> infilename;
	infile.open(infilename.c_str());
	vector<int> grid;
	vector<int> grid2;

	if(!infile.is_open()){
		cout << "file not found, default start configuration:" << endl;
		for(int i = 0; i <= 14; i++){
				grid.push_back(0);
			}
			grid.push_back(2);
		}
	else{
		int value;
		while(infile >> value){
				grid.push_back(value);
		    }
	}
	bool move;
	printgrid(grid);
	srand(time(NULL));
	char direction;
    move = true;
    move = GameOver(grid);
	while(move){
		grid2 = grid;
		cin >> direction;
		MoveDir(grid, direction);
		if(grid2 != grid){
			GenTwo(grid);
		    printgrid(grid);
		}
	    move = GameOver(grid);
	}
	cout << "\n\n game over" << endl;
	return 0;
}

void space(int n){
	for(int i = 0; i < n; i++){
	cout << "  ";
	}
}

void printgrid(vector<int> grid){
	for (int i =0; i < 4; i ++){
			for (int j =0; j  < 4; j++){
					cout << grid[j+(4*i)];
					cout << "\t";
			}
			cout << endl;
	}
}


void MoveRight(vector <int>& grid){
			for(int q = 1; q <= 4 ; q++){
				for(int i = 4*(q)-1; i >= 4*(q-1); i--){
					if(grid[i] == 0){
						bool flag = true;
						for(int j = i-1; j >= 4*(q-1) && flag == true; j--){
							if (grid[j] != 0){
								grid[i] = grid[j];
								grid[j] = 0;
								flag = false;
							}
						}
					}
				}
			}
		}

void AddRight(vector <int>& grid){
			for(int q = 1; q <= 4 ; q++){
				for(int i = 4*(q)-1; i >= 4*(q-1); i--){
						bool flag = true;
						for(int j = i-1; j >= 4*(q-1) && flag == true; j--){
							if (grid[j] == grid[i]){
								grid[i] = 2*grid[j];
								grid[j] = 0;
								MoveRight(grid);
								flag = false;
							}
							else{
								flag = false;
							}
						}
					}
				}
			}

void MoveLeft(vector <int>& grid){
			for(int q = 1; q <= 4 ; q++){
				for(int i = 4*(q-1); i < 4*q; i++){
					if(grid[i] == 0){
						bool flag = true;
						for(int j = i+1; j < 4*q && flag == true; j++){
							if (grid[j] != 0){
								grid[i] = grid[j];
								grid[j] = 0;
								flag = false;
							}
						}
					}
				}
			}
		}
void AddLeft(vector <int>& grid){
			for(int q = 1; q <= 4 ; q++){
				for(int i = 4*(q-1); i < 4*q; i++){
						bool flag = true;
						for(int j = i+1; j < 4*q && flag == true; j++){
							if (grid[j] == grid[i]){
								grid[i] = 2*grid[j];
								grid[j] = 0;
								MoveLeft(grid);
								flag = false;
							}
							else{
								flag = false;
							}
						}
					}
				}
			}

void RotateGrid(vector <int>& grid){
	vector<int> rotatedgrid;
	for(int q = 0; q < 4; q++){
		for(int i=0; i < 4; i++){
			rotatedgrid.push_back( grid[4*i + q]);
			}
		}
	for(int j=0; j < 16; j++){
		grid[j] = rotatedgrid[j];
	}
}

void GenTwo(vector<int>& grid){
	int i = 0;
	for (int q = 0; q < 16; q++){
			if (grid[q] == 0){
				i++;
			}
		}
	int n = (rand() % i + 1);
		for (int q = 0; q < 16; q++) {
					if (grid[q] == 0) {
						n--;
						if(n == 0){
						grid[q] = 2;
				}
			}
		}
	}

void MoveDir(vector<int>& grid, char direction){

	if(direction == 'w'){
		RotateGrid(grid);
		MoveLeft(grid);
		AddLeft(grid);
		RotateGrid(grid);
		}
	if(direction == 'a'){
		MoveLeft(grid);
		AddLeft(grid);
		}
	if(direction == 's'){
		RotateGrid(grid);
		MoveRight(grid);
		AddRight(grid);
		RotateGrid(grid);
		}
	if(direction == 'd'){
		MoveRight(grid);
		AddRight(grid);
		}
}

bool GameOver(vector<int>& grid) {
	vector<int> grid2;
	grid2 = grid;
	MoveDir(grid2, 'd');
	MoveDir(grid2, 's');
	MoveDir(grid2, 'a');
	MoveDir(grid2, 'w');
	if (grid2 != grid) {
		return true;
	}
	else{
		return false;
	}
}
