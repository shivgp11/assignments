package hw2;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class MyServer {
   static ArrayList<Socket> sockets = new ArrayList<>();

    public static void main(String[] args) throws IOException {

        ServerSocket serverSocket = null;

        try {
            serverSocket = new ServerSocket(4444); // provide MYSERVICE at port

        }
        catch (IOException e) {
        }

        while (true) {
            Socket clientSocket = null;
            try {

                clientSocket = serverSocket.accept();
                sockets.add(clientSocket);

                Thread t = new Thread(new ClientHandler(clientSocket, sockets));
                t.start();

            } catch (IOException e) {
            }
        }
    }

}

class ClientHandler implements Runnable {

    Socket s;
    ArrayList<Socket> sockets;

    ClientHandler(Socket s, ArrayList<Socket> sockets) {
        this.s = s;
        this.sockets = sockets;
    }

    public void run() {

        Scanner in;
        PrintWriter out;

        try {
            in = new Scanner(new BufferedInputStream(s.getInputStream()));
            out = new PrintWriter(new BufferedOutputStream(s.getOutputStream()));
            out.println("Enter your name:");
            out.flush();
            String name = in.nextLine();
            out.println("Enter access code:");
            out.flush();
            String accessCode = in.nextLine();
            while(!accessCode.equals("cs319Spring2020")) {
                out.println("Incorrect access code, please try again:");
                out.flush();
                accessCode = in.nextLine();
            }
            out.println("You are connected");
            out.flush();
            while(true) {
                String clientMessage = in.nextLine();

                System.out.println(name + ": " + clientMessage);

                for(int i = 0; i < sockets.size(); i++) {
                    if(!s.equals(sockets.get(i))) {
                        out = new PrintWriter(new BufferedOutputStream(sockets.get(i).getOutputStream()));
                        out.println(name + ": " +  clientMessage);
                        out.flush();
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


    }


}