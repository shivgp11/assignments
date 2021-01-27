package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class LargeStraight extends Daddy {
	/**
	 * set amount of points received for filling category
	 */
	private int points;
	/**
	 * tracks if category is satisfied given hand
	 */
	private boolean satisfied;

	public LargeStraight(String name, int points) {
		this.name = name;
		this.points = points;
	}

	/**
	 * Scoring category for a "large straight". A hand with N dice satisfies this
	 * category only if there are N distinct consecutive values. For a hand that
	 * satisfies this category, the score is a fixed value specified in the
	 * constructor; otherwise, the score is zero.
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {

		satisfied = false;
		int count = 0;
		int[] sample = hand.getAllValues();
		if (sample.length > 2) {
			for (int i = 0; i < sample.length - 1; i++) {
				if (sample[i + 1] == (sample[i] + 1)) {
					count++;
				}
			}
			if (count >= sample.length - 1) {
				satisfied = true;
				score = points;
			}
		} else if (sample[1] == (sample[0] + 1)) {
			satisfied = true;
			score = points;
		}

		return satisfied;
	}

}
