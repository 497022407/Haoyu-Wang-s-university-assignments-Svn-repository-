//==================================
// Foundations of Computer Science
// Student: Haoyu Wang
// id: a1785394
// Semester: 1
// Year:2020
// Practical Exam Number:
//===================================

// count from 50 to 3

class Problem {  //declare calss
	public static void main(String [] args) {  //declare the function main

		for (int i = 48; i >= 3; i -= 3) { //count from 49 to 3, as integer numbers, only include multiples of the number 3

			if(i >= 30){ // if the integer numbers are between 30 and 50 except 33, print 0
				if(i == 33){
					for (int j = 1; j <= i; j++){
					System.out.print('3');
					}
				}
				else{
					for (int j = 1; j <= i; j++){
					System.out.print('o');
					}
				}
				System.out.println();
			}
			else if (i >= 20){ // if the integer numbers are between 20 and 30, print x
				for (int j = 1; j <= i; j++){
					System.out.print('x');
				}
				System.out.println();
			}
			else if (i >= 10){ // if the integer numbers are between 10 and 20, print =
				for (int j = 1; j <= i; j++){
					System.out.print('=');
				}
				System.out.println();
			}
			else{ // if the integer numbers are between 1 and 10, print *
				for (int j = 1; j <= i; j++){
					System.out.print('*');
				}
				System.out.println();
			}

		}
	}
}

