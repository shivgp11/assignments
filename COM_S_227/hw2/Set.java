package hw2;
import hw2.TennisGame;
/**
 * 
 * @author Shiv
 *
 *Tracks the set
 */
public class Set {

	private TennisGame game;
	private int player0Wins;
	private int player1Wins;
	private int bareMinimumGamesToWin;
	private boolean doesPlayer1ServeFirst;

	/**
	 * Constructs a set with the given minimum number of games. If the parameter
	 * player1ServesFirst is true, then player 1 will be the server in the initial
	 * current game; otherwise player 0 will start out as server.
	 * 
	 * @param minimumGamesToWin  number of games needed to win the set
	 * 
	 * 
	 * @param player1ServesFirst true if player 1 is the server in the first game
	 * 
	 */
	public Set(int minimumGamesToWin, boolean player1ServesFirst)
	{
		bareMinimumGamesToWin = minimumGamesToWin;
		game = new TennisGame();
		
		if (player1ServesFirst == true) 
		{
			doesPlayer1ServeFirst = true;
		} 
		else 
		{
			doesPlayer1ServeFirst = false;
		}
	}

	/**
	 * Invokes serve on the current game and updates the winner's count of games won
	 * if the action ends the current game. Does nothing if the set is over or if
	 * the current game is over.
	 * 
	 * @param serviceFault true if there is a service fault, false otherwise
	 */
	public void serve(boolean serviceFault) 
	{
		
		if (game.isOver() == false && isSetOver() == false)
		{
			game.serve(serviceFault);
			if (game.serverWon() == true && doesPlayer1ServeFirst == true)
			{
				player1Wins = player1Wins + 1;
			}
			else if (game.serverWon() == true && doesPlayer1ServeFirst == false)
			{
				player0Wins = player0Wins + 1;
			}
		}
		else if(game.isOver() == true && isSetOver() == false)
		{
			game.serve(serviceFault);
		}
	}

	/**
	 * Invokes hit on the current game and updates the winner's count of games won
	 * if the action ends the current game. Does nothing if the set is over or if
	 * the current game is over.
	 * 
	 * @param fault       true if the hit results in a fault ending the rally
	 * @param outOfBounds true if the hit goes over the net but on an out of bounds
	 *                    trajectory
	 */
	public void hit(boolean fault, boolean outOfBounds) 
	{

		if (game.isOver() == false && isSetOver() == false)
		{
			game.hit(fault, outOfBounds);
			if (game.serverWon() == true && doesPlayer1ServeFirst == true)
			{
				player1Wins = player1Wins + 1;
			}
			else if (game.serverWon() == true && doesPlayer1ServeFirst == false)
			{
				player0Wins = player0Wins + 1;
			}
		}
	}

	/**
	 * Invokes miss on the current game and updates the winner's count of games won
	 * if the action ends the current game. Does nothing if the set is over or if
	 * the current game is over.
	 */
	public void miss() 
	{
		if (game.isOver() == false && isSetOver() == false)
		{
			game.miss();
			if (game.serverWon() == true && doesPlayer1ServeFirst == true)
			{
				player1Wins = player1Wins + 1;
			}
			else if (game.serverWon() == true && doesPlayer1ServeFirst == false)
			{
				player0Wins = player0Wins + 1;
			}
		}
	}

	/**
	 * Invokes setScore on the current game and updates the winner's count of games
	 * won if the action ends the current game. Does nothing if the set is over or
	 * if the current game is over. This method is intended for testing and does not
	 * check that the given scores are realistic.
	 * 
	 * @param serverScore   score to be set for the server
	 * @param receiverScore score to be set for the receiver
	 */
	public void fastForward(int serverScore, int receiverScore) 
	{
		game.setScore(serverScore, receiverScore);
		
		if (game.isOver() == true && isSetOver() == false)
		{
			
			if (game.serverWon() == true && doesPlayer1ServeFirst == true)
			{
				player1Wins = player1Wins + 1;
			}
			else if (game.receiverWon() == true && doesPlayer1ServeFirst == true)
			{
				player0Wins = player0Wins + 1;
			}
			else if (game.serverWon() == false && doesPlayer1ServeFirst == false)
			{
				player1Wins = player1Wins + 1;

			}
			else if (game.receiverWon() == false && doesPlayer1ServeFirst == false)
			{
				player0Wins = player0Wins + 1;
			}
		}
	}

	/**
	 * Starts a new game in this set, switching the service to the opposite player.
	 * This method does nothing if the current game is still in progress, or if the
	 * set is over.
	 */
	public void newGame() 
	{
		{
			if (game.isOver() == true && isSetOver() == false)
			{
				game = new TennisGame();
				doesPlayer1ServeFirst = !doesPlayer1ServeFirst;
			}
		}
	}

	/**
	 * Returns true if the current game is over.
	 * 
	 * @return true if the current game is over, false otherwise
	 */
	public boolean isCurrentGameOver() {
		return game.isOver();

	}

	/**
	 * Returns true if the set is over. The set ends when a player has won the
	 * minimum number of games AND has won at least two games more than the other
	 * player.
	 * 
	 * @return true if the set is over, false otherwise
	 */
	public boolean isSetOver() {
		if (player0Wins >= bareMinimumGamesToWin && player0Wins >= player1Wins + 2) {
			return true;
		} else if (player1Wins >= bareMinimumGamesToWin && player1Wins >= player0Wins + 2) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Returns a string representation of the current status of the set in the form
	 * "Set: x-y Game: ss". Here x is the number of games won by the currently
	 * serving player, y is the number of games won by the other player, and ss is
	 * the score string for the current game. If the parameter useCallString is
	 * false, then the string ss is formatted as in TennisGame.getScore();
	 * otherwise, the string ss is formed according to the conventions of
	 * TennisGame.getCallString().
	 * 
	 * @param useCallString
	 * @return string representation of the set's current status
	 */
	public java.lang.String getCurrentStatus(boolean useCallString)
	{
		if (useCallString == false && doesPlayer1ServeFirst == true)
		{
			return "Set: " + player1Wins + "-" + player0Wins + " Game: " + game.getScore();
		}
		else if (useCallString == false && doesPlayer1ServeFirst == false)
		{
			return "Set: " + player0Wins + "-" + player1Wins + " Game: " + game.getScore();
		}
		else if (useCallString == true && doesPlayer1ServeFirst == true)
		{
			return "Set: " + player1Wins + "-" + player0Wins + " Game: " + game.getCallString();
		}
		else if (useCallString == true && doesPlayer1ServeFirst == false)
		{
			return "Set: " + player0Wins + "-" + player1Wins + " Game: " + game.getCallString();
		}
		return null;
	}

	/**
	 * Returns the player (0 or 1) who is the server in the current game.
	 * 
	 * @return server in the current game
	 */
	public int whoIsServing() 
	{
		if (doesPlayer1ServeFirst == true)
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}

	/**
	 * Returns the number of games won by player 0.
	 * 
	 * @return number of games won by player 0
	 */
	public int player0GamesWon() {
		return player0Wins;
	}

	/**
	 * Returns the number of games won by player 1.
	 * 
	 * @return number of games won by player 1
	 */
	public int player1GamesWon() {
		return player1Wins;
	}
}
