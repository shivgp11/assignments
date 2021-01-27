package pa2;
/**
 * @author Shiv Patel
 * @author Alejandro Delbrey
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class MatrixCuts {

    public static ArrayList<Tuple> widthCut(int [][] m) {

        //List that will be returned
        ArrayList<Tuple> result = new ArrayList<>();

        //Matrix that will store the cost from the subproblems
        int[][] pathCost = new int[m.length][m[0].length];

        //Copy the first row of the given array into the cost matrix
        for (int i = 0; i < pathCost[0].length; i++) {
            pathCost[0][i] = m[0][i];
        }

        //initialize the rest of the cost matrix to a really high number
        for (int i = 1; i < pathCost.length; i++) {
            for (int j = 0; j < pathCost[0].length; j++) {
                pathCost[i][j] = Integer.MAX_VALUE;
            }
        }

        //filling up the min cost array
        for (int i = 0; i < m.length - 1; i++) {
            for (int j = 0; j < m[0].length; j++) {
                if (j == 0) {
                    if (pathCost[i][j] + m[i + 1][j] < pathCost[i + 1][j]) {
                        pathCost[i + 1][j] = pathCost[i][j] + m[i + 1][j];
                    }
                    if (pathCost[i][j] + m[i + 1][j + 1] < pathCost[i + 1][j + 1]) {
                        pathCost[i + 1][j + 1] = pathCost[i][j] + m[i + 1][j + 1];
                    }
                } else if (j == m[0].length - 1) {
                    if (pathCost[i][j] + m[i + 1][j] < pathCost[i + 1][j]) {
                        pathCost[i + 1][j] = pathCost[i][j] + m[i + 1][j];
                    }
                    if (pathCost[i][j] + m[i + 1][j - 1] < pathCost[i + 1][j - 1]) {
                        pathCost[i + 1][j - 1] = pathCost[i][j] + m[i + 1][j - 1];
                    }
                } else {
                    if (pathCost[i][j] + m[i + 1][j] < pathCost[i + 1][j]) {
                        pathCost[i + 1][j] = pathCost[i][j] + m[i + 1][j];
                    }
                    if (pathCost[i][j] + m[i + 1][j + 1] < pathCost[i + 1][j + 1]) {
                        pathCost[i + 1][j + 1] = pathCost[i][j] + m[i + 1][j + 1];
                    }
                    if (pathCost[i][j] + m[i + 1][j - 1] < pathCost[i + 1][j - 1]) {
                        pathCost[i + 1][j - 1] = pathCost[i][j] + m[i + 1][j - 1];
                    }

                }
            }
        }

        //printing out given matrix
//        for (int i = 0; i < pathCost.length; i++) {
//            for (int j = 0; j < pathCost[0].length; j++) {
//                System.out.print(m[i][j] + " ");
//            }
//            System.out.println();
//        }
//
//        System.out.println();

        //printing out the min cost matrix
//        for (int i = 0; i < pathCost.length; i++) {
//            for (int j = 0; j < pathCost[0].length; j++) {
//                System.out.print(pathCost[i][j] + " ");
//            }
//            System.out.println();
//        }
//        System.out.println();


        //finding the smallest sum in the bottom of the cost matrix
        int min = pathCost[pathCost.length - 1][0];
        //the y-coordinate of the min sum at the bottom of the cost matrix
        int col = 0;
        for (int i = 1; i < pathCost[0].length; i++) {
            if (min > pathCost[pathCost.length - 1][i]) {
                min = pathCost[pathCost.length - 1][i];
                col = i;
            }
        }

        //adding tuple of sum and -1 to the arraylist that will be returned
        result.add(new Tuple(min, -1));

        //creating a tuple array to store the tuples of the min cost path
        Tuple[] minCostWidthCut = new Tuple[pathCost.length];
        minCostWidthCut[0] = new Tuple(pathCost.length - 1, col);

        //backtracking to get the tuples of the min cost path starting at the bottom of the cost matrix
        int c = 0;
        Tuple current = minCostWidthCut[c];
        c++;
        for (int i = current.getX(); i > 0; i--) {
            if (current.getY() == 0) {
                if (pathCost[current.getX() - 1][current.getY()] < pathCost[current.getX() - 1][current.getY() + 1]) {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY());
                    current = minCostWidthCut[c];
                    c++;

                } else if (pathCost[current.getX() - 1][current.getY() + 1] < pathCost[current.getX() - 1][current.getY()]) {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY() + 1);
                    current = minCostWidthCut[c];
                    c++;
                } else {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY());
                    current = minCostWidthCut[c];
                    c++;
                }
            } else if (current.getY() == pathCost.length - 1) {
                if (pathCost[current.getX() - 1][current.getY() - 1] < pathCost[current.getX() - 1][current.getY()]) {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY() - 1);
                    current = minCostWidthCut[c];
                    c++;

                } else if (pathCost[current.getX() - 1][current.getY()] < pathCost[current.getX() - 1][current.getY() - 1]) {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY());
                    current = minCostWidthCut[c];
                    c++;
                } else {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY() - 1);
                    current = minCostWidthCut[c];
                    c++;
                }
            } else {
                Tuple min2;
                if(pathCost[current.getX() - 1][current.getY() - 1] < pathCost[current.getX() - 1][current.getY()]) {
                    min2 = new Tuple(current.getX() - 1, current.getY() - 1);

                }
                else if (pathCost[current.getX() - 1][current.getY()] < pathCost[current.getX() - 1][current.getY() - 1]) {
                    min2 = new Tuple(current.getX() - 1, current.getY());
                }
                else {
                    min2 = new Tuple(current.getX() - 1, current.getY() - 1);
                }

                if(pathCost[current.getX() - 1][current.getY() + 1] < pathCost[min2.getX()][min2.getY()]) {
                    minCostWidthCut[c] = new Tuple(current.getX() - 1, current.getY() + 1);
                    current = minCostWidthCut[c];
                    c++;
                }
                else {
                    minCostWidthCut[c] = min2;
                    current = minCostWidthCut[c];
                    c++;
                }

            }
        }

        //adding the tuples in the tuple array to the array list that will be returned
        for(int i = minCostWidthCut.length - 1; i >= 0; i--) {
            result.add(minCostWidthCut[i]);
        }

        return result;
    }



   public static ArrayList<Tuple> stitchCut(int [][] m) {

        //Array list that will be returned
        ArrayList<Tuple> result = new ArrayList<>();

        //matrix that will hold the min stitch cut cost
        int[][] pathCost = new int[m.length][m[0].length];

        //copy the first row of the given matrix into the cost matrix
        for (int i = 0; i < pathCost[0].length; i++) {
            pathCost[0][i] = m[0][i];
        }

        //set the rest of the cost values in the matrix to a really high number
        for (int i = 1; i < pathCost.length; i++) {
            for (int j = 0; j < pathCost[0].length; j++) {
                pathCost[i][j] = Integer.MAX_VALUE;
            }
        }

        //filling up the stitch cut cost matrix and overwriting min cost values
        for (int i = 0; i < m.length - 1; i++) {
            for (int j = 0; j < m[0].length; j++) {
                if (j == m[0].length - 1) {
                    if (pathCost[i][j] + m[i + 1][j] < pathCost[i + 1][j]) {
                        pathCost[i + 1][j] = pathCost[i][j] + m[i + 1][j];
                    }
                }
                else {
                    if (pathCost[i][j] + m[i + 1][j] < pathCost[i + 1][j]) {
                        pathCost[i + 1][j] = pathCost[i][j] + m[i + 1][j];
                    }
                    if (pathCost[i][j] + m[i + 1][j + 1] < pathCost[i + 1][j + 1]) {
                        pathCost[i + 1][j + 1] = pathCost[i][j] + m[i + 1][j + 1];
                    }
                    if(pathCost[i][j] + m[i][j + 1] < pathCost[i][j + 1]) {
                        pathCost[i][j + 1] = pathCost[i][j] + m[i][j + 1];
                    }
                }
            }
        }

        //printing the given matrix
//        for (int i = 0; i < pathCost.length; i++) {
//            for (int j = 0; j < pathCost[0].length; j++) {
//                System.out.print(m[i][j] + " ");
//            }
//            System.out.println();
//        }

        System.out.println();

        //printing the stitch cut cost matrix
//        for (int i = 0; i < pathCost.length; i++) {
//            for (int j = 0; j < pathCost[0].length; j++) {
//                System.out.print(pathCost[i][j] + " ");
//            }
//            System.out.println();
//        }
//        System.out.println();


        //finding the min cost which is at the bottom row of the cost matrix
        int min = pathCost[pathCost.length - 1][0];
        int col = 0;
        for (int i = 1; i < pathCost[0].length; i++) {
            if (min > pathCost[pathCost.length - 1][i]) {
                min = pathCost[pathCost.length - 1][i];
                col = i;
            }
        }
        result.add(new Tuple(min, -1));

        //if the min cost is in the first column of the cost matrix, simply return the tuples in the first column
        if(col == 0) {
            for(int i = pathCost.length - 1; i >= 0; i--) {
                result.add(new Tuple(i , 0));
            }
            return result;
        }

        //Array list to hold the tuples of the min cost path starting with the last tuple
        ArrayList<Tuple> minCostStitchCut = new ArrayList<Tuple>();
        minCostStitchCut.add(new Tuple(pathCost.length - 1, col));

        // counter to keep track of the current tuple in the array list
        int c = 0;
        Tuple current = minCostStitchCut.get(c);


        /*
        finding the second tuple
        only two options as opposed to three (up and diagonal)
        only one case
         */
        if (pathCost[current.getX() - 1][current.getY() - 1] < pathCost[current.getX() - 1][current.getY()]) {
            minCostStitchCut.add(new Tuple(current.getX() - 1, current.getY() - 1));
            c++;
            current = minCostStitchCut.get(c);

        } else if (pathCost[current.getX() - 1][current.getY()] < pathCost[current.getX() - 1][current.getY() - 1]) {
            minCostStitchCut.add(new Tuple(current.getX() - 1, current.getY()));
            c++;
            current = minCostStitchCut.get(c);
        }
        else {
            minCostStitchCut.add(new Tuple(current.getX() - 1, current.getY() - 1));
            c++;
            current = minCostStitchCut.get(c);
        }

        int i = current.getX();

        //back tracking to find the rest of the tuples
        outerloop:
        while (i > 0) {

            if (current.getY() == 0) {
                for(int j = current.getX(); j > 0; j--) {
                    minCostStitchCut.add(new Tuple(j- 1, 0));

                }
                break outerloop;
            }
            else {
                Tuple min2;
                if(pathCost[current.getX() - 1][current.getY() - 1] < pathCost[current.getX() - 1][current.getY()]) {
                    min2 = new Tuple(current.getX() - 1, current.getY() - 1);

                }
                else if (pathCost[current.getX() - 1][current.getY()] < pathCost[current.getX() - 1][current.getY() - 1]) {
                    min2 = new Tuple(current.getX() - 1, current.getY());
                }
                else {
                    min2 = new Tuple(current.getX() - 1, current.getY() - 1);
                }

                if(pathCost[current.getX()][current.getY() - 1] < pathCost[min2.getX()][min2.getY()]) {
                    minCostStitchCut.add(new Tuple(current.getX(), current.getY() - 1));
                    c++;
                    current = minCostStitchCut.get(c);
                }
                else {
                    minCostStitchCut.add(min2);
                    c++;
                    current = minCostStitchCut.get(c);
                    i--;
                }

            }

        }
        //adding tuples in the cost arraylist to the result array list
        for(int j = minCostStitchCut.size() - 1; j >= 0; j--) {
            result.add(minCostStitchCut.get(j));
        }
        return result;
    }

    public static void main(String[] args) {

        Random rand = new Random();
        int[][] arr = new int[900][1600];
        for(int i = 0; i < arr.length; i++) {
            for(int j = 0; j < arr[0].length; j++) {
                arr[i][j] = rand.nextInt(1000);
            }
        }
//        arr[0][0] = 5;
//        arr[0][1] = 7;
//        arr[0][2] = 9;
//        arr[0][3] = 4;
//        arr[0][4] = 5;
//        arr[1][0] = 2;
//        arr[1][1] = 3;
//        arr[1][2] = 1;
//        arr[1][3] = 1;
//        arr[1][4] = 2;
//        arr[2][0] = 2;
//        arr[2][1] = 0;
//        arr[2][2] = 49;
//        arr[2][3] = 46;
//        arr[2][4] = 8;
//        arr[3][0] = 3;
//        arr[3][1] = 1;
//        arr[3][2] = 1;
//        arr[3][3] = 1;
//        arr[3][4] = 1;
//        arr[4][0] = 50;
//        arr[4][1] = 51;
//        arr[4][2] = 25;
//        arr[4][3] = 26;
//        arr[4][4] = 1;

        System.out.println("Widthcut:");
        ArrayList<Tuple> widthCut = MatrixCuts.widthCut(arr);
        for(int i = 0; i < widthCut.size(); i++) {
            System.out.print(widthCut.get(i).toString() + " ");
        }
        System.out.println();
        System.out.println("Stitchcut:");
        ArrayList<Tuple> stitchCut = MatrixCuts.stitchCut(arr);
        for(int i = 0; i < stitchCut.size(); i++) {
            System.out.print(stitchCut.get(i).toString() + " ");
        }

    }
}
