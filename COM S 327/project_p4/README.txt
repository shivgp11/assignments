1. Both -f and -s switches works. Reads from filename passed as argument if -f, and takes in the inputted random seed 
   if -s. 

2. Typing make builds the executables check and advance and game.

3. Tableau, Foundations, Waste top, Hotkeys display.

4. Pressing 'q' exits cleanly.

5. Gameplay, moving cards from waste to Foundations, waste to column, column to column, column to waste next card from stock 
   to waste (depending on turn 1 or 3) and resetting all the cards from waste to stock.

6. Turning over 3 cards displays the top 3 waste cards

7. Limited stock resets where stock resets are disallowed when the limit is reached.

8. Pressing 'r' restarts the same game from the beginning. Partially works. When restarting most of the elements reverts back 
   to the original position but some extra cards are added on the table. Reason is unknown. Also restarting more than once
   throws a segmentation fault.