1. Typing make builds the executables check and advance.

2. Reads from filename passed as argument.

3. Reads in switches, if -x output as human readable format, if -o output to corresponding output file,
   if -m should be followed by a number that is read as number of moves, else moves are unlimited.

4. Outputs to standard output if -o is not read, as game configuration output or as human readable format if -x is read.

5. Firsts checks if format of moves in file is valid, and if valid then checks if the moves themselves are valid. If they
   are valid, the appropriate moves of cards through linked list movements either from waste to table column or table column
   to table column or table column to foundations or waste to foundations or stock to waste or when cards are reset from the
   waste back to the stock.

6. If moves are invalid in either format read or if it's an invalid move, then appropriate error is displayed to
   standard error.
