package hw2;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.SQLOutput;
import java.util.Scanner;

public class MyCLient {

    public static void main(String[] args) throws UnknownHostException,
            IOException {

        Scanner scan = new Scanner(System.in);
        PrintWriter out;
        Socket socket = new Socket("localhost", 4444);
        Thread t = new Thread(new ServerHandler(socket));
        t.start();

        out = new PrintWriter(new BufferedOutputStream(socket.getOutputStream()));
        while (true) {
            out.println(scan.nextLine());
            out.flush();
        }

    }


}

class ServerHandler implements Runnable {
    Socket s;

    public ServerHandler(Socket s) {
        this.s = s;
    }

    public void run() {
        try {
            Scanner in = new Scanner(new BufferedInputStream(s.getInputStream()));
            while (true) {
                System.out.println(in.nextLine());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}