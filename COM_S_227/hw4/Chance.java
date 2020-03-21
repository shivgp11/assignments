package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class Chance extends Daddy {

	public Chance(String name) {
		this.name = name;
	}

	/**
	 * Scoring category that is satisfied by any hand. The score is the sum of all
	 * die values.
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {
		score = 0;
		int[] sample = hand.getAllValues();
		for (int i = 0; i < sample.length; i++) {
			score += sample[i];
		}
		return true;
	}

}
