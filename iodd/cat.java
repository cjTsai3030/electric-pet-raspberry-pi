package iodd;
import java.awt.*;
import javax.swing.*;
import java.net.ServerSocket;
import java.net.Socket;

public class cat extends JFrame
{
	private static JFrame face = new JFrame();
	private static JLabel label;
	private static ImageIcon icon;
	private static ImageIcon tmp1, tmp2, cry1, cry2, angry1, angry2, die1, die2, hungry1, hungry2, happy1, happy2, sleep1, sleep2, origin, love1, love2;

	public static ImageIcon getFace (String imgName){
		String path = new String("with/");
		path += imgName;
		System.out.println("Path = " + path);
		Image img = new ImageIcon(path).getImage().getScaledInstance(480, 320, java.awt.Image.SCALE_SMOOTH);
		ImageIcon imgIcon = new ImageIcon(img);
		return imgIcon;
	}

	public static void animation(String input) {

		switch(input) {
		case "cry"   : tmp1 = cry1; tmp2 = cry2; break;
		case "angry" : tmp1 = angry1; tmp2 = angry2; break;
		case "die"   : tmp1 = die1; tmp2 = die2; break;
		case "hungry": tmp1 = hungry1; tmp2 = hungry2; break;
		case "happy" : tmp1 = happy1; tmp2 = happy2; break;
		case "sleep" : tmp1 = sleep1; tmp2 = sleep2; break;
		case "love"  : tmp1 = love1; tmp2 = love2; break;
		case "origin": tmp1 = tmp2 = origin; break;
		}	
	}

	public static Runnable move = new Runnable() {
		@Override
		public void run (){
			while(true) {
			 	try{
                                	label.setIcon(tmp1);
                                	Thread.sleep(500);
                                	label.setIcon(tmp2);
                                	Thread.sleep(500);
                        	} catch (InterruptedException e) {
                                	System.out.println(e);
                        	}

			}
		}		
	};

	public static void main (String[] args) {
		
		cry1 = getFace("cry1.jpg");
		cry2 = getFace("cry2.jpg");
		sleep1 = getFace("sleep1.jpg");
		sleep2 = getFace("sleep2.jpg");
                angry1 = getFace("angry1.jpg");
                angry2 = getFace("angry2.jpg");
                die1 = getFace("die1.jpg");
                die2 = getFace("die2.jpg");
                hungry1 = getFace("hungry1.jpg");
                hungry2 = getFace("hungry2.jpg");
                happy1 = getFace("happy1.jpg");
                happy2 = getFace("happy2.jpg");
                love1 = getFace("love1.jpg");
                love2 = getFace("love2.jpg");
                origin = getFace("origin.jpg");


		label = new JLabel(origin);
		face.add(label);
		face.pack();
		face.setVisible(true);
		//label.setIcon(origin);

		Thread thread = new Thread(move);
		thread.start();	

		SocketServer server = new SocketServer();
		server.start();
	}
}
