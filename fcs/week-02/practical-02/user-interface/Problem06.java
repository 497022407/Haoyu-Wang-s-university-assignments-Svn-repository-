// student ID: a1785394
// student name: Haoyu Wang


// calculate the sum of 2 numbers given by user

import java.util.Scanner;

public class Problem06{ // declare calss
	public static void main(String [] args){ // declare function main

		int number1, number2, sum; // declare int variable
		char option; // declare char variable

		Scanner input = new Scanner(System.in); //create an object of scanner class

		do {
			//print prompt message
			System.out.println("Welcome dear user!");
			System.out.println("Would you like to:");
			System.out.println("a) sum again");
			System.out.println("b) exit");
			System.out.println("Option: ");

			// get input of the selection from user
			option = input.next().charAt(0);

			// if user chose to calculate
			if (option == 'a'){
				// ask user to input 2 numbers
				System.out.println("Please, insert the first number: ");
				number1 = input.nextInt(); //get int input from user

				System.out.println("Please, insert the second number: ");
				number2 = input.nextInt(); //get int input from user

				// calculate the sum
				sum = number1 + number2;

				// ptint the result of sum
				System.out.println("Thank you for your enquiry, the sum between " + number1 + " and " + number2 + " is " + sum);
			}
		}while(option == 'a'); // if user chose to continue, then do ti again
		// if user chose to quit, then print "Thank you! Have a good day."
		System.out.println("Thank you! Have a good day.");
	}
}


