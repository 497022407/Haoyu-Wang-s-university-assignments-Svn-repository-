// student ID: a1785394
// student name: Haoyu Wang


// identify prime number



import java.util.*;

public class Problem02{ //declare calss
	public static void main(String[] args){ //declare function main

		int number = 0;  //declare int variable

		// create Scanner object
		Scanner input = new Scanner(System.in);

		//print prompt message
		System.out.println("please input a number");

		//get input of a number
		try{ // try to catch a exception
			number = input.nextInt();
			if(number <= 1)
				System.out.println("Unacceptable input");
		}catch(InputMismatchException e){ // if find exception InputMismatchException
			System.out.println("Exception ： " + e); // print exception
		}catch(IllegalArgumentException e){ // if find exception IllegalArgumentException
			System.out.println("Exception ： " + e); // print exception
		}

		// call method to indentify whether it's prime
		test(number);
	}

	public static void test(int number){ // define method of identifying prime

		int i = 2;

		// test whether it is prime
		for (; i < number; ++i){ 
			if (number % i == 0) {  //  if it is not prime, print it is not prime
				System.out.println("Your number is not prime");
				break;
			}
		}

		// if it is not, print it is not
		if(i == number)
			System.out.println("Your number is prime");
	}
}