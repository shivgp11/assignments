package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class AllButTwoOfAKind extends Daddy {
	/**
	 * keeps track of whether or not the scoring category is satisfied
	 * 
	 */
	private boolean satisfied;

	public AllButTwoOfAKind(String name) {
		this.name = name;
	}

	/**
	 * Scoring category for (N-2) of a kind. A hand with N dice satisfies this
	 * category only if at least N - 2 of the values are the same. For a hand that
	 * satisfies this category, the score the sum of all die values; otherwise the
	 * score is zero.
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {
		score = 0;
		satisfied = false;
		int count = 0;
		int[] sample = hand.getAllValues();
		if (sample.length > 4) {

			for (int i = 0; i < sample.length - 2; i++) {
				if (sample[i] == sample[i + 1] && sample[i + 1] == sample[i + 2]) {
					count++;
				}
			}
			if (count >= sample.length - 4) {
				satisfied = true;
				for (int i = 0; i < sample.length; i++) {
					score += sample[i];
				}
			}
		} else if (sample.length == 4 && (sample[0] == sample[1] || sample[1] == sample[2] || sample[2] == sample[3])) {
			satisfied = true;
			for (int i = 0; i < sample.length; i++) {
				score += sample[i];
			}
		} else {
			satisfied = true;
			for (int i = 0; i < sample.length; i++) {
				score += sample[i];
			}
		}
		return satisfied;
	}

}
