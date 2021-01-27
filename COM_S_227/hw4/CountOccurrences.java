package hw4;
/**
 * @author Shiv
 */
import hw4.api.Die;

public class CountOccurrences extends Daddy {

	/**
	 * the specified number that is being counted
	 */
	private int number;

	public CountOccurrences(String name, int number) {
		this.name = name;
		this.number = number;
	}

	/**
	 * Scoring category that is based on counting occurrences of a particular target
	 * value (specified in the constructor). This category is satisfied by any hand.
	 * The score is the sum of just the die values that match the target value.
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {

		score = 0;
		int[] sample = hand.getAllValues();
		for (int i = 0; i < sample.length; i++) {
			if (sample[i] == number) {
				score += number;
			}
		}
		return true;
	}

}
