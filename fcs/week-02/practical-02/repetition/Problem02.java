// student ID: a1785394
// student name: Haoyu Wang


// print star lines that show the value of the variables

import java.util.*;

public class Problem02 { //declare calss
	public static void main(String[] args){ //declare function main
		
		float sum = 0;
		int random, average = 0;

		// create random object
		Random ran = new Random();

		// print horizontal star lines
		for (int i = 1; i <= 10; ++i){
			random = ran.nextInt(21); // generating random integer
			sum += random; // calculate the sum of the values
			// print star line that shows the value of the variables
			System.out.print("Number (" + random + "): ");
			for (int j = 1; j <= random; j++){
				System.out.print('*');
			}
			System.out.println(); // move the cursor to next line
		}

		// calculate the mean of these values
		average = (int)(sum/ 10 + 0.5);

		// print the mean of these values
		System.out.print("Average (" + average + "): ");

		for (int i = 1; i <= average; i++){
				System.out.print('*');
			}

		System.out.println();// move the cursor to next line
	}
}