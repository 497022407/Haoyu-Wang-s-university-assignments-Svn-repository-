// student ID: a1785394
// student name: Haoyu Wang

// print lines that show the value and whether the variables are odd or even



import java.util.*;

public class Problem03 { //declare calss
	public static void main(String[] args){ //declare function main

		float sum = 0; //declare float variable
		int random, average = 0; //declare int variable

		// create random object
		Random ran = new Random();

		// print 10 times
		for (int i = 1; i <= 10; ++i){
			random = ran.nextInt(21); // generating random integer
			sum += random; // calculate the sum of the values.
			// print according to whether the nvalue are odd or even 
			System.out.print("Number (" + random + "): ");
			//if the value is even, print '+'
			if((random % 2 == 0) && (random != 1)){ 
				for (int j = 1; j <= random; j++){
					System.out.print('+');
				}
			}
			//if the value is odd, print '-'
			else{
				for (int j = 1; j <= random; j++){
				System.out.print('-');
				}
			}
			System.out.println(); // move the cursor to next line
		}

		average = (int)(sum/ 10 + 0.5); //calculate the mean of the values

		//print the mean of the values by '*'
		System.out.print("Average (" + average + "): ");

		for (int i = 1; i <= average; i++){
				System.out.print('*');
			}

		System.out.println();// move the cursor to next line
	}
}