#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game2048
{
private:
    int nrow;
    int ncol;
    int **board;
    int state;
    int score;
	int highScore;

public:
    // when this constructor is called it will return a pointer to the Game2048 object (see main function)
    Game2048(int r, int c)
    {
        nrow = r;
        ncol = c;

        board = new int *[r]; // allocate memory for row pointers
        board[0] = new int [r*c]; // allocate memory for 1D array of all board elements
        
		for(int i=0; i<r; ++i) // link the row pointer to the correct elements in 1D array
            board[i] = board[0]+c*i;

        for(int i=0; i<r; ++i)
            for(int j=0; j<c; ++j)
                board[i][j]=0; 
    }

	
    ~Game2048() 
    {
        // this will be the default destructor.
        // it will be automaticaly called when the Game2048 object goes out of scope in a function
        delete [] board[0];
        delete [] board;
    }


	void boardPrint()
    {
        for(int i=0; i<nrow; ++i)
        {
            for(int j=0; j<ncol; ++j)
            {
				for(int k=0; k < 6; k++)
				{
					if((k < 1) || (k >1))
						cout << " ";
					else if(k = 1)
					{
						if(board[i][j]==0) 
							cout << " -";
						else 
							cout << " " << board[i][j];
					
						if(board[i][j] < 10)
							k = 2;
						else if(board[i][j] < 100)
							k = 3;
						else if(board[i][j] < 1000)
							k = 4;
						else if(board[i][j] < 10000)
							k = 5;
					}
				}
			}
					
            cout << endl;
        }
        cout << endl;
    }
	
	void customBoard(int r, int c)
    {
        nrow = r;
        ncol = c;

        board = new int *[r]; // allocate memory for row pointers
        board[0] = new int [r*c]; // allocte memory for 1D array of all board elements
        for(int i=0; i<r; ++i) // link the row pointer to the correct elements in 1D array
            board[i] = board[0]+c*i;

        for(int i=0; i<r; ++i)
            for(int j=0; j<c; ++j)
                board[i][j]=0; 
    }
	
	// Displays menus and the choices
	void menu()
	{
		switch(state)
		{
			// Pre Game Menu
			case 0:
				cout << "1. Start New Game \n2. Start Custom Game \n3. Quit \n\nDecision: ";
				scanChar();
			break;
			
			// Playing Game Menu
			case 1:
				cout << "W.Up A.Left S.Down D.Right U.Undo Q.Quit\n";
				cout << "Score: " << score <<  "  High Score: " << highScore;
				cout << "\n\nNext Move:";
				scanChar();
			break;
			
			// Custom Game Set Up
			case 2:
				cout << "What size board? (n*n)\n";
				scanInt();
			break;
			
			default:
			break;
		}
	}
	
	
	// Scans for Character input and turns to upper case
	void scanChar()
	{
		char x;
		cin >> x;
		
		if((96 < x) && (x < 123))	// Converts to uppercase if lowecase
			x = x - 32;
		else
			x = x;
	
		decision(x);
	}
	
	
	//Scans for Interger Input
	void scanInt()
	{
		int x;
		cin >> x;
	
		decision(x);
	}
	
	// Decisions based on user input_iterator
	void decision(int dec)
	{
		cout << endl;
		
		// Pre Game Menu
		if (state == 0)
		{
			switch (dec) {
				case '1':	// 1. Standard Game
					customBoard(4, 4); //Resets board back to default size
					rand2or4(2);
					state = 1;
					boardPrint();
				break;
				
				case '2':	// 2. Custom Game
					state = 2;
				break;
				
				case '3':	// 3. Quit
					exit(EXIT_SUCCESS);
				break;
				
				default:
				break;}
		}
		
		else if(state == 1)
		{
			switch(dec)
			{
				case 'W':	// Swipes Up
					rotate90clock(3);
					swipeLeft();
					addNum();
					swipeLeft();
					rotate90clock(1);
					rand2or4(1);
				break;
		
				case 'A':	// Swipes Left
					swipeLeft();
					addNum();
					swipeLeft();
					rand2or4(1);
				break;
				
				case 'S':	// Swipes Down
					rotate90clock(1);
					swipeLeft();
					addNum();
					swipeLeft();
					rotate90clock(3);
					rand2or4(1);
				break;
				
				case 'D':	// Swipes Right
					rotate90clock(2);
					swipeLeft();
					addNum();
					swipeLeft();
					rotate90clock(2);
					rand2or4(1);
				break;
				
				case 'Q':	// Quits Game back to main menu
					state = 0;
					score = 0;
					cout << "Quitting Game... \n\n";
					menu();
				break;
				
				case '0':		// Game board is full
					cout << "\nGame Over. Board is full and no valid moves.\n";
					cout << "You're Score was: " << score;
					cout << "\n\nReturning back to Main Menu.\n\n";
					state = 0;
					score = 0;
					menu();
				break;
	
				default:
				break;
			}
			
			boardPrint();
		}
			
		// Custom Game Setup
		else if(state == 2)	
		{
			customBoard(dec, dec);
			rand2or4(2);
			boardPrint();
			state = 1;
		}
		
		menu();
	}
	
	
	// Pushes all the numbers to the far left
	void swipeLeft()
	{
		for(int i = 0; i < nrow; i ++)
			for(int j = 0; j < ncol; j ++)
				if(board[i][j] == 0)
					for (int k = (j+1); k < ncol; k ++)
						if (board[i][k] != 0)
						{
							board[i][j] = board[i][k];
							board[i][k] = 0;
							k = ncol;
						}
	}
	
	void addNum()
	{
		for(int i = 0; i < nrow; i ++)
			for(int j = 1; j < ncol; j ++)
				if(board[i][j] != 0)
					if(board[i][j] == board [i][j-1])
					{
						board[i][j-1] = board[i][j-1] * 2;
						score = score + board[i][j-1];
						if(score > highScore)
							highScore = score;
						board[i][j] = 0;
						j ++;
					}
	}
	
	
	void rand2or4(int n)
	{
		srand(time(0));
		
		for (int a = 0; a < n; a ++)
		{
			int x = rand() % nrow;	// Finds a random co-ordinate on the game board
			int y = rand() % ncol;;
			int z = 1 + rand()% 4;		// Creates a randon number z, between 2 and 4
			
			if (z <= 3) 
				z = 2;			// If greater than or equal to 3, make z 4
			else 
				z = 4;
			if ( board [x][y] > 1 )					// If board location already filled by a number
					a --;								// Try again	
			else
				board[x][y] = z;					// Else set to 2 or 4
		}
	}
	
	// Rotates the matrix t amount of times clockwise
	void rotate90clock(int t)
	{
		for(int i = 0; i < t; i++) 
		{
			for(int r = 0; r < nrow; r++)
				for(int c = r; c < ncol; c++)
						swap(board[r][c], board[c][r]);

			for(int r = 0; r < nrow; r++)
				for(int c = 0; c < ncol/2; c ++)
						swap(board[r][c], board[r][ncol - c -1]);
		}
	}
};


int main()
{
    Game2048 *myGame = new Game2048(4,4);
	myGame -> menu();
	
	return 0;
}

//