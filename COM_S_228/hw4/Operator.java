package edu.iastate.cs228.hw4;

/**
 *  
 * @author
 *
 */

/**
 * 
 * This class represents operators '+', '-', '*', '/', '%', '^', '(', and ')'.  
 * Every operator has an input precedence, a stack precedence, and a rank, as specified 
 * in the table below. 
 * 
 *   operator       input precedence        stack precedence       rank
 *   ___________________________________________________________________
 *   - (unary)				6						 5				 0
 *   +  -                   1                        1              -1
 *   *  /  %                2                        2              -1
 *   ^                      4                        3              -1
 *   (                      7                       -1               0
 *   )                      0                        0               0 
 *
 */


import java.lang.Comparable; 

public class Operator implements Comparable<Operator>
{
	public char operator; 	      // operator
	
	private	int inputPrecedence;  // input precedence of operator in the range [0, 6]
	private	int stackPrecedence;  // stack precedence of operator in the range [-1, 5]

	/**
	 * Constructor 
	 * 
	 * ch == '~' if the operator is unary minus. 
	 * 
	 * Refer to the table in Section 2.2 of the project description when setting the values of 
	 * inputPrecedence and stackPrecedence. 
	 * 
	 * @param ch
	 */
	public Operator(char ch) 
	{
		// TODO
	}
	

	/**
	 * Returns 1, 0, -1 if the stackPrecedence of this operator is greater than, equal to, 
	 * or less than the inputPrecedence of the parameter operator op. It's for determining 
	 * whether this operator on the stack should be output before pushing op onto the stack.
	 */
	@Override
	public int compareTo(Operator op)
	{ 	
		// TODO
		return -1;  // TO MODIFY
	} 


	/**
	 * 
	 * @return char Returns the operator character.  
	 */
	public char getOp()   
	{
	   return operator; 
	}
}
