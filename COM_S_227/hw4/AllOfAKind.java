package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class AllOfAKind extends Daddy {
	/**
	 * represents the state of category (Satisfied or not satisfied)
	 */
	private boolean satisfied;
	/**
	 * represents the set amount of points the player would receive for filling this
	 * category
	 */
	private int points;

	
	public AllOfAKind(String name, int points) {
		this.name = name;
		this.points = points;
	}

	/**
	 * Scoring category for a "yahtzee". A hand with N dice satisfies this category
	 * only if all N values are the same. For a hand that satisfies this category,
	 * the score is a fixed value specified in the constructor; otherwise, the score
	 * is zero.
	 * 
	 * @param name given display
	 * @param points set amount points a player recieves for filling category
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {
		satisfied = true;
		int[] sample = hand.getAllValues();
		for (int i = 0; i < sample.length - 1; i++) {
			if (sample[i] != sample[i + 1]) {
				satisfied = false;
			}
		}
		if (satisfied == true) {
			score = points;
		}

		return satisfied;
	}

}
