package hw4;
/**
 * 
 * @author Shiv
 *
 */
public class AllPrimes extends Daddy {
	/**
	 * keeps track of whether or not the category is satisfied
	 */
	private boolean satisfied;

	public AllPrimes() {
		name = "AllPrimes";
	}

	/**
	 * Scoring category for all primes. A hand satisfies this category only if all
	 * die values are prime numbers. For a hand that satisfies this category, the
	 * score the sum of all die values; otherwise the score is zero. The display
	 * name for this category is always the exact string "All Primes".
	 */
	@Override
	public boolean isSatisfiedBy(Hand hand) {
		score = 0;
		int count = 0;
		int[] sample = hand.getAllValues();
		for (int i = 0; i < sample.length; i++) {
			if (isPrime(sample[i])) {
				count++;
			}
		}
		if (count == sample.length) {
			satisfied = true;
			for (int j = 0; j < sample.length; j++) {
				score += sample[j];
			}
		}
		return satisfied;
	}

	/**
	 * helper method for determining if a given integer is a prime number
	 * @param n the given number
	 * @return true of false
	 */
	private boolean isPrime(int n) {
		for (int i = 2; i <= n / 2; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
}
