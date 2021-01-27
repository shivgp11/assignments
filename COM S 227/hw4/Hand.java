package hw4;
/**
 * @author Shiv
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import hw4.api.Die;

/**
 * This class represents values of a group of dice for a dice game such as
 * Yahtzee in which multiple rolls per turn are allowed. The number of faces on
 * the dice, the number of dice in the Hand, and the maximum number of rolls are
 * configurable via the constructor. At any time some of the dice may be
 * <em>available</em> to be rolled, and the other dice are <em>fixed</em>. Calls
 * to the <code>roll()</code> method roll the available dice only. After the
 * maximum number of rolls, all dice are automatically fixed; before that, the
 * client can select which dice to "keep" (change from available to fixed) and
 * which dice to "free" (change from fixed to available).
 * <p>
 * Note that valid die values range from 1 through the given
 * <code>maxValue</code>.
 */
public class Hand {
	/**
	 * Constructs a new Hand in which each die initially has the value 1.
	 * 
	 * @param numDice  number of dice in this group
	 * @param maxValue largest possible die value, where values range from 1 through
	 *                 <code>maxValue</code>
	 * @param maxRolls maximum number of total rolls
	 */
	/**
	 * an array of die that that represents the actual dice the player will have and what we're going to work witj
	 */
	private Die[] dice;
	/**
	 * the number of dice set for the round
	 */
	private int numberOfDice;
	/**
	 * the number of sides the die have for the game aka the max number of sides
	 */
	private int maximumValue;
	/**
	 * the maximum rolls a player is aloud for the given round
	 */
	private int maximumRolls;
	/**
	 * keeps track of the number of rolls the player's made so far
	 */
	private int rolls;

	public Hand(int numDice, int maxValue, int maxRolls) {
		numberOfDice = numDice;
		maximumValue = maxValue;
		maximumRolls = maxRolls;
		rolls = 0;
		dice = new Die[numDice];
		for (int i = 0; i < dice.length; i++) {
			dice[i] = new Die(1, maxValue);
		}

	}

	/**
	 * Constructs a new Hand in which each die initially has the value given by the
	 * <code>initialValues</code> array. If the length of the array is greater than
	 * the number of dice, the extra values are ignored. If the length of the array
	 * is smaller than the number of dice, remaining dice will be initialized to the
	 * value 1.
	 * <p>
	 * This version of the constructor is primarily intended for testing.
	 * 
	 * @param numDice       number of dice in this hand
	 * @param maxValue      largest possible die value, where values range from 1
	 *                      through <code>maxValue</code>
	 * @param maxRolls      maximum number of total rolls
	 * @param initialValues initial values for the dice
	 */
	public Hand(int numDice, int maxValue, int maxRolls, int[] initialValues) {
		numberOfDice = numDice;
		maximumValue = maxValue;
		maximumRolls = maxRolls;
		rolls = 0;
		dice = new Die[numDice];
		if (dice.length < initialValues.length || dice.length == initialValues.length) {
			for (int i = 0; i < dice.length; i++) {
				dice[i] = new Die(initialValues[i], maxValue);
			}
		} else if (dice.length > initialValues.length) {
			for (int i = 0; i < initialValues.length; i++) {
				dice[i] = new Die(initialValues[i], maxValue);
				for (int j = i + 1; j < dice.length; j++) {
					dice[j] = new Die(1, maxValue);
				}
			}
		}
	}

	/**
	 * Returns the number of dice in this hand.
	 * 
	 * @return number of dice in this hand
	 */
	public int getNumDice() {
		return numberOfDice;
	}

	/**
	 * Returns the maximum die value in this hand. Valid values start at 1.
	 * 
	 * @return maximum die value
	 */
	public int getMaxValue() {
		return maximumValue;
	}

	/**
	 * Rolls all available dice using the given random number generator. If the
	 * number of rolls has reached the maximum, all dice are marked as fixed.
	 * 
	 * @param rand random number generator to be used for rolling dice
	 */
	public void roll(Random rand) {
		if (rolls < maximumRolls) {
			for (int i = 0; i < dice.length; i++) {
				if (dice[i].isAvailable() == true) {
					dice[i] = new Die(rand.nextInt(maximumValue) + 1, maximumValue);
				}
			}
			rolls++;
		}
		if (rolls == maximumRolls) {

			for (int j = 0; j < dice.length; j++) {
				dice[j].setAvailable(false);
			}
		}
	}

	/**
	 * Selects a single die value to be changed from the available dice to the fixed
	 * dice. If there are multiple available dice with the given value, only one is
	 * changed to be fixed. Has no effect if the given value is not among the values
	 * in the available dice. Has no effect if the number of rolls has reached the
	 * maximum.
	 * 
	 * @param value die value to be changed from available to fixed
	 */
	public void keep(int value) {
		if (rolls < maximumRolls) {
			for (int i = 0; i < dice.length; i++) {
				if (dice[i].value() == value) {
					dice[i].setAvailable(false);
					break;
				}
			}
			DieComparator comp = new DieComparator();
			Arrays.sort(dice, comp);
		}

	}

	/**
	 * Selects a die value to be moved from the fixed dice to the available dice
	 * (i.e. so it will be re-rolled in the next call to <code>roll()</code>). If
	 * there are multiple fixed dice with the given value, only one is changed be
	 * available. Has no effect if the given value is not among the values in the
	 * fixed dice. Has no effect if the number of rolls has reached the maximum.
	 * 
	 * @param value die value to be moved
	 */
	public void free(int value) {
		if (rolls < maximumRolls) {
			for (int i = 0; i < dice.length; i++) {
				if (dice[i].value() == value && dice[i].isAvailable() == false)  {
					dice[i].setAvailable(true);
					break;
				}
			}
			DieComparator comp = new DieComparator();
			Arrays.sort(dice, comp);
		}

	}

	/**
	 * Causes all die values to be changed from available to fixed. Has no effect if
	 * the number of rolls has reached the maximum.
	 */
	public void keepAll() {
		for (int i = 0; i < dice.length; i++) {
			dice[i].setAvailable(false);
		}
	}

	/**
	 * Causes all die values to be changed from fixed to available. Has no effect if
	 * the number of rolls has reached the maximum.
	 */
	public void freeAll() {
		for (int i = 0; i < dice.length; i++) {
			dice[i].setAvailable(true);
		}
	}

	/**
	 * Determines whether there are any dice available to be rolled in this hand.
	 * 
	 * @return true if there are no available dice, false otherwise
	 */
	public boolean isComplete() {
		for (int i = 0; i < dice.length; i++) {
			if (dice[i].isAvailable() == true) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Returns an array containing just the available dice in this hand, sorted according to DieComparator.
	 * @return    array of the available dice
	 */
	public Die[] getFixedDice() {
		ArrayList<Die> list = new ArrayList<Die>();
		for (int i = 0; i < dice.length; i++) {
			if (dice[i].isAvailable() == false) {
				list.add(dice[i]);
			}
		}
		Die[] arr = new Die[list.size()];
		for (int j = 0; j < list.size(); j++) {
			arr[j] = list.get(j);
		}
		DieComparator comp = new DieComparator();
		Arrays.sort(arr, comp);
		return arr;
	}

	/**
	 * Returns an array containing just the fixed dice in this hand, sorted according to DieComparator.
	 * @return     array of the fixed dice
	 */
	public Die[] getAvailableDice() {
		ArrayList<Die> list = new ArrayList<Die>();
		for (int i = 0; i < dice.length; i++) {
			if (dice[i].isAvailable() == true) {
				list.add(dice[i]);
			}
		}
		Die[] arr = new Die[list.size()];
		for (int j = 0; j < list.size(); j++) {
			arr[j] = list.get(j);
		}
		DieComparator comp = new DieComparator();
		Arrays.sort(arr, comp);
		return arr;
	}

	/**
	 * Returns all die values in this hand, in ascending order.
	 * 
	 * @return all die values in this hand
	 */
	public int[] getAllValues() {
		int[] arr = new int[dice.length];
		for (int i = 0; i < dice.length; i++) {
			arr[i] = dice[i].value();
		}
		Arrays.sort(arr);
		return arr;
	}

	/**
	 * Returns an array of all the dice in this hand.
	 * 
	 * @return array of all dice
	 */
	public Die[] getAllDice() {
		Die[] arr = new Die[dice.length];
		for (int i = 0; i < dice.length; i++) {
			arr[i] = dice[i];
		}
		DieComparator comp = new DieComparator();
		Arrays.sort(arr, comp);
		return arr;
	}

}
