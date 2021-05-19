// student ID: a1785394
// student name: Haoyu Wang


// change an particular amount of cash to a combination of $20 and/or $50 notes

import java.util.Scanner;

public class ATM{ // declare calss
	public static void main(String [] args){ // declare function main

		int cash; // declare int variable
		char option; // declare char variable

		Scanner input = new Scanner(System.in); //create an object of scanner class

		System.out.println("Please input your money"); //print prompt message

		cash = input.nextInt(); // get input of money from user

		run(cash); // call the method "run"
	}

	public static void run (int money){ // declare method "run"

		int cash50, cash20; // declare int variable

		cash50 = money / 50; // calculate how many 50$ cash are needed
		cash20 = (money % 50) / 20; // calculate how many 20$ cash are needed

		if ((money % 50) % 20 == 0){ // indentify whether the given amount money can be withdrew

			// print the result
			System.out.println("Here is " + cash20 + " $20 notes and " + cash50 + " $50 notes.");

		}

		else if ((money % 100) % 20 == 0){  // indentify whether the given amount money can be withdrew

			cash50 = money / 100 * 2; // calculate how many 50$ cash are needed
			cash20 = (money % 100) / 20; // calculate how many 20$ cash are needed

			// print the result of the combination
			System.out.println("Here is " + cash20 + " $20 notes and " + cash50 + " $50 notes.");

		}

		else { // if the value you input cannot be withdrew

			System.out.println("Sorry, the value you input cannot be withdrew"); // print "Sorry, the value you input cannot be withdrew"
		}
	}
}


