package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class FullHouse extends Daddy {

	/**
	 *  set amount of points received for filling category 
	 */
	private int points;
	/**
	 * tracks if category is satisfied given the hand 
	 */
	private boolean satisfied;

	public FullHouse(String name, int points) {
		this.name = name;
		this.points = points;
	}

	/**
	 * Scoring category for a generalized full house. A hand with N dice satisfies
	 * this category only in the following cases: If N is even, there are two
	 * different values, each occurring exactly N/2 times. If N is odd, there are
	 * two different values, one of them occurring N/2 times and the other occurring
	 * N/2 + 1 times. For a hand that satisfies this category, the score is a fixed
	 * value specified in the constructor; otherwise, the score is zero.
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {
		score = 0;
		satisfied = true;
		int[] sample = hand.getAllValues();
		if (sample.length % 2 == 0) {
			for (int i = 0; i < (sample.length / 2) - 1; i++) {
				if (sample[i] != sample[i + 1]) {
					return false;
				}
			}
			for (int j = sample.length / 2; j < sample.length - 1; j++) {
				if (sample[j] != sample[j + 1]) {
					return false;

				}
			}
			score = points;
		}
		if (sample.length % 2 == 1) {
			if (sample[sample.length / 2] != sample[(sample.length / 2) - 1]) {
				for (int i = 0; i < (sample.length / 2 - 1); i++) {
					if (sample[i] != sample[i + 1]) {
						satisfied = false;
					}
				}
				for (int j = sample.length / 2; j < sample.length - 1; j++) {
					if (sample[j] != sample[j + 1]) {
						satisfied = false;
					}
				}
			}

			else {
				for (int k = 0; k < sample.length / 2; k++) {
					if (sample[k] != sample[k + 1]) {
						satisfied = false;
					}
				}
				for (int m = sample.length / 2 + 1; m < sample.length - 1; m++) {
					if (sample[m] != sample[m + 1]) {
						satisfied = false;
					}
				}
			}
		}
		if (satisfied == true) {
			score = points;
		}
		return satisfied;
	}
}
