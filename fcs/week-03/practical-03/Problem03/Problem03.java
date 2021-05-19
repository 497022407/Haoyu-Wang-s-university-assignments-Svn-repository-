// student ID: a1785394
// student name: Haoyu Wang


// compare 2 variables and print the bigger one



import java.util.*;

public class Problem03{ //declare calss
	public static void main(String[] args){ //declare function main

		float number1 = 0;  //declare float variable
		float number2 = 0;

		// create Scanner object
		Scanner input = new Scanner(System.in);

		//get input of 2 numbers
		try{ // try to catch a exception
			System.out.println("please input the first number");
			number1 = input.nextFloat();
			System.out.println("please input the second number");
			number2 = input.nextFloat();
			
			test(number1, number2); // call method to compare
		}catch(InputMismatchException e){ // if find exception InputMismatchException
			System.out.println("Exception ： " + e); //print exception
		}
	}

	public static void test(float number1, float number2){ // define method

		// compare numbers and print the biggest one
		if(number1 >= number2)
			System.out.println("The bigger number is " + number1);
		else
			System.out.println("The bigger number is " + number2);
	}
}