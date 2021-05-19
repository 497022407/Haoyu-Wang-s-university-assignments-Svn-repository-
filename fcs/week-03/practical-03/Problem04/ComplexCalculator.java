// student ID: a1785394
// student name: Haoyu Wang


// 



import java.util.*;

public class ComplexCalculator{ //declare calss
	public static void main(String[] args){ //declare function main

		float number1a = 0;  // declare float variable
		float number1b = 0;
		float number2a = 0;
		float number2b = 0;

		// create Scanner object
		Scanner input = new Scanner(System.in);

		//get input of 2 complex numbers
		try{ // try to catch a exception
			System.out.println("please input a of the first number");
			number1a = input.nextFloat();
			System.out.println("please input b of the first number");
			number1b = input.nextFloat();
			System.out.println("please input a of the second number");
			number2a = input.nextFloat();
			System.out.println("please input b of the second number");
			number2b = input.nextFloat();
			// call method to calculate
			add(number1a, number1b, number2a, number2b);
			sub(number1a, number1b, number2a, number2b);
			multiplication(number1a, number1b, number2a, number2b);
			division(number1a, number1b, number2a, number2b);
		}catch(InputMismatchException e){ // if find exception InputMismatchException
			System.out.println("Exception ： " + e); //print exception
		}
	}

	public static void add(float a1, float b1, float a2, float b2){ // define method of addition

		// calculate addition
		float a = a1 + a2;
		float b = b1 + b2;
		// print result
		if(b < 0)
			System.out.println("Addition of the two complex numbers is " + a + " " + b + 'i');
		else
			System.out.println("Addition of the two complex numbers is " + a + " + " + b + 'i');
	}

	public static void sub(float a1, float b1, float a2, float b2){ // define method of subtraction

		// calculate subtraction
		float a = a1 - a2;
		float b = b1 - b2;
		// print result
		if(b < 0)
			System.out.println("Subtraction of the two complex numbers is " + a + " " + b + 'i');
		else
			System.out.println("Subtraction of the two complex numbers is " + a + " + " + b + 'i');
	}

	public static void multiplication(float a1, float b1, float a2, float b2){ // define method of multiplication

		// calculate multiplication
		float a = a1 * a2 - b1 * b2;
		float b = a1 * b2 + a2 * b1;
		// print result
		if(b < 0)
			System.out.println("Multiplication of the two complex numbers is " + a + " " + b + 'i');
		else
			System.out.println("Multiplication of the two complex numbers is " + a + " + " + b + 'i');
	}

	public static void division(float a1, float b1, float a2, float b2){ // define method of division

		// calculate division
		float a = (a1 * a2 + b1 * b2) / (a2 * a2 + b2 * b2);
		float b = (a2 * b1 - a1 * b2) / (a2 * a2 + b2 * b2);
		// print result
		if(b < 0)
			System.out.println("Division of the two complex numbers is " + a + " " + b + 'i');
		else
			System.out.println("Division of the two complex numbers is " + a + " + " + b + 'i');
	}
}