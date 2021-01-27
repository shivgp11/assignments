package hw4;
/**
 * This is the super class that implements the ScoringCategories interface. The methods implemented are shared by the 9 
 * scoring categories with the exception of the isSatisfiedBy method which is overriden in each of the 9 subclasses. 
 * 
 * @author Shiv 
 *
 */
import hw4.api.ScoringCategory;

import hw4.Hand;

public class Daddy implements ScoringCategory {
	/**
	 * represents the state of a category (filled or not filled)
	 */
	protected boolean filled;
	/**
	 * represents the score of the game: the net score of scores of the filled categories
	 */
	protected int score;
	/**
	 * represents an instance of a hand 
	 */
	protected Hand elMano;
	/**
	 * the name of the scoring category and the display name
	 */
	protected String name;

	public boolean isFilled() {

		return filled;
	}

	public int getScore() {
		if (isFilled()) {
			return score;
		}
		return 0;
	}

	public Hand getHand() {
		if (!isFilled()) {
			return null;
		}
		return elMano;
	}

	public String getDisplayName() {

		return name;
	}

	public void fill(Hand hand) {

		if (isFilled() || !hand.isComplete()) {
			throw new IllegalStateException();
		} else {
			filled = true;
			elMano = hand;
			score = getPotentialScore(hand);
		}

	}

	public boolean isSatisfiedBy(Hand hand) {
		return false;
	}

	public int getPotentialScore(Hand hand) {
		if (!isSatisfiedBy(hand)) {
			return 0;
		}
		return score;
	}

}
