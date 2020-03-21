package hw2;

import static hw2.BallDirection.*;
/**
 * 
 * @author Shiv
 * 
 * This class models the game of tennis and its different scenarios
 *
 */
public class TennisGame {

	private int serverScore;
	private int recieverScore;
	private BallDirection direction;
	private int faults;
	private boolean isHeadedOutOfBounds;

	/**
	 * Constructs a new TennisGame in which both players have zero points and the
	 * ball is initially not in play.
	 */
	public TennisGame() {
		serverScore = 0;
		recieverScore = 0;
		direction = BallDirection.NOT_IN_PLAY;
	}

	/**
	 * Directly sets the scores to the given amounts and sets the ball's status to
	 * NOT_IN_PLAY. Note that this operation may cause the scores to go down, or
	 * result in unrealistic values. This method is intended for testing only.
	 * 
	 * @param newServerScore   new score for the server
	 * @param newReceiverScore new score for the receiver
	 */
	public void setScore(int newServerScore, int newReceiverScore) {
		serverScore = newServerScore;
		recieverScore = newReceiverScore;
		direction = BallDirection.NOT_IN_PLAY;
	}

	/**
	 * Returns the current number of points for the receiver.
	 * 
	 * @return current number of points for the receiver
	 */
	public int getReceiverPoints() {
		return recieverScore;
	}

	/**
	 * Returns the current number of points for the server.
	 * 
	 * @return current number of points for the server
	 */
	public int getServerPoints() {
		return serverScore;
	}

	/**
	 * Returns the current status of the ball (traveling toward the receiver,
	 * traveling toward the server, or not in play).
	 * 
	 * @return current status of the ball
	 */
	public BallDirection getBallStatus() {
		return direction;
	}

	/**
	 * Returns true if the game is over, which occurs when one player has more than
	 * three points AND has a margin of at least two points over the other player.
	 * 
	 * @return true if the game is over, false otherwise
	 */
	public boolean isOver() {
		if (serverScore > 3 && serverScore >= recieverScore + 2) {
			return true;
		} else if (recieverScore > 3 && recieverScore >= serverScore + 2) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Returns true if the game is over and the server has won.
	 * 
	 * @return true if the server has won the game, false otherwise
	 */
	public boolean serverWon() {
		if (serverScore > 3 && serverScore >= recieverScore + 2) {
			return true;

		} else {
			return false;
		}
	}

	/**
	 * Returns true if the game is over and the receiver has won.
	 * 
	 * @return true if the receiver has won the game, false otherwise
	 */
	public boolean receiverWon() {
		if (recieverScore >= 3 && recieverScore >= serverScore + 2) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Simulates the server serving the ball. If the serviceFault parameter is
	 * false, then the ball's status will be TOWARD_RECEIVER. If the serviceFault
	 * parameter is true, the number of faults is incremented, and if the number of
	 * faults reaches two, it is reset to zero and a point is awarded to the
	 * receiver. This method does nothing if the game is over or if the ball status
	 * isn't NOT_IN_PLAY.
	 * 
	 * @param serviceFault serviceFault - true if there is a service fault, false
	 *                     otherwise
	 */
	public void serve(boolean serviceFault) {
		if (isOver() == false && direction == NOT_IN_PLAY) {
			if (serviceFault == false) {
				direction = TOWARD_RECEIVER;
				faults = 0;
			} else {
				faults = faults + 1;
				if (faults == 2) {
					faults = 0;
					recieverScore = recieverScore + 1;
				}
			}
		}
	}

	/**
	 * Simulates a hit of the ball by the player toward whom the ball is currently
	 * moving. If the fault parameter is true, indicates that the hit results in a
	 * fault; then the rally ends with the other player getting a point, and the
	 * ball's status becomes NOT_IN_PLAY. If the fault parameter is false, then the
	 * ball's status just switches direction. The outOfBounds parameter indicates
	 * whether or not the trajectory of the ball would land it out of bounds, if the
	 * other player misses it. (The other player could elect to hit the ball before
	 * it bounces.) This method does nothing if the ball is not in play.
	 * 
	 * @param fault             true if this hit ends the rally
	 * @param headedOutOfBounds true if the hit is not a fault but is on an
	 *                          out-of-bounds trajectory
	 */
	public void hit(boolean fault, boolean headedOutOfBounds) {
		isHeadedOutOfBounds = headedOutOfBounds;

		if (direction == TOWARD_RECEIVER) {
			if (fault == true) {
				serverScore = serverScore + 1;
				direction = NOT_IN_PLAY;
			} else {
				direction = TOWARD_SERVER;
			}
		} else if (direction == TOWARD_SERVER) {
			if (fault == true) {
				recieverScore = recieverScore + 1;
				direction = NOT_IN_PLAY;
			} else {
				direction = TOWARD_RECEIVER;
			}
		}
	}

	/**
	 * Simulates a miss of the ball by the player toward whom the ball is currently
	 * traveling. If the ball is on an out-of-bounds trajectory, that player gets a
	 * point, otherwise the other player gets a point. This method always ends the
	 * rally, i.e., after this method executes, the ball is no longer in play. This
	 * method does nothing if the ball is not in play.
	 */
	public void miss() {
		if (direction == TOWARD_RECEIVER) {
			if (isHeadedOutOfBounds == true) {
				recieverScore = recieverScore + 1;
				direction = NOT_IN_PLAY;
				isHeadedOutOfBounds = false;
			} else {
				serverScore = serverScore + 1;
				direction = NOT_IN_PLAY;
			}
		} else if (direction == TOWARD_SERVER) {
			if (isHeadedOutOfBounds == true) {
				serverScore = serverScore + 1;
				direction = NOT_IN_PLAY;
				isHeadedOutOfBounds = false;
			} else {
				recieverScore = recieverScore + 1;
				direction = NOT_IN_PLAY;
			}
		}
	}

	/**
	 * Returns a string representation of the raw points for each player, in the
	 * form "x-y" where x is the number of points for the server and y is the number
	 * of points for the receiver.
	 * 
	 * @return string representation of the score
	 */
	public java.lang.String getScore() {
		return serverScore + "-" + recieverScore;
	}

	/**
	 * Returns a string representation of the score using the bizarre conventions of
	 * tennis. If the game is over, the returned string is always of the form "x-y",
	 * where x is the server's score and y is the receiver's score. When the game is
	 * not over, the following rules apply: If the server's score is at least 4 and
	 * is exactly one more than the receiver's score, then the string is "advantage
	 * in" If the receiver's score is at least 4 and is exactly one more than the
	 * receiver's score, then the string is "advantage out" If the scores are equal
	 * and at least 3, the string is "deuce" If the scores are equal and the value
	 * is 0, 1, or 2, the string is "love-all", "15-all", or "30-all", respectively
	 * In all other cases, the string is of the form "a-b", where a is a string
	 * describing the server's score and b is a string describing the receiver's
	 * score, using "love" for 0 points, "15" for 1 point, "30" for 2 points, and
	 * "40" for three points.
	 * 
	 * @return string representing the game's current score using tennis conventions
	 */
	public java.lang.String getCallString() {
		if (isOver() == true) {
			return serverScore + "-" + recieverScore;
		} else {
			if (serverScore >= 4 && serverScore == recieverScore + 1) {
				return "advantage in";
			} else if (recieverScore >= 4 && recieverScore == serverScore + 1) {
				return "advantage out";
			} else if (serverScore == recieverScore) {
				if (serverScore >= 3) {
					return "deuce";
				} else if (serverScore == 0) {
					return "love-all";
				} else if (serverScore == 1) {
					return "15-all";
				} else if (serverScore == 2) {
					return "30-all";
				}
			} else if (recieverScore == 0) {
				if (serverScore == 1) {
					return "15-love";
				} else if (serverScore == 2) {
					return "30-love";
				} else if (serverScore == 3) {
					return "40-love";
				}
			} else if (serverScore == 0) {
				if (recieverScore == 1) {
					return "love-15";
				} else if (recieverScore == 2) {
					return "love-30";
				} else if (recieverScore == 3) {
					return "love-40";
				}
			} else if (serverScore == 1 && recieverScore == 2) {
				return "15-30";
			} else if (serverScore == 2 && recieverScore == 1) {
				return "30-15";
			} else if (serverScore == 2 && recieverScore == 3) {
				return "30-40";
			} else if (serverScore == 3 && recieverScore == 2) {
				return "40-30";
			} else if (serverScore == 3 && recieverScore == 1) {
				return "40-15";
			} else if (serverScore == 1 && recieverScore == 3) {
				return "15-40";
			}
		}
		return null;
	}
}
