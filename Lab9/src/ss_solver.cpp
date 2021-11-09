/* Name: Sarah Huang
 * Date: 11/8/21
 * Program: ss_solver.cpp
 * Purpose: It takes a grid on its command line, and then each line of standard input specifies a shape. 
 *			After reading all of the shapes, your program should output how to apply each shape to solve the puzzle. 
 *			If there is no solution, it should simply exit with no output.
 */

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


class Shifter{
	public:
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		bool Apply_Shape(int index, int r, int c);
		bool Find_Solution(int index);
		void Print_Solution() const;

	protected:
		vector <string> Grid;				//Grid = Vector of 0's and 1's
		vector <vector <string> > Shapes;	//Shapes in the order in which they appear in standard input
		vector <int> Solution_Rows;			//Starting row of shapes when finding solution and done
		vector <int> Solution_Cols;			//Starting col of shapes when finding solution and done
};


/* 1. Read_Grid_And_Shapes() initializes the grid from argc/argv
 * 2. Reads from standard input to get the shapes.*/
bool Shifter::Read_Grid_And_Shapes(int argc, const char **argv){
	stringstream ss;
	int numShapes = 0;			//Total number of shapes
	string input;				//Shape
	string separate;			//Separate shape into different blocks

	if(argc <= 1)
		return false;

	for(int i = 0; i < argc-1; i++){		
		Grid.push_back(argv[i+1]);
	}

	//Need to resize in order to access each element
	Shapes.resize(10);

	while(getline(cin, input)){
		ss.clear();
		ss << input;
		ss >> separate;

		Shapes[numShapes].push_back(separate);	

		while(ss.peek() == ' '){
			ss.clear();
			ss >> separate;
			Shapes[numShapes].push_back(separate);
		}
		numShapes++;
	}
	Shapes.resize(numShapes);
	Solution_Rows.resize(numShapes);
	Solution_Cols.resize(numShapes);

	return true;
}



/* 1. Apply_Shape() applies the shape in Shapes[index] to the grid, starting at row r and column c. 
 * 2. If you call Apply_Shape twice with the same arguments, you'll end up with same grid as before the two calls. */
bool Shifter::Apply_Shape(int index, int r, int c){
	(void) index;								//Specific shape
	(void) r;									//Starting row
	(void) c;									//Starting col
	bool goodRow = false, goodCol = false;		//Shape can fit with starting row, col
	bool possible = false;						//Shape could fit here as a solution

	if(r + Shapes[index].size() <= Grid.size())
		goodRow = true;
	if(c + Shapes[index][0].size() <= Grid[0].size())
		goodCol = true; 

	if(goodRow && goodCol){
		possible = true;		
		for(unsigned int i = 0; i < Shapes[index].size(); i++){
			for(unsigned int j = 0; j < Shapes[index][i].size(); j++){
				//Sword + Sword = Shield
				if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '1')
					Grid[r+i][c+j] = '0';

				//Sword + Shield = Sword
				else if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '0')
					Grid[r+i][c+j] = '1';
			}
		}
	}
	return possible;
}


/* 1. Find_Solution() is the recursive procedure.  
 * 2. It tries all possible starting positions for Shape[index], 
 *	  and calls Find_Solution() recursively to see if that's a correct way to use Shape[index]. 
 * 3. If a recursive call returns false, then it "undoes" the shape by calling Apply_Shape() again.*/
bool Shifter::Find_Solution(int index){
	(void) index;				//Specific shape
	unsigned int num_ones = 0;	//Number of ones
	
	for(unsigned int row = 0; row < Grid.size(); row++){
		for(unsigned int col = 0; col < Grid[0].size(); col++){
			
			if(index < (int) Shapes.size()){	
				if(Apply_Shape(index, row, col) == true){
					Solution_Rows[index] = row;
					Solution_Cols[index] = col;				
					index++;
					
					//If the applied shapes are not the solution
					if(!Find_Solution(index)){
						index--;
					}
					else{						
						num_ones = 0;
						for(unsigned int y = 0; y < Grid.size(); y++){
							for(unsigned int z = 0; z < Grid[0].size(); z++){
								num_ones++;
							}
						}
						
						if(num_ones == (Grid.size() * Grid[0].size())){
							return true;
						}
					}
				}		
			}
		}
	}

	for(unsigned int i = 0; i < Grid.size(); i++){
		for(unsigned int j = 0; j < Grid[0].size(); j++){
			if(Grid[i][j] == '1'){
				num_ones++;
			}
		}
	}

	if(num_ones != (Grid.size() * Grid[0].size())){
		index--;
		Apply_Shape(index, Solution_Rows[index], Solution_Cols[index]);
		return false;
	}
	else
		return true;
}


/* 1. This prints the solution on standard output.*/
void Shifter::Print_Solution() const{
	for(unsigned int row = 0; row < Shapes.size(); row++){
		for(unsigned int col = 0; col < Shapes[row].size(); col++){
			cout << Shapes[row][col] << " ";
		}
		cout << Solution_Rows[row] << " " << Solution_Cols[row] << endl;
	}
}



int main(int argc, const char **argv){
	Shifter shwifty;
	
	shwifty.Read_Grid_And_Shapes(argc, argv);
	shwifty.Find_Solution(0);
	shwifty.Print_Solution();
	
	return 0;
}
