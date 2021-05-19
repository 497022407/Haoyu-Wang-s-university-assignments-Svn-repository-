//==================================
// Foundations of Computer Science
// Student: Haoyu Wang
// id: a1785394
// Semester: 1
// Year:2020
// Practical Exam Number:
//===================================

// count from 1 to 40

class Problem {  //declare calss
	public static void main(String [] args){  //declare the function main

		for (int i = 1; i <= 40; i++){ //count from 1 to 40, as integer numbers

			if(i < 10){ // if the integer numbers are less than 10, print *
				for (int j = 1; j <= i; j++){
					System.out.print('*');
				}
				System.out.println();
			}
			else if (i < 20){ // if the integer numbers are between 10 and 20, print =
				for (int j = 1; j <= i; j++){
					System.out.print('=');
				}
				System.out.println();
			}
			else if (i < 30){ // if the integer numbers are between 20 and 30, print x
				for (int j = 1; j <= i; j++){
					System.out.print('x');
				}
				System.out.println();
			}
			else{ // if the integer numbers are between 30 and 40, print o
				for (int j = 1; j <= i; j++){
					System.out.print('o');
				}
				System.out.println();
			}

		}
	}
}

