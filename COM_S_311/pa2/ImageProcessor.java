package pa2;

import java.util.ArrayList;

public class ImageProcessor {

    public static Picture reduceWidth(int x, String inputImage) {

        Picture pic = new Picture(inputImage);
        int count = 0;
        while(count < x) {
            int[][] I = new int[pic.height()][pic.width()];

            //compute the importance matrix
            for(int i = 0; i < I.length; i++) {
                for(int j = 0; j < I[0].length; j++) {
                    if(j == 0) {
                        I[i][j] = ImageStitch.pixelDistance(pic.get(j, i), pic.get(j + 1, i));
                    }
                    else if (j == pic.width() - 1) {
                        I[i][j] = ImageStitch.pixelDistance(pic.get(j, i), pic.get(j - 1, i));
                    }
                    else {
                        I[i][j] = ImageStitch.pixelDistance(pic.get(j - 1, i), pic.get(j + 1, i));
                    }
                }
            }


            // Holds the widthcut tuples to be deleted
              ArrayList<Tuple> widthCut = MatrixCuts.widthCut(I);

            //shifting elements
            for(int i = 1; i < widthCut.size(); i++) {
                int row = widthCut.get(i).getX();
                int col  = widthCut.get(i).getY();
                for(int j = col; j < pic.width() - 1; j++) {
                    pic.set(j, row, pic.get(j + 1, row));
                }
            }
            //cropping out last column of pic
            pic = ImageStitch.crop(pic, 1);
           count++;
        }

        return pic;


    }
    public static void main(String[] args) {
        Picture pic = ImageProcessor.reduceWidth(200, "https://wallpapercave.com/wp/DrU7MMU.jpg");
        pic.show();
    }
}
