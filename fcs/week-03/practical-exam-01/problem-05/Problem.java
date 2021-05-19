//==================================
// Foundations of Computer Science
// Student: Haoyu Wang
// id: a1785394
// Semester: 1
// Year:2020
// Practical Exam Number:
//===================================

// re-organize the code 

class Problem {  //declare calss
	public static void main(String [] args) {  //declare the function main

		int ths = 25; //Declare integer variable

		System.out.println("This is the last line of the code!"); //print "This is the last line of the code!"

		for(int i = 0; i < 10; i++){
			for(int j = i; j < 10; j++){
				for (int k = j; k < 10; k ++){
					int value = i * j * k; 
					if(value != 0){
						if(value % ths == 0 ){
							System.out.print("i: " + i); 
							System.out.print(" j: " + j);
							System.out.println(" k: " + k + " - value " + value);
						}
					}
				}
			}
		}

		System.out.println("This is the first line of the code!"); //print "This is the first line of the code!"
	}
}


