// student ID: a1785394
// student name: Haoyu Wang


// print symbols according to the value

import java.util.*;

public class Problem03 { // declare calss
	public static void main(String[] args){ // declare function main

		float sum = 0; // declare float variable
		int random, average = 0; // declare int variable

		// create random object
		Random ran = new Random();

		// print 10 times
		for (int i = 1; i <= 10; ++i){
			random = ran.nextInt(21); // generating random integer
			sum += random; // calculate the sum of the values
			System.out.print("Number (" + random + "): ");

			// print symbols according to the value
			switch (random){
				case 1:
				for (int j = 1; j <= random; j++){
					System.out.print("o");
				}
				break;
				case 2:
				for (int j = 1; j <= random; j++){
					System.out.print("o");
				}
				break;
				case 3:
				for (int j = 1; j <= random; j++){
					System.out.print("o");
				}
				break;
				case 4:
				for (int j = 1; j <= random; j++){
					System.out.print("o");
				}
				break;
				case 5:
				for (int j = 1; j <= random; j++){
					System.out.print("o");
				}
				break;
				case 6:
				for (int j = 1; j <= random; j++){
					System.out.print("x");
				}
				break;
				case 7:
				for (int j = 1; j <= random; j++){
					System.out.print("x");
				}
				break;
				case 8:
				for (int j = 1; j <= random; j++){
					System.out.print("x");
				}
				break;
				case 9:
				for (int j = 1; j <= random; j++){
					System.out.print("x");
				}
				break;
				case 10:
				for (int j = 1; j <= random; j++){
					System.out.print("x");
				}
				break;
				case 11:
				for (int j = 1; j <= random; j++){
					System.out.print("s");
				}
				break;
				case 12:
				for (int j = 1; j <= random; j++){
					System.out.print("s");
				}
				break;
				case 13:
				for (int j = 1; j <= random; j++){
					System.out.print("s");
				}
				break;
				case 14:
				for (int j = 1; j <= random; j++){
					System.out.print("s");
				}
				break;
				case 15:
				for (int j = 1; j <= random; j++){
					System.out.print("s");
				}
				break;
				default :
				for (int j = 1; j <= random; j++){
					System.out.print("*");
				}
				break;
			}

			System.out.println(); // move the cursor to next line
		}

		average = (int)(sum/ 10 + 0.5); // calculate the mean of the values

		// print the mean of the values by '*'
		System.out.print("Average (" + average + "): ");

		for (int i = 1; i <= average; i++){
				System.out.print('*');
			}

		System.out.println(); // move the cursor to next line
	}
}