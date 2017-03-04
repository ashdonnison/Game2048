import java.util.*;

public class Play2048
{
	public static void main (String[] args)
	{
		Game2048 newGame = new Game2048(4, 4);
		
		newGame.play();	
	}
}