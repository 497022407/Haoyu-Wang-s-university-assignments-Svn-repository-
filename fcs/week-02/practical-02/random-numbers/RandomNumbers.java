// student ID: a1785394
// student name: Haoyu Wang


// generate 10 different positive integer variables and calculate the mean of these values

import java.util.*;

public class RandomNumbers{ //declare calss
	public static void main(String[] args){ //declare function main

		float sum = 0; //declare float variable
		float average = 0;  //declare float variable
		int random;  //declare int variable

		// create random object
		Random ran = new Random();

		// generating random positive integer
		for (int i = 1; i <= 10; ++i){
			random = ran.nextInt(); // generate random variable
			if (random < 0) {  // if random is negative, change it to positive number value.
				random = random - 2 * random;
			}
			sum += random; // calculate the sum of the values.
		}

		average = sum / 10;  //calculate the mean of the values

		System.out.println("The mean of 10 positive intergers is " + average); //print the mean of the values
	}
}