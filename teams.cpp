#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here
void d_print(const int* team1, const int* team2, int size){
	for(int i = 0;i<size;i++){
		cout << team1[i] << " ";
	}
	cout << ":"; 
	for(int i = 0;i<size;i++){
		cout << team2[i] << " ";
	}
	cout << endl;
}

void print(const int* team1, const int* team2, const string* names, int size){
	string* team1N = new string[size/2];
	string* team2N = new string[size/2];
	for(int i = 0;i<size/2;i++){
		team1N[i] = names[team1[i]];
		team2N[i] = names[team2[i]];
	}
	printSolution(team1N, team2N, size/2);
	delete [] team1N;
	delete [] team2N;
}

void solve(int* team1, const string* names, int filledUp, int last, int size){
	if(filledUp == size/2) {
		bool *team = new bool[size];
		for(int i = 0;i<size/2;i++) team[i] = false;
		for(int i = 0;i<size/2;i++){
			team[team1[i]] = true;
		}
		int* team2 = new int[size/2];
		int slowI = 0;
		for(int i = 0;i<size;i++){
			if(!team[i]) team2[slowI++] = i;
		}
		//d_print(team1, team2, size/2);
		print(team1, team2, names, size);
		delete team2;
		return;
	}
	for(int i = last;i<size;i++){
		team1[filledUp] = i;
		solve(team1, names, filledUp+1, i+1, size);
	}
	return;
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
  ifstream f;
	f.open(argv[1]);
	if(f.fail()){
		cout << "Error" << endl;
		return 1;
	}
	int size;
	f >> size;
	string* names = new string[size]; 
	for(int i = 0;i<size;i++){
		f >> names[i];
	}
	int* team1 = new int[size/2];
	solve(team1, names, 0, 0, size);
	
	delete [] team1;
  return 0;
}
