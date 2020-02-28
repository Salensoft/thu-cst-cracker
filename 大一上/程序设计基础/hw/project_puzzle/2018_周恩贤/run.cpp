#include "my_function.h"

void run_3x3(){
	cout << endl << "Using BFS to solve 3*3 puzzle:" << endl;
	int puzzle[3*3];
	for (int i=0;i<3*3-1;i++) //initialize
		puzzle[i] = i+1;
	puzzle[3*3-1] = -1;
	srand(unsigned(time(NULL))); //for the function random_shuffle
	random_shuffle(puzzle, puzzle+3*3); 	//����Ҫ��(3)
	cout << "\nPuzzle after shuffling:" << endl;
	print_puzzle(3,3,puzzle);
	bool mark = can_solve(3, 3, puzzle); //����Ҫ��(4)
	if(mark){
		cout << "Solvable!\n";
		Sleep(1000);
	}
	else {
		cout << "Unsolvable!\n";
		cout << "Swap to solvable? [y/n]";
		reshuffle(3,3,puzzle,mark);
	}
	system("cls");
	print_instruction();
	print_puzzle(3,3,puzzle);
	read_3x3(puzzle,3,3);		
}

void run_MxN(){
	int M,N;
	char c;
	cout << "\nPlease enter the size of the puzzle M,N (M,N > 1)" << endl;
	//����cin.fail�Д��Ƿ�ݔ�����_ 
	if(readsize(M, N)){  //����Ҫ��(2) 
		int puzzle[M*N];
		for (int i=0;i<M*N-1;i++) //initialize
			puzzle[i] = i+1;
		puzzle[M*N-1] = -1;
		srand(unsigned(time(NULL))); //for the function random_shuffle
		random_shuffle(puzzle, puzzle+M*N); 	//����Ҫ��(3)
		cout << "\nPuzzle after shuffling:" << endl;
		print_puzzle(M,N,puzzle);
		bool mark = can_solve(M, N, puzzle); //����Ҫ��(4)
		if(mark)
			cout << "Solvable!\n";
		else {
			cout << "Unsolvable!\n";
			cout << "Swap to solvable? [y/n]";
			reshuffle(M,N,puzzle,mark);
		}
		cout << "Keep Playing? [y/n]" << endl; //����Ҫ��(5)
		read_2(M,N,puzzle);	
	}else{
		print_error("Please enter two numbers! (M>1, N>1)\n");
		run_MxN();
	}
}

/* 
		�Д෽ʽ : ���򔵵���ż�� 
	�հ׸������Ƅ� : ����׃����ż��
	�հ׸������Ƅ� : �ஔ�ĳ��������N-1�����B�m���Q,
					 ��N�攵->����׃����ż��
					 ��Nż��->��׃����ż��
*/ 
bool sum_of_reverse_number(int M, int N,int puzzle[]){
	int num = 0;
	for (int i=0; i<M*N; i++){
		for (int j=i+1; j<M*N; j++){
			if (puzzle[i] == -1 || puzzle[j] == -1)
				continue;
			if(puzzle[i] > puzzle[j]) {
				num = !num;  
			}
		}
	}
	return num ; 
}


bool can_solve(int M, int N, int puzzle[]){
	int num = sum_of_reverse_number(M, N, puzzle);
	if (N%2 == 1){
		return (num%2 == 0);
	}
	//check the blank if it is in the k row;
	int pos = find(M, N, puzzle, -1);
	int row = pos / N;
	int move = (M-1) - row;
	return ((num + move) %2 == 0);  
};

void reshuffle(int M,int N,int puzzle[],bool mark){
	char c;
	cin >> c;
	if(!cin.fail()){
		switch(c){
			case 'y':
			case 'Y':
				while (!mark){
					for (int i=0; i<M*N; i++){
						if (puzzle[i]!=-1 && puzzle[i+1]!=-1){
							swap(puzzle[i],puzzle[i+1]);
							break;
						}
					}
					cout << "\nPuzzle after changing:" << endl;
					print_puzzle(M,N,puzzle);
					mark = can_solve(M, N, puzzle); //����Ҫ��(4)
					if(mark)
						cout << "Solvable!\n";
					else 
						cout << "Unsolvable!\n";
					Sleep(1000); //��ϴ֮�g�и�ͣ�� 
					}
				break;
			case 'n':
			case 'N': 
				break;
			default :
				print_error("You've entered a wrong instruction!\nPlease re-enter:\n");
		}
	}else{
		print_error("You've entered a wrong instruction!\nPlease re-enter:\n");
		read_2(M,N,puzzle);
	}
}

