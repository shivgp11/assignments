package hw3;
/**
 * Shiv Patel
 */


import static api.CellState.*;
import static api.Direction.*;
import api.*;
import java.util.ArrayList;

/**
 * Basic game state and operations for a simplified version of the video game
 * "Quell".
 */
public class CS227Quell {
	/**
	 * variable representing the number of pearls eaten aka the score
	 */
	private int score;

	/**
	 * variable that tracks the amount of moves made by the player
	 */
	private int moves;

	/**
	 * Two-dimensional array of Cell objects representing the grid on which the game
	 * is played.
	 */
	private Cell[][] grid;

	/**
	 * Instance of GameSupport to be used in the move() algorithm.
	 */
	private GameSupport support;

	/**
	 * Constructs a game from the given string description. The conventions for
	 * representing cell states as characters can be found in
	 * <code>StringUtil</code>.
	 * 
	 * @param init    string array describing initial cell states
	 * @param support GameSupport instance to use in the <code>move</code> method
	 */
	public CS227Quell(String[] init, GameSupport support) {
		grid = StringUtil.createFromStringArray(init);
		this.support = support;

		// TODO - any other initialization you need
	}

	/**
	 * Returns the number of columns in the grid.
	 * 
	 * @return width of the grid
	 */
	public int getColumns() {
		return grid[0].length;
	}

	/**
	 * Returns the number of rows in the grid.
	 * 
	 * @return height of the grid
	 */
	public int getRows() {
		return grid.length;
	}

	/**
	 * Returns the cell at the given row and column.
	 * 
	 * @param row row index for the cell
	 * @param col column index for the cell
	 * @return cell at given row and column
	 */
	public Cell getCell(int row, int col) {
		return grid[row][col];
	}

	/**
	 * Returns true if the game is over, false otherwise. The game ends when all
	 * pearls are removed from the grid or when the player lands on a cell with
	 * spikes.
	 * 
	 * @return true if the game is over, false otherwise
	 */
	public boolean isOver() {

		int i = getCurrentRow();
		int j = getCurrentColumn();

		if (spikesAreDeadly(grid[i][j].getState(), UP) || spikesAreDeadly(grid[i][j].getState(), DOWN)
				|| spikesAreDeadly(grid[i][j].getState(), LEFT) || spikesAreDeadly(grid[i][j].getState(), RIGHT)
				|| grid[i][j].getState() == SPIKES_ALL || countPearls() == 0) {
			return true;
		}
		return false;
	}

	/**
	 * Performs a move along a cell sequence in the given direction, updating the
	 * score, the move count, and all affected cells in the grid. The method returns
	 * an array of Descriptor objects representing the cells in original cell
	 * sequence before modification, with their <code>movedTo</code> and
	 * <code>disappeared</code> status set to indicate the cells' new locations
	 * after modification.
	 * 
	 * @param dir direction of the move
	 * @return array of Descriptor objects describing modified cells
	 */
	public Descriptor[] move(Direction dir) {
		int initialPearls = 0;
		int finalPearls = 0;
		Cell[] cells = getCellSequence(dir);
		for(int i = 0; i < cells.length; i++)
		{
			if (cells[i].getState() == PEARL) {
				initialPearls++;
			}
		}
		Descriptor[] descriptors = new Descriptor[cells.length];
		for (int i = 0; i < cells.length; ++i) {
			descriptors[i] = new Descriptor(cells[i], i);
		}
		support.shiftMovableBlocks(cells, descriptors);
		support.shiftPlayer(cells, descriptors, dir);
		for(int i = 0; i < cells.length; i++)
		{
			if (cells[i].getState() == PEARL) {
				finalPearls++;
			}
		}
		setCellSequence(cells, dir);
		moves++;
		score = initialPearls - finalPearls;
		return descriptors;
	}

	/**
	 * Returns the row index for the player's current location.
	 * 
	 * @return
	 */
	public int getCurrentRow() {
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[i].length; j++) {
				if (grid[i][j].isPlayerPresent() == true) {
					return i;
				}
			}
		}
		return 0;
	}

	/**
	 * Returns the column index for the player's current location.
	 */
	public int getCurrentColumn() {
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[i].length; j++) {
				if (grid[i][j].isPlayerPresent() == true) {
					return j;
				}
			}
		}
		return 0;
	}

	/**
	 * Returns true if the game is over and the player did not die on spikes.
	 */
	public boolean won() {

		int i = getCurrentRow();
		int j = getCurrentColumn();

		if (spikesAreDeadly(grid[i][j].getState(), UP) || spikesAreDeadly(grid[i][j].getState(), DOWN)
				|| spikesAreDeadly(grid[i][j].getState(), LEFT) || spikesAreDeadly(grid[i][j].getState(), RIGHT)
				|| grid[i][j].getState() == SPIKES_ALL) {
			return false;
		}
		return countPearls() == 0;
	}

	/**
	 * Returns the current number of moves made in this game.
	 */
	public int getMoves() {
		return moves;
	}

	/**
	 * Returns the current score (number of pearls disappeared) for this game.
	 */
	public int getScore() {
		return score;
	}

	/**
	 * Finds a valid cell sequence in the given direction starting with the player's
	 * current position and ending with a boundary cell as defined by the method
	 * CellState.isBoundary. The actual cell locations are obtained by following
	 * getNextRow and getNextColumn in the given direction, and the sequence ends
	 * when a boundary cell is found. A boundary cell is defined by the
	 * CellState.isBoundary and is different depending on whether a movable block
	 * has been encountered so far in the cell sequence (the player can move through
	 * open gates and portals, but the movable blocks cannot). It can be assumed
	 * that there will eventually be a boundary cell (i.e., the grid has no infinite
	 * loops). The first element of the returned array is the cell containing the
	 * player, and the last element of the array is the boundary cell. This method
	 * does not modify the grid or any aspect of the game state.
	 */
	public Cell[] getCellSequence(Direction dir) {

		ArrayList<Cell> seq = new ArrayList<Cell>();
		int row = getCurrentRow();
		int column = getCurrentColumn();
		int tempRow = 0;
		int tempColumn = 0;
		boolean portals = false;
		boolean barrier = false;

		while (!isBoundary(grid[row][column].getState(), barrier)) {

			seq.add(grid[row][column]);

			if (grid[row][column].getState() == PORTAL && !portals) {
				/*
				 * since portals is now true, the next row and column won't use the offsets
				 * because it will go straight to the else statement.
				 */
				portals = true;

				tempRow = getNextRow(row, column, dir, true);
				tempColumn = getNextColumn(row, column, dir, true);
				row = tempRow;
				column = tempColumn;
			} else {
				portals = false;
				tempRow = getNextRow(row, column, dir, false);
				tempColumn = getNextColumn(row, column, dir, false);
				row = tempRow;
				column = tempColumn;
			}
			/*
			 * checks if the new cell is movable. if so, then portals and gates are now
			 * boundaries
			 */
			if (isMovable(grid[row][column].getState())) {
				barrier = true;
			}
		}
		seq.add(grid[row][column]);
		Cell arr[] = new Cell[seq.size()];
		for (int i = 0; i < arr.length; i++) {
			arr[i] = seq.get(i);
		}
		return arr;
	}

	/**
	 * Sets the given cell sequence and updates the player position. This method
	 * effectively retraces the steps for creating a cell sequence in the given
	 * direction, starting with the player's current position, and updates the grid
	 * with the new cells. Exactly one cell in the given sequence must have the
	 * condition isPlayerPresent true. The given cell sequence can be assumed to be
	 * structurally consistent with the existing grid, e.g., no portal or wall cells
	 * are moved.
	 */
	public void setCellSequence(Cell[] cells, Direction dir) {
		ArrayList<Cell> seq = new ArrayList<Cell>();
		int row = getCurrentRow();
		int column = getCurrentColumn();
		int tempRow = 0;
		int tempColumn = 0;
		boolean portals = false;
		boolean barrier = false;
		int i = 0;
		while (!isBoundary(grid[row][column].getState(), barrier)) {

			grid[row][column] = cells[i];

			if (grid[row][column].getState() == PORTAL && !portals) {
				/*
				 * since portals is now true, the next row and column won't use the offsets
				 * because it will go straight to the else statement.
				 */
				portals = true;

				tempRow = getNextRow(row, column, dir, true);
				tempColumn = getNextColumn(row, column, dir, true);
				row = tempRow;
				column = tempColumn;
			} else {
				portals = false;
				tempRow = getNextRow(row, column, dir, false);
				tempColumn = getNextColumn(row, column, dir, false);
				row = tempRow;
				column = tempColumn;
			}
			/*
			 * checks if the new cell is movable. if so, then portals and gates are now
			 * boundaries
			 */
			if (isMovable(grid[row][column].getState())) {
				barrier = true;
			}
			i++;
		}

	}

	/**
	 * Helper method returns the next row for a cell sequence in the given
	 * direction, possibly wrapping around. If the flag doPortalJump is true, then
	 * the next row will be obtained by adding the cell's row offset. (Normally the
	 * caller will set this flag to true when first landing on a portal, but to
	 * false for the second portal of the pair.)
	 */
	public int getNextRow(int row, int col, Direction dir, boolean doPortalJump) {

		if (doPortalJump == true) {
			return row + grid[row][col].getRowOffset();
		}
		if (dir == UP) {
			return ((row - 1) + getRows()) % getRows();
		} else if (dir == DOWN) {
			return (row + 1) % getRows();
		}
//			
		return row;
	}

	/**
	 * Helper method returns the next column for a cell sequence in the given
	 * direction, possibly wrapping around. If the flag doPortalJump is true, then
	 * the next column will be obtained by adding the cell's column offset.
	 * (Normally the caller will set this flag to true when first landing on a
	 * portal, but to false for the second portal of the pair.)
	 */
	public int getNextColumn(int row, int col, Direction dir, boolean doPortalJump) {

		if (doPortalJump == true) {
			return col + grid[row][col].getColumnOffset();
		}
		if (dir == LEFT) {
			return ((col - 1) + getColumns()) % getColumns();
		} else if (dir == RIGHT) {
			return (col + 1) % getColumns();
		}

		return col;

	}

	/**
	 * Returns the number of pearls left in the grid.
	 */
	public int countPearls() {
		int pearls = 0;
		for (int i = 0; i < grid.length; i++) {
			for (int j = 0; j < grid[i].length; j++) {
				if (grid[i][j].getState() == PEARL) {
					pearls++;
				}
			}
		}
		return pearls;
	}
	// TODO - everything else
}
