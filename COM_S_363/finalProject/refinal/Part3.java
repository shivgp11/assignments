package group70;

/**
 *  
 * @author Cen Reyes	
 *
 */

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.sql.*;

import javax.swing.*;
import javax.swing.border.LineBorder;

public class Part3 {
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
		if (ioption == 0) // pressing OK button
		{
			result[0] = tfUsername.getText();
			result[1] = new String(pfPassword.getPassword());
		}
		return result;
	}
	private static void Q3(Connection conn, int k, int year) {
		if(conn == null || k == 0 || year == 0) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			
			PreparedStatement inststmt = conn.prepareStatement(" select hashtags_name, count(distinct state) as num_states,"
					+ " group_concat(distinct state) as states from users, tweets, hastags where users.screen_name = "
					+ "tweets.user_screen_name and hastags.tweets_tid = tweets.tid and year(created_time) = ? "
					+ "group by hashtags_name order by num_states desc limit ?; ");
			inststmt.setInt(1, year);
			inststmt.setInt(2, k);
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		} catch (SQLException e) {
		}
		
	}
	
	private static void Q7(Connection conn, String hashtag, String state, int k, int month, int year) {
		if (conn == null || hashtag == null || state == null || k == 0 || month == 0 || year == 0) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("select count(tid), screen_name, category from users, tweets, hastags where users.screen_name = tweets.user_screen_name and hastags.tweets_tid = tweets.tid and month(created_time) = ? and year(created_time) = ? and state = ? and hashtags_name = ? group by screen_name order by count(tid) desc limit ?; ");
			inststmt.setInt(1,month);
			inststmt.setInt(2, year);
			inststmt.setString(3, state);
			inststmt.setString(4, hashtag);
			inststmt.setInt(5, k);
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		}catch (SQLException e) {
		}
		
	}

	private static void Q9(Connection conn, String subcategory, int k) {
		if (conn == null || subcategory == null) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("select screen_name, subcategory, num_followers from users where subcategory = ? order by num_followers desc limit ?; ");
			inststmt.setString(1, subcategory);
			inststmt.setInt(2, k);
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		}catch (SQLException e) {
		}
	}
	
	private static void Q16(Connection conn, int k, int month, int year) {
		if (conn == null || k == 0 || month == 0 || year == 0) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("select name, category, text, retweet_count, urls_address from users, tweets, hasurls where users.screen_name = tweets.user_screen_name and hasurls.tweets_tid = tweets.tid and month(created_time) = ? and year(created_time) = ? order by retweet_count desc limit ?; ");
			inststmt.setInt(1, month);
			inststmt.setInt(2, year);
			inststmt.setInt(3, k);
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		}catch (SQLException e) {
		}
	}
	
	private static void Q18(Connection conn, int k, String subcategory, int month, int year) {
		if (conn == null || k == 0 || subcategory == null || month == 0 || year == 0) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("select mentions.user_screen_name, state, group_concat(distinct screen_name) from users, mentions, tweets where mentions.tweet_tid = tweets.tid and users.screen_name = tweets.user_screen_name and subcategory = ? and month(created_time) = ? and year(created_time) = ? group by mentions.user_screen_name order by count(screen_name) desc limit ?; ");
			inststmt.setString(1, subcategory);
			inststmt.setInt(2, month);
			inststmt.setInt(3, year);
			inststmt.setInt(4, k);
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		}catch (SQLException e) {
		}
	}
	
	private static void Q23(Connection conn, String subcategory, String months, int year, int k) {
		if (conn == null || subcategory == null || months == null || year == 0 || k == 0) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("select hashtags_name, count(tid) from hastags, users, tweets where hastags.tweets_tid = tweets.tid and users.screen_name = tweets.user_screen_name and subcategory = ? and year(created_time) = ? and find_in_set(month(created_time), ?) group by hashtags_name order by count(tid) desc limit ?; ");
			inststmt.setString(1, subcategory);
			inststmt.setInt(2, year);
			inststmt.setString(3, months);
			inststmt.setInt(4, k);
			
			ResultSet rs;
			ResultSetMetaData rsMetaData;
			String toShow;
			rs = inststmt.executeQuery();
			rsMetaData = rs.getMetaData();
			toShow = "";
			while (rs.next()) {
				for (int i = 0; i < rsMetaData.getColumnCount(); i++) {
					toShow += rs.getString(i + 1) + ", ";
				}
				toShow += "\n";
			}
			JOptionPane.showMessageDialog(null, toShow);
			inststmt.close();

			conn.commit();
		}catch (SQLException e) {
		}
	}
	
	private static void insert(Connection conn, String username, String name, int numFollowers, int numFollowing, String category, String subcategory, String state) {
		if (conn == null || username == null || name == null || category == null || subcategory == null || state == null) {
			throw new NullPointerException();
		}
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("insert into users values(?, ?, ?, ?, ?, ?, ?)");
			inststmt.setString(1, username);
			inststmt.setString(2, name);
			inststmt.setInt(3, numFollowers);
			inststmt.setInt(4, numFollowing);
			inststmt.setString(5, category);
			inststmt.setString(6, subcategory);
			inststmt.setString(7, state);
			int rowcount = inststmt.executeUpdate();

			System.out.println("Number of rows updated:" + rowcount);
			inststmt.close();
			// confirm that these are the changes you want to make
			conn.commit();
		} catch (SQLException e) {
		}
		
	}
	
	private static void delete(Connection conn, String userName) {
		if (conn == null || userName == null) {
			throw new NullPointerException();
		}
		
		try {
			conn.setAutoCommit(false);
			PreparedStatement inststmt = conn.prepareStatement("delete hastags from hastags inner join tweets on tweets_tid = tid where user_screen_name = ?;");
			inststmt.setString(1, userName);
			int rowcount = inststmt.executeUpdate();
			System.out.println("Number of rows updated:" + rowcount);
			inststmt.close();
			
			inststmt = conn.prepareStatement("delete hasurls from hasurls inner join tweets on tweets_tid = tid where user_screen_name = ?;");
			inststmt.setString(1, userName);
			int rowcount1 = inststmt.executeUpdate();
			System.out.println("Number of rows updated:" + rowcount1);
			inststmt.close();
			
			inststmt = conn.prepareStatement("delete mentions from mentions inner join tweets on tweet_tid = tid where tweets.user_screen_name = ?;");
			inststmt.setString(1, userName);
			int rowcount2 = inststmt.executeUpdate();
			System.out.println("Number of rows updated:" + rowcount2);
			inststmt.close();
			
			inststmt = conn.prepareStatement("delete from tweets where user_screen_name = ?;");
			inststmt.setString(1, userName);
			int rowcount3 = inststmt.executeUpdate();
			System.out.println("Number of rows updated:" + rowcount3);
			inststmt.close();
			
			inststmt = conn.prepareStatement("delete from users where screen_name = ?;");
			inststmt.setString(1, userName);
			int rowcount4 = inststmt.executeUpdate();
			System.out.println("Number of rows updated:" + rowcount4);
			inststmt.close();
			
			conn.commit();
		}catch (SQLException e) {
		}
	}
	
	//This method deletes the respective row from the rental and payment tables before deleting from customer.
	private static void deleteCustomer(Connection conn, int customer_id) {
		if (conn == null || customer_id == 0) {
			throw new NullPointerException();
		}

		try {
			conn.setAutoCommit(false);
			
			PreparedStatement inststmt = conn.prepareStatement("delete from rental where customer_id = ?");
			inststmt.setInt(1, customer_id);
			int rowcount = inststmt.executeUpdate();
			System.out.println("Number of rental rows updated:" + rowcount);
			inststmt.close();

			inststmt = conn.prepareStatement("delete from payment where customer_id = ?");
			inststmt.setInt(1, customer_id);
			rowcount = inststmt.executeUpdate();
			System.out.println("Number of payment rows updated:" + rowcount);
			inststmt.close();

			inststmt = conn.prepareStatement("delete from customer where customer_id = ?");
			inststmt.setInt(1, customer_id);
			rowcount = inststmt.executeUpdate();
			System.out.println("Number of customer rows updated:" + rowcount);
			inststmt.close();

			conn.commit();
		} catch (SQLException e) {
		}
	}
	
	//This is the main method.
	public static void main(String[] args) {
		String dbServer = "jdbc:mysql://localhost:3306/group70?useSSL=false";
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

			String option = "";
			String instruction = "Enter Q3: Find k hashtags that appeared in the most number of states in a given year; list the total number of states the\r\n" + 
					"hashtag appeared, the list of the distinct states it appeared (FL is the same as Florida*), and the hashtag itself in\r\n" + 
					"descending order of the number of states the hashtag appeared." + "\n"
					+ "Enter Q7: Find k users who used a given hashtag in a given state in a given month of a given year. Show the count of tweets\r\n" + 
					"posted with that hashtag along with the user’s screen name and category in descending order of the tweet count." + "\n"
					+ "Enter Q9: Find top k most followed users in a given party. Show the user’s screen name, the user’s party, and the number of\r\n" + 
					"followers in descending order of the number of followers." + "\n"
					+ "Enter Q16: Show names and categories of k users along with the tweet text, retweet count, and the url used by the user a given\r\n" + 
					"month of a given year in descending order of the retweet count"
					+ "Enter Q18: Find k users who were mentioned the most in tweets of users of a given party in a given month of a given year. Show\r\n" + 
					"the user’s screen name, user’s state, and the list of the screen name of the user(s) who mentioned this user in\r\n" + 
					"descending order of the number of tweets mentioning this user." + "\n"
					+ "Enter Q23: Find k most used hashtags with the count of tweets it appeared posted by a given sub-category of users in a\r\n" + 
					"list of months. Show the hashtag name and the count in descending order of the count." + "\n"
					+ "Enter insert: Insert information of a new user into the database." + "\n" 
					+ "Enter delete: Delete a given user and all the tweets the user has tweeted, relevant hashtags, and users mentioned." + "\n";

			while (true) {
				option = JOptionPane.showInputDialog(instruction);
				if (option.equalsIgnoreCase("Q3")) {
					String given1 = JOptionPane.showInputDialog("Enter the year: ");
					int year = Integer.parseInt(given1);
					String given = JOptionPane.showInputDialog("Enter the k value: ");
					int k = Integer.parseInt(given);
					Q3(conn, k, year);
				} 
				
				else if (option.equalsIgnoreCase("Q7")) {
					String given1 = JOptionPane.showInputDialog("Enter the month: ");
					String given2 = JOptionPane.showInputDialog("Enter the year: ");
					String state = JOptionPane.showInputDialog("Input your state: ");
					String hashtag = JOptionPane.showInputDialog("Input your hashtag: ");
					String given = JOptionPane.showInputDialog("Enter the k value: ");					
					int k = Integer.parseInt(given);
					int month = Integer.parseInt(given1);
					int year = Integer.parseInt(given2);
					Q7(conn, hashtag, state, k, month, year);
					
				} 
				else if (option.equalsIgnoreCase("Q9")) {
					String subcategory = JOptionPane.showInputDialog("Enter the subcategory: ");
					String given = JOptionPane.showInputDialog("Enter the k value: ");
					int k = Integer.parseInt(given);
					Q9(conn, subcategory, k);
				} 
				else if (option.equalsIgnoreCase("Q16")) {
					String given1 = JOptionPane.showInputDialog("Input the month: ");
					String given2 = JOptionPane.showInputDialog("Input the year: ");
					String given = JOptionPane.showInputDialog("Enter the k value: ");
					int k = Integer.parseInt(given);
					int month = Integer.parseInt(given1);
					int year = Integer.parseInt(given2);
					Q16(conn, k, month, year);
				}
				else if (option.equalsIgnoreCase("Q18")) {
					String subcategory = JOptionPane.showInputDialog("Enter the subcategory: ");
					String given1 = JOptionPane.showInputDialog("Enter the month: ");
					String given2 = JOptionPane.showInputDialog("Enter the year: ");
					String given = JOptionPane.showInputDialog("Enter the k value: ");
					int month = Integer.parseInt(given1);
					int year = Integer.parseInt(given2);
					int k = Integer.parseInt(given);
					Q18(conn, k, subcategory, month, year);
				}
				else if (option.equalsIgnoreCase("Q23")) {
					String subcategory = JOptionPane.showInputDialog("Enter the subcategory: ");
					String given2 = JOptionPane.showInputDialog("Enter the year: ");
					int year = Integer.parseInt(given2);
					String given = JOptionPane.showInputDialog("Enter the k value: ");
					int k = Integer.parseInt(given);
					String months = JOptionPane.showInputDialog("Enter the months (separate them by commas and NO SPACES (please c:) : ");
					Q23(conn, subcategory, months, year, k);
					
				}
				else if (option.equalsIgnoreCase("insert")) {
					String uName = JOptionPane.showInputDialog("Input the username: ");
					String name = JOptionPane.showInputDialog("Input the name: ");
					String given = JOptionPane.showInputDialog("Input the number of followers: ");
					int numFollowers = Integer.parseInt(given);
					String given2 = JOptionPane.showInputDialog("Input the number following: ");
					int numFollowing = Integer.parseInt(given2);
					String category = JOptionPane.showInputDialog("Input the category: ");
					String subcategory = JOptionPane.showInputDialog("Input the subcategory: ");
					String state = JOptionPane.showInputDialog("Input the state (abbreviated form ex: IA): ");
					insert(conn, uName, name, numFollowers, numFollowing, category, subcategory, state);
				}
				else if (option.equalsIgnoreCase("delete")) {
					String screenName = JOptionPane.showInputDialog("Input the screen name: ");
					delete(conn, screenName);
					
				}
				else if (option.equalsIgnoreCase("e")) {
					System.exit(0);
				}
				else {
					break;
				}
			}

			stmt.close();
			conn.close();
		} catch (Exception e) {
			System.out.println("Program terminates due to errors");
			e.printStackTrace(); // for debugging
		}
	}

}
