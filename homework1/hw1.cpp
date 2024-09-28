#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
using namespace std;
class Grid{
	public:
		vector<vector<int>> grid;
		int box_size;
		int grid_size;

		Grid(int Box_size = 3, int Grid_size = 9): box_size(Box_size),grid_size(Grid_size),grid(Grid_size,vector<int>(Grid_size,0)){}
		Grid(const Grid& other){
			box_size = other.box_size;
        	grid = other.grid;
		}
		Grid& operator = (const Grid& other){
			if (this == &other) {
            	return *this;
        	}
	        box_size = other.box_size;
	        grid = other.grid;
	        return *this;
		}
		vector<int> getRow(int row){
			return grid[row];	
		}
		vector<int> getColumn(int col){
			vector<int> column(grid_size);
        	for (int i = 0; i < grid_size; ++i) {
            	column[i] = grid[i][col];
        	}
        	return column;
		}
		vector<int> getBox(int row,int col){
			vector<int> box;
        	int RowStart = (row / box_size) * box_size;
        	int ColStart = (col / box_size) * box_size;

       	 	for (int i = 0; i < box_size; ++i) {
            	for (int j = 0; j < box_size; ++j) {
                	box.push_back(grid[RowStart + i][ColStart + j]);
            	}
        	}
        	return box;
		}
		// serialize
    	string serialize() const {
        	stringstream ss;
        	for (int i=0;i<grid.size();i++) {
            	for (int j=0;j<grid.size();j++) {
                	ss << grid[i][j];
            	}
        	}
        	return ss.str();
    	}	
		
    	bool operator==(const Grid &other){
        	return grid == other.grid;
    	}
};
class Sudoku{
	private :
		Grid my_grid;
	public:
		Sudoku(){}
		Sudoku(const Sudoku& other){
			my_grid = other.my_grid;
		}
		Sudoku& operator = (const Sudoku& other){
			if (this == &other) {
            	return *this;
        	}
	        my_grid = other.my_grid;
	        return *this;
		}
		void parse(string input){
        	for (int i = 0; i < my_grid.grid_size; ++i) {
            	for (int j = 0; j < my_grid.grid_size; ++j) {
                	char ch = input[i * my_grid.grid_size + j];
                		my_grid.grid[i][j] = ch - '0'; // Convert char to int
            	}
        	}
		}
		void print(){
			for(int i=0;i<my_grid.grid_size;++i){
				for(int j=0;j<my_grid.grid_size;++j){
					cout<<my_grid.grid[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		vector<int> getInference(int row,int col){
			vector<int> candidate;
            vector<int> Row = my_grid.getRow(row);
            vector<int> Col = my_grid.getColumn(col);
            vector<int> Box = my_grid.getBox(row, col);
			set<int> usedNumbers;
            for (int num : Row) usedNumbers.insert(num);
            for (int num : Col) usedNumbers.insert(num);
            for (int num : Box) usedNumbers.insert(num);
            for (int num = 1; num <= 9; ++num) {
            	if (usedNumbers.find(num) == usedNumbers.end()) {
                	candidate.push_back(num);
                }
            }
        	return candidate;
		}
};

void test(string input ){
	Sudoku test1;
	cout<<"test1:"<<endl;
	test1.parse(input);
	test1.print();
	vector<int> test_result = test1.getInference(3,7);
	cout<<"inference_result in pos (3,7):"<<endl;
	for(int i=0;i<test_result.size();i++){
		cout<<test_result[i]<<" ";
	}
	cout<<endl;
	Sudoku test2(test1);
	Sudoku test3 = test2;
	cout<<"test2:"<<endl;
	test2.print();
	cout<<"test3:"<<endl;
	test3.print();
	
}
int main(){
	string input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
	test(input);
	return 0;
}