import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class pa2 {

	public static void main(String[] args) throws FileNotFoundException {
		File f = new File(args[0]);
		Scanner sc = new Scanner(f); //replace name of file with args[0] when done
		int linecount= 0;
		String testline = "";
        ArrayList<String> lines = new ArrayList<String>();
       while(sc.hasNext())
		{
			testline = sc.next(); //takes string of instructions
			linecount = testline.length()/32; //sees how many total instructions
		}
		int j = 0;
		for(int i = 0; i < linecount; i++)
		{
			String instruction = testline.substring(j,j+32);//takes each instruction
			lines.add(instruction);//and adds it to the list
			j += 32;
		}

        String[] output = new String[lines.size()];
        sc.close();
		//labels[i] = 0 if line i needs a preceding label
		boolean[] labels = new boolean[linecount];
		sc.close();
		//sc = new Scanner(f);
		//int labelcount = 1;
        for(int i = 0; i < lines.size(); i++) {
            String line = lines.get(i);
            String legv8 = "";
            //Shiv
            if (line.substring(0, 11).equals("10001011000")) {
				String op = "ADD ";
				String rm = line.substring(11, 16);
				String shamt = line.substring(16, 22);
				String rn = line.substring(22, 27);
				String rd = line.substring(27, 32);
				legv8 += op;
				legv8 += "X" + Integer.parseUnsignedInt(rd, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rn, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rm, 2);
				output[i] = legv8;
				// System.out.println(legv8);
			} else if (line.substring(0, 10).equals("1001000100")) {
				String op = "ADDI ";
				String immediate = line.substring(10, 22);
				boolean isnegative = false;
				if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
				String rn = line.substring(22, 27);
				String rd = line.substring(27, 32);
				legv8 += op;
				legv8 += "X" + Integer.parseUnsignedInt(rd, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rn, 2) + ", ";
				legv8 += "#";
				if(isnegative)
				{
					legv8 += "-";
				}
				legv8 += "" + Integer.parseUnsignedInt(immediate, 2);
				output[i] = legv8;
				// System.out.println(legv8);
			} else if (line.substring(0, 11).equals("10001010000")) {
				String op = "AND ";
				String rm = line.substring(11, 16);
				String shamt = line.substring(16, 22);
				String rn = line.substring(22, 27);
				String rd = line.substring(27, 32);
				legv8 += op;
				legv8 += "X" + Integer.parseUnsignedInt(rd, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rn, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rm, 2);
				output[i] = legv8;
				// System.out.println(legv8);
			} else if (line.substring(0, 10).equals("1001001000")) {
				String op = "ANDI ";
				String immediate = line.substring(10, 22);
				boolean isnegative = false;
				if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
				String rn = line.substring(22, 27);
				String rd = line.substring(27, 32);
				legv8 += op;
				legv8 += "X" + Integer.parseUnsignedInt(rd, 2) + ", ";
				legv8 += "X" + Integer.parseUnsignedInt(rn, 2) + ", ";
				legv8 += "#";
				if(isnegative)
				{
					legv8 += "-";
				}
				legv8 += Integer.parseUnsignedInt(immediate, 2);
				output[i] = legv8;
				// System.out.println(legv8);
			} 
			else if (line.substring(0, 6).equals("000101")) {
				output[i] = handleBranch("B ", line.substring(6, 32), labels, i);
			}
			else if (line.substring(0, 8).equals("01010100")) {
				String op = "B.";
				String baddress = line.substring(8, 27);
				String rt = line.substring(27, 32);
				int decimal = Integer.parseInt(rt, 2);
				String hex = Integer.toString(decimal, 16);
				switch (hex) {
				case "0":
					op += "EQ";
					break;
				case "1":
					op += "NE";
					break;
				case "2":
					op += "HS";
					break;
				case "3":
					op += "LO";
					break;
				case "4":
					op += "MI";
					break;
				case "5":
					op += "PL";
					break;
				case "6":
					op += "VS";
					break;
				case "7":
					op += "VC";
					break;
				case "8":
					op += "HI";
					break;
				case "9":
					op += "LS";
					break;
				case "a":
					op += "GE";
					break;
				case "b":
					op += "LT";
					break;
				case "c":
					op += "GT";
					break;
				case "d":
					op += "LE";
					break;
				}
				op += " ";
				output[i] = handleBranch(op, baddress, labels, i);
			}
            //Carter
            //BL - B TYPE
			else if(line.substring(0, 6).equals("100101"))
            {
				output[i] = handleBranch("BL ", line.substring(6, 32), labels, i);
            }
            //BR - R TYPE
            else if(line.substring(0, 11).equals("11010110000"))
            {
            	String address = line.substring(22, 27);
                int rn = Integer.parseInt(line.substring(22, 27), 2); //branch target

                output[i] = ("BR X" + rn);
                //output[i] = handleBranch("BR X" + rn + " ", address, labels, i);
            }
            //CBNZ - CB TYPE
            else if(line.substring(0, 8).equals("10110101"))
            {
                String address = line.substring(8, 27);

                int rt = Integer.parseInt(line.substring(27, 32), 2);

                output[i] = handleBranch("CBNZ X" + rt + ", ", address, labels, i);
            }
            //CBZ - CB TYPE
            else if(line.substring(0, 8).equals("10110100"))
            {
                String address = line.substring(8, 27);

                int rt = Integer.parseInt(line.substring(27, 32), 2);

                output[i] = handleBranch("CBZ X" + rt + ", ", address, labels, i);
            }
            //EOR - R TYPE
            else if(line.substring(0, 11).equals("11001010000"))
            {
                int rm = Integer.parseInt(line.substring(11, 16), 2);
                int shamt = Integer.parseInt(line.substring(16, 22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);

                output[i] = ("EOR X" + rd + ", X" + rn + ", X" + rm);
            }
            //EORI - I TYPE
            else if(line.substring(0, 10).equals("1101001000"))
            {
                String immediate = line.substring(10, 22);
                boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}

                int imm = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                
                legv8 = "EORI X" + rd + ", X" + rn + ", #";
                if(isnegative)
                {
                	legv8 += "-";
                }

                output[i] = (legv8 + imm);
            }
            //LDUR - D TYPE
            else if(line.substring(0, 11).equals("11111000010"))
            {
                String address = line.substring(11, 20);
                boolean isnegative = false;
                if(address.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(address);
					address = findTwoscomplement(str);
					isnegative = true;
				}

                int add = Integer.parseInt(address, 2);
                int op2 = Integer.parseInt(line.substring(20, 22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rt = Integer.parseInt(line.substring(27, 32), 2);
                legv8 = "LDUR X" + rt + ", [X" + rn + ", #";
                if(isnegative)
                {
                	legv8 += "-";
                }
                output[i] = (legv8 + add + "]");
            }
            //Zaid
            //LSL
            else if(line.substring(0, 11).equals("11010011011"))
			{
			   String immediate = (line.substring(16,22));
				boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
         
				
			    //R type: 11 opcode, 5 RM, 6 Shamt, 5 Rn, 5 Rd
                int rm = Integer.parseInt(line.substring(11,16), 2);
                int shamt = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                if(isnegative)
                {
                	 output[i] = ("LSL X" + rd + ", X" + rn + ", #-" + shamt); 
                }
                else {
                	output[i] = ("LSL X" + rd + ", X" + rn + ", #" + shamt);        
                }
			}
			
			//LSR
			else if(line.substring(0, 11).equals("11010011010"))
			{
			String immediate = (line.substring(16,22));
				boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
       
			    //R type: 11 opcode, 5 RM, 6 Shamt, 5 Rn, 5 Rd
                int rm = Integer.parseInt(line.substring(11,16), 2);
                int shamt = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                if(isnegative)
                {
                	 output[i] = ("LSR X" + rd + ", X" + rn + ", #-" + shamt); 
                }
                else {
                	output[i] = ("LSR X" + rd + ", X" + rn + ", #" + shamt);        
                }


			}
			
			//ORR
			if(line.substring(0, 11).equals("10101010000"))
			{
			    //R type: 11 opcode, 5 RM, 6 Shamt, 5 Rn, 5 Rd
                int rm = Integer.parseInt(line.substring(11,16), 2);
                int shamt = Integer.parseInt(line.substring(16,22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                output[i] = ("ORR X" + rd + ", X" + rn + ", X" + rm);

			}
			
			//ORRI
			if(line.substring(0, 10).equals("1011001000"))
			{
				//I type: 10 opcode, 12 ALUimmediate, 5 Rn, 5 Rd
				String immediate = line.substring(10, 22);
				boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
                int imm = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                legv8 = "ORRI X" + rd + ", X" + rn + ", #";
                if(isnegative)
                {
                	legv8 += "-";
                }
                output[i] = (legv8 + imm);
             

			}
			
			//STUR
			else if(line.substring(0, 11).equals("11111000000"))
			{
			    String immediate = (line.substring(11,20));
				boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}              
			    //D type: 11 opcode, 9 DT_Address, 2 op, 5 Rn, 5 Rd
                int DT_addr = Integer.parseInt(immediate, 2);
                int op = Integer.parseInt(line.substring(20,22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rt = Integer.parseInt(line.substring(27, 32), 2);
                if(isnegative)
                {
                	output[i] = ("STUR X" + rt + ", [X" + rn + ", #-" + DT_addr + "]");
                }
                else
                {
                	output[i] = ("STUR X" + rt + ", [X" + rn + ", #" + DT_addr + "]");
                }


			} 

			
			//SUB
			if(line.substring(0, 11).equals("11001011000"))
			{
			    //R type: 11 opcode, 5 RM, 6 Shamt, 5 Rn, 5 Rd
                int rm = Integer.parseInt(line.substring(11,16), 2);
                int shamt = Integer.parseInt(line.substring(16,22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                output[i] = ("SUB X" + rd + ", X" + rn + ", X" + rm);

			}
			
			//SUBI
			if(line.substring(0, 10).equals("1101000100"))
			{
			    //I type: 10 opcode, 12 ALUimmediate, 5 Rn, 5 Rd
				String immediate = line.substring(10, 22);
				boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
                int imm = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                legv8 = "SUBI X" + rd + ", X" + rn + ", #";
                if(isnegative)
                {
                	legv8 += "-";
                }
                output[i] = (legv8 + imm);

			}

			//Alex
            //SUBIS
			else if(line.substring(0, 10).equals("1111000100"))
            {
                //I type: 10 opcode, 12 ALU_immediate, 5 Rn, 5 Rd
                String immediate = line.substring(10, 22);
                boolean isnegative = false;
                if(immediate.charAt(0) == '1')
				{
					StringBuffer str = new StringBuffer(immediate);
					immediate = findTwoscomplement(str);
					isnegative = true;
				}
                int imm = Integer.parseInt(immediate, 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                legv8 = "SUBIS X" + rd + ", X" + rn + ", #";
                if(isnegative)
                {
                	legv8 += "-";
                }
                output[i] = (legv8 + imm);
            }
            //SUBS
            else if(line.substring(0, 11).equals("11101011000"))
            {
                //R type: 11 opcode, 5 rm, 6 shamt, 5 rn, 5 rd
                int rm = Integer.parseInt(line.substring(11, 16), 2);
                int shamt = Integer.parseInt(line.substring(16, 22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                output[i] = ("SUBS X" + rd + ", X" + rn + ", X" + rm);
            }
            //MUL
            else if(line.substring(0, 11).equals("10011011000"))
            {
            	//R type: 11 opcode, 5 rm, 6 shamt, 5 rn, 5 rd
                int rm = Integer.parseInt(line.substring(11, 16), 2);
                int shamt = Integer.parseInt(line.substring(16, 22), 2);
                int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                output[i] = ("MUL X" + rd + ", X" + rn + ", X" + rm);
            }
            //PRNT
            else if(line.substring(0, 11).equals("11111111101"))
            {
            	//R type: 11 opcode, 5 rm, 6 shamt, 5 rn, 5 rd
                //int rm = Integer.parseInt(line.substring(11, 16), 2);
                //int shamt = Integer.parseInt(line.substring(16, 22), 2);
                //int rn = Integer.parseInt(line.substring(22, 27), 2);
                int rd = Integer.parseInt(line.substring(27, 32), 2);
                output[i] = ("PRNT X" + rd);
            }
            //PRNL
            else if(line.substring(0, 11).equals("11111111100"))
            {
            	output[i] = ("PRNL");
            }
            //DUMP
            else if(line.substring(0, 11).equals("11111111110"))
            {
            	output[i] = ("DUMP");
            }
            //HALT
            else if(line.substring(0, 11).equals("11111111111"))
            {
            	output[i] = ("HALT");
            }
        }
        for(int i = 0; i < output.length; i++)
        {
        	if(labels[i])
        	{
        		System.out.println("label" + (i+1) + ":");
        	}
        	System.out.println(output[i]);
        }
        sc.close();
	}
	
		public static String handleBranch(String op, String baddress, boolean[] labels, int i)
		{
			String legv8 = "";
			String label = "";
			int jump = 0;
			//System.out.println(baddress);
			if (baddress.substring(0, 1).equals("1")) {
				StringBuffer str = new StringBuffer(baddress);
				String twoscomp = findTwoscomplement(str);
				jump = Integer.parseUnsignedInt(twoscomp, 2);
				jump *= -1;
				int labelnum = i + jump + 1;
				label = "label" + labelnum + "";
				legv8 += op;
				legv8 += label;
				labels[i + jump] = true;
				return legv8;
			} else {
				jump = Integer.parseUnsignedInt(baddress, 2);
				int labelnum = i + jump + 1;
				label = "label" + labelnum + "";
				legv8 += op;
				legv8 += label;
				//System.out.println("i: " + i + " jump: " + jump);
				labels[i + jump] = true;
				return legv8;
			}
		}

    	static String findTwoscomplement(StringBuffer str) {
    		int n = str.length();

    		int i;
    		for (i = n - 1; i >= 0; i--)
    			if (str.charAt(i) == '1')
    				break;

    		if (i == -1)
    			return "1" + str;

    		for (int k = i - 1; k >= 0; k--) {
    			if (str.charAt(k) == '1')
    				str.replace(k, k + 1, "0");
    			else
    				str.replace(k, k + 1, "1");
    		}

    		return str.toString();
    	}

}
