/**
 * @author Shiv Patel 
 */
package cs363;

import java.awt.Color;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.sql.*;
import javax.swing.*;
import javax.swing.border.LineBorder;

public class hw4 {
	//function that gives user interface 
	public static String[] loginDialog() {
		String result[] = new String[2];
		JPanel panel = new JPanel(new GridBagLayout());
		GridBagConstraints cs = new GridBagConstraints();

		cs.fill = GridBagConstraints.HORIZONTAL;

		JLabel lbUsername = new JLabel("Username: ");
		cs.gridx = 0;
		cs.gridy = 0;
		cs.gridwidth = 1;
		panel.add(lbUsername, cs);

		JTextField tfUsername = new JTextField(20);
		cs.gridx = 1;
		cs.gridy = 0;
		cs.gridwidth = 2;
		panel.add(tfUsername, cs);

		JLabel lbPassword = new JLabel("Password: ");
		cs.gridx = 0;
		cs.gridy = 1;
		cs.gridwidth = 1;
		panel.add(lbPassword, cs);

		JPasswordField pfPassword = new JPasswordField(20);
		cs.gridx = 1;
		cs.gridy = 1;
		cs.gridwidth = 2;
		panel.add(pfPassword, cs);
		panel.setBorder(new LineBorder(Color.GRAY));

		String[] options = new String[] { "OK", "Cancel" };
		int ioption = JOptionPane.showOptionDialog(null, panel, "Login", JOptionPane.OK_OPTION,
				JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
		if (ioption == 0) {
			result[0] = tfUsername.getText();
			result[1] = new String(pfPassword.getPassword());
		}
		return result;
	}

	//inserts actor given the first name and last name of the actor
	private static void insertActor(Connection conn, String fname, String lname) {

		if (conn == null || fname == null || lname == null)
			throw new NullPointerException();
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			ResultSet rs;
			int id = 0;
			rs = stmt.executeQuery("select max(actor_id) from actor");
			while (rs.next()) {
				id = rs.getInt(1);
			}
			rs.close();
			stmt.close();

			PreparedStatement inststmt = conn.prepareStatement(
					" insert into actor (actor_id, first_name, last_name, last_update) values(?,?,?, current_date())");
			inststmt.setInt(1, id + 1);
			inststmt.setString(2, fname);
			inststmt.setString(3, lname);

			int rowcount = inststmt.executeUpdate();

			System.out.println("Number of rows updated:" + rowcount);
			inststmt.close();
			conn.commit();
		} catch (SQLException e) {
		}

	}

	//deletes all rows with the given customer id from rental, payment, and customer relations
	private static void deleteCustomer(Connection conn, String cid) {
		if (conn == null || cid == null) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			int customerid = Integer.parseInt(cid);
			PreparedStatement inststmt;

			inststmt = conn.prepareStatement("delete from rental where customer_id = ?");
			inststmt.setInt(1, customerid);
			int rowcount = inststmt.executeUpdate();
			System.out.println("Number of rows updated on rental:" + rowcount);
			inststmt.close();

			inststmt = conn.prepareStatement("delete from payment where customer_id = ?");
			inststmt.setInt(1, customerid);
			rowcount = inststmt.executeUpdate();
			System.out.println("Number of rows updated on payment:" + rowcount);
			inststmt.close();

			inststmt = conn.prepareStatement("delete from customer where customer_id = ?");
			inststmt.setInt(1, customerid);
			rowcount = inststmt.executeUpdate();
			System.out.println("Number of rows updated on customer:" + rowcount);
			inststmt.close();

			conn.commit();
		} catch (SQLException e) {

		}
	}

	//call the my_total_sales procedure to calculate the total sales for the given month
	private static void callMyTotalSales(Connection conn, String month) {
		int m = Integer.parseInt(month);
		if (conn == null)
			throw new NullPointerException();
		double totalSales = 0;
		try {
			CallableStatement cstmt = conn.prepareCall("{call my_total_sales(?,?)}");
			cstmt.setInt("given_month", m);
			cstmt.registerOutParameter("total_amount", Types.DOUBLE);
			cstmt.execute();
			totalSales = cstmt.getDouble("total_amount");
			System.out.println(totalSales);
			cstmt.close();

		} catch (SQLException e) {

		}
	}

	//main function to launch connect to login into server, display the user interface, and take input
	public static void main(String[] args) {
		String dbServer = "jdbc:mysql://localhost:3306/sakila_mod?useSSL=false";
		String userName = "";
		String password = "";

		String result[] = loginDialog();
		userName = result[0];
		password = result[1];

		Connection conn;
		Statement stmt;
		if (result[0] == null || result[1] == null) {
			System.out.println("Terminating: No username nor password is given");
			return;
		}
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			conn = DriverManager.getConnection(dbServer, userName, password);
			stmt = conn.createStatement();
			String sqlQuery = "";

			String option = "";
			String instruction = "Enter a: Enter new actor" + "\n" + "Enter b: Delete Customer " + "\n"
					+ "Enter c: Calculate total sales for month" + "\n" + "Enter e: Quit " + "\n";

			while (true) {
				option = JOptionPane.showInputDialog(instruction);
				if (option.equals("a")) {
					String fname = JOptionPane.showInputDialog("Enter first name of actor:");
					String lname = JOptionPane.showInputDialog("Enter last name of actor:");
					insertActor(conn, fname, lname);
				} else if (option.equalsIgnoreCase("b")) {
					String cid = JOptionPane.showInputDialog("Enter customer id:");
					String proceed = JOptionPane.showInputDialog(
							"WARNING: All info on customer " + cid + " will be lost. Do you want to proceed? y/n");
					if (proceed.equals("y")) {
						deleteCustomer(conn, cid);
					}
				} else if (option.equals("c")) {
					String month = JOptionPane.showInputDialog("Enter month:");
					callMyTotalSales(conn, month);

				} else if (option.equals("e")) {
					System.exit(0);
				} else {
					break;
				}
			}

			stmt.close();
			conn.close();
		} catch (Exception e) {
			System.out.println("Program terminates due to errors");
			e.printStackTrace();
		}
	}

}
