/**
 * @author Shiv Patel
 */
package application;

import javafx.application.Application;
import javafx.beans.property.Property;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Ellipse;

public class TicTacToe extends Application {

	private Cell[][] cell = new Cell[3][3];
	private char turn = 'X';
	private Label status = new Label("Turn X");

	public void start(Stage primaryStage) {
		GridPane pane = new GridPane();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				pane.add(cell[i][j] = new Cell(), j, i);

		BorderPane borderPane = new BorderPane();
		borderPane.setCenter(pane);
		borderPane.setBottom(status);

		Scene scene = new Scene(borderPane, 900, 600);
		primaryStage.setTitle("Tic-Tac-Toe");
		primaryStage.setScene(scene);
		primaryStage.show();
	}

	public boolean isFull() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (cell[i][j].getToken() == ' ')
					return false;
		return true;
	}

	public boolean isWon(char token) {
		for (int i = 0; i < 3; i++)
			if (cell[i][0].getToken() == token && cell[i][1].getToken() == token && cell[i][2].getToken() == token) {
				return true;
			}
		for (int j = 0; j < 3; j++)
			if (cell[0][j].getToken() == token && cell[1][j].getToken() == token && cell[2][j].getToken() == token) {
				return true;
			}
		if (cell[0][0].getToken() == token && cell[1][1].getToken() == token && cell[2][2].getToken() == token) {
			return true;
		}
		if (cell[0][2].getToken() == token && cell[1][1].getToken() == token && cell[2][0].getToken() == token) {
			return true;
		}

		return false;
	}

	public class Cell extends Pane {
		private char move = ' ';
		public Cell() {
			setStyle("-fx-border-color: black");
			this.setPrefSize(800, 800);
			this.setOnMouseClicked(e -> handleMouseClick());
		}

		public char getToken() {
			return move;
		}

		public void setToken(char c) {
			move = c;
			if (move == 'X') {
				Image image = new Image("file:x.jpg", this.getWidth(), this.getHeight(), false, false);
				ImageView imgview = new ImageView(image);
				imgview.fitWidthProperty().bind(this.widthProperty());
				imgview.fitHeightProperty().bind(this.heightProperty());
				this.getChildren().add(imgview);
			} else if (move == 'O') {
				Image image = new Image("file:o.jpg", this.getWidth(), this.getHeight(), false, false);
				ImageView imgview = new ImageView(image);
				imgview.fitWidthProperty().bind(this.widthProperty());
				imgview.fitHeightProperty().bind(this.heightProperty());
				this.getChildren().add(imgview);
			}
		}

		private void handleMouseClick() {

			if (move == ' ' && turn != ' ') {
				setToken(turn);
				if (isWon(turn)) {
					status.setText("Congratulations, " + turn + " won the game!");
					turn = ' ';
				} else if (isFull()) {
					status.setText("Draw");
					turn = ' ';
				} else {
					turn = (turn == 'X') ? 'O' : 'X';
					status.setText("Turn: " + turn);
				}
			}
		}
	}

	public static void main(String[] args) {
		launch(args);
	}
}