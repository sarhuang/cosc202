/* Name:
 * Date:
 * Program:
 * Purpose:
 */

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


class Shifter{
	public:
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		void Apply_Shape(int index, int r, int c);
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
	int r = 0;
	string input;
	string separate;

	if(argc <= 1)
		return false;


	for(int i = 0; i < argc-1; i++){		
		Grid.push_back(argv[i+1]);
	}


	Shapes.resize(10);

	while(getline(cin, input)){
		ss.clear();
		ss << input;
		ss >> separate;

		Shapes[r].push_back(separate);	

		while(ss.peek() == ' '){
			ss.clear();
			ss >> separate;
			Shapes[r].push_back(separate);
		}
		
		r++;
	}
	Shapes.resize(r);

	/*
	for(unsigned int row = 0; row < Shapes.size(); row++){
		for(unsigned int col = 0; col < Shapes[row].size(); col++){
			cout << Shapes[row][col] << " ";
		}
		cout << endl;
	}*/
	return true;
}


/* 1. Apply_Shape() applies the shape in Shapes[index] to the grid, starting at row r and column c. 
 * 2. If you call Apply_Shape twice with the same arguments, you'll end up with same grid as before the two calls. */
void Shifter::Apply_Shape(int index, int r, int c){
	(void) index;
	(void) r;
	(void) c;
	bool goodRow = false, goodCol = false;
	
	cout << "Apply Shape" << endl;
	
	if(r + Shapes[index].size() <= Grid.size())
		goodRow = true;
	if(c + Shapes[index][0].size() <= Grid[0].size())
		goodCol = true; 


	if(goodRow && goodCol){
		for(unsigned int i = 0; i < Shapes[index].size(); i++){
			for(unsigned int j = 0; j < Shapes[index][i].size(); j++){
				
				if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '1')
					Grid[r+i][c+j] = '0';

				else if(Shapes[index][i][j] == '1' && Grid[r+i][c+j] == '0')
					Grid[r+i][c+j] = '1';

				cout << "Grid (" << r+i << ", " << c+j << ") = " << Grid[r+i][c+j] << endl;
			}
		}
	}
}


/* 1. Find_Solution() is the recursive procedure.  
 * 2. It tries all possible starting positions for Shape[index], 
 *	  and calls Find_Solution() recursively to see if that's a correct way to use Shape[index]. 
 * 3. If a recursive call returns false, then it "undoes" the shape by calling Apply_Shape() again.*/
bool Shifter::Find_Solution(int index){
	(void) index;
	cout << "We are now finding the solution" << endl;

	for(unsigned int row = 0; row < Grid.size(); row++){
		for(unsigned int col = 0; col < Grid[0].size(); col++){
			
			Apply_Shape(index, r, c);
			
		}
	}
	return true;
}


/* 1. This prints the solution on standard output.*/
void Shifter::Print_Solution() const{
	cout << "I should be printing the solution now" << endl;
	
	for(unsigned int row = 0; row < Shapes.size(); row++){
		for(unsigned int col = 0; col < Shapes[row].size(); col++){
			cout << Shapes[row][col] << " " << Solution_Rows[row] << " " << Solution_Cols[col] << endl;
		}
	}
}



int main(int argc, const char **argv){
	Shifter shwifty;
	shwifty.Read_Grid_And_Shapes(argc, argv);
	
	cout << "Time to find some solutions!" << endl;
	
	if(shwifty.Find_Solution(0))
		shwifty.Print_Solution();
	
	return 0;
}


