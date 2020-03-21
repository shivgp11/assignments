package hw4;

/**
 * @author Shiv
 */
import hw4.api.ScoringCategory;
import java.util.ArrayList;

import hw4.api.ScoringCategory;

/**
 * I created a super class "Daddy" which impliments the scoring category interface. 
 * There are 9 different Scoring Categories: AllButOneOfAKind, AllButTwoOfAKind, AllOfAKind, 
 * AllPrimes, Chance, FullHouse, LargeStraight, and SmallStraight.
 *  The 9 scoring categories share all but one method which is the isSatisfiedBy method. That's the method that I overrode 
 *  for each of the 9 classes. The 9 categories inherit
 * the rest of the methods from the parent superclass. 
 */
/**
 * Game state for a dice game such as Yahtzee. The game consists of a list of
 * <code>ScoringCategory</code> objects, each of which is responsible for
 * keeping track of the dice used to satisfy it and of its own contribution to
 * the total score. Clients interact directly with the category objects, which
 * are obtained using method <code>getCategories()</code>. The total score for
 * the game may be obtained via the <code>getScore</code> method. This class
 * also keeps track of several game attributes: the number of dice being used in
 * the game, the maximum value (number of "sides") of the dice, and the number
 * of times the dice may be re-rolled in each round.
 */
public class DiceGame {

	/**
	 * Constructs a new DiceGame based on the given parameters. Initially the list
	 * of categories is empty.
	 * 
	 * @param numDice     number of dice used in this game
	 * @param maxDieValue maximum face value (number of faces) for each die
	 * @param numRolls    number of times the dice can be rolled in each round
	 */

	/**
	 * keeps track of the max number of dice
	 */
	private int dice;
	/**
	 * keeps track of the number of sides the dice has aka the maxDieValue
	 */
	private int sides;
	/**
	 * the number of rolls that are set per round
	 */
	private int rolls;
	/**
	 * an array list of the individual categories of scoring categories used to
	 * calculate score and keep track of the different sub classes of scoring
	 * category
	 */
	private ArrayList<ScoringCategory> categories = new ArrayList<ScoringCategory>();

	public DiceGame(int numDice, int maxDieValue, int numRolls) {
		dice = numDice;
		sides = maxDieValue;
		rolls = numRolls;
		categories.clear();
		;

	}

	/**
	 * Adds a scoring category to this game.
	 * 
	 * @param category scoring category to add
	 */
	public void addCategory(ScoringCategory category) {
		categories.add(category);
	}

	/**
	 * Returns the list of categories in this game.
	 * 
	 * @return list of categories
	 */
	public ArrayList<ScoringCategory> getCategories() {
		return categories;
	}

	/**
	 * Returns a new Hand corresponding to the number of dice, maximum die value,
	 * and number of rolls for this game. Initially all dice in the hand are
	 * available to be rolled.
	 * 
	 * @return new Hand based on this game's parameters
	 */
	public Hand createNewHand() {
		Hand elMano = new Hand(dice, sides, rolls);
		return elMano;
	}

	/**
	 * Returns the current total score for all categories.
	 * 
	 * @return total score for all categories
	 */
	public int getScore() {
		int score = 0;
		for (int i = 0; i < categories.size(); i++) {
			score += categories.get(i).getScore();
		}

		return score;
	}

}
