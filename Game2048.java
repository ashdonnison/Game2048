import java.util.*;

public class Game2048
{
	private int nrow;
    private int ncol;
    private int[][] board;
	private int gameState;
	private int highScore = 0;
	private int score = 0;
	
	
	// Creates the Board
	public Game2048(int r, int c)
    {
        nrow = r;
        ncol = c;

        board = new int[r][c];

        for(int i=0; i<nrow; i++)
            for(int j=0; j<ncol; j++)
                board[i][j]=0;
    }
	
	// Creates the Board
	private void CustomBoard(int r, int c)
    {
        nrow = r;
        ncol = c;

        board = new int[r][c];

        for(int i=0; i<nrow; i++)
            for(int j=0; j<ncol; j++)
                board[i][j]=0;
    }
	
	// Method for menu
	private void Menu()
	{	
		switch (gameState){
			case 0:		// Pre Game
				System.out.printf("1. Start New Game %n2. Start Custom Game %n3. Quit %n%nDecision: ");
				ScanChar();
			break;
		
			case 1:		// When game is playing
				System.out.println("W.Up A.Left S.Down D.Right U.Undo R.Redo Q.Quit");
				System.out.printf("Score: %d  High Score: %d %n%nNext Move: ", score, highScore); 
				ScanChar();
			break;
		
			case 2: 	// Custom Mode Board Size Selection		
				System.out.printf("%nWhat size board? (n*n)%n");
				ScanInt();
			break;
			
			default:
			break;
		}
	}
	
	// Method that creates random 2's or 4's, and can input how many needed
	private void Rand2or4(int n)
	{
		for (int a = 0; a < n; a ++)
		{
			int x = (int)(Math.random() * (nrow - 1) + 0.5);	// Finds a random co-ordinate on the game board
			int y = (int)(Math.random() * (ncol - 1) + 0.5);
			int z = (int)(Math.random() + 2.2);		// Creates a randon number z, between 2 and 4
			
			if (z >=3) 
				z=4;								// If greater than or equal to 3, make z 4
			
			if ( board [x][y] > 1 )					// If board location already filled by a number
				a --;								// Try again
			else
				board[x][y] = z;					// Else set to 2 or 4
		}
	}
	
	// SCans for an Integer
	private void ScanInt()
	{
		Scanner sc = new Scanner(System.in);
		int i = sc.nextInt();
		
		Selection(i);
	}
	
	// Scans Player/User Input of Character
	private void ScanChar()
	{
		Scanner s = new Scanner(System.in);
		char x = s.next().charAt(0);
		
		Selection(x);
	}
	
	// Menu selection function, for both in-game menu and pre game menu's
	private void Selection(int sel)
	{
		// Pre Game Menu
		if (gameState == 0)
		{
			switch (sel) {
				case '1':	// 1. Standard Game
					gameState = 1;
					Rand2or4(2);
					BoardPrint();
				break;
				
				case '2':	// 2. Custom Game
					gameState = 2;
				break;
				
				case '3':	// 3. Quit
					System.exit(0);
				break;
				
				default:
				break;
			}
			Menu();
		}
		
		// Game in Progress 
		else if (gameState == 1)
		{
			switch(sel){
				case 'W':	// Swipes Up
				break;
		
				case 'A':	// Swipes Left
					SwipeLeft();
					AddNum();
					SwipeLeft();
					Rand2or4(1);
				break;
				
				case 'S':	// Swipes Down
				break;
				
				case 'D':	// Swipes Right
				break;
				
				case 'Q':	// Quits Game back to main menu
					gameState = 0;
					CustomBoard(4, 4);
					highScore = score;
					score = 0;
					System.out.printf("Quitting Game... %n%n");
					Menu();
				break;
				
				case '8':
					Rand2or4(1);
				
				default:
				break;
			}
			// Have in game move selection
			BoardPrint();
		}
		
		// Custom Game Setup
		else if (gameState == 2)
		{
			CustomBoard(sel, sel);
			Rand2or4(2);
			gameState = 1;
			BoardPrint();
		}		
	}
	
	
	// Play function that runs in "Play2048"
	public void play()
	{
		Menu();
	}
	
	
	// Method for printing the Board
	private void BoardPrint()
	{
		System.out.println();
		for (int i = 0; i < nrow; i ++)
		{
			for(int j = 0; j < ncol; j ++)
			{
				if (board[i][j] == 0)
					System.out.printf(" -");
				else
					System.out.printf(" %d", board[i][j]);
			}
			System.out.println();
		}
		System.out.println();
		Menu();
	}

	
	//Pushes all the numbers to far left, without adding them
	private void SwipeLeft()
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
	
	
	// Adds two numbers next to each other 
	private void AddNum()
	{
		for(int i = 0; i < nrow; i ++)
			for(int j = 1; j < ncol; j ++)
				if(board[i][j] != 0)
					if(board[i][j] == board [i][j-1])
					{
						board[i][j-1] = board[i][j-1] * 2;
						score = score + board[i][j-1];
						board[i][j] = 0;
						j ++;
					}
	}	
}