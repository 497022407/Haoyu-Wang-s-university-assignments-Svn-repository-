// student ID: a1785394
// student name: Haoyu Wang


// calculate determinant of matrix



import java.util.*;

public class Problem05{ //declare calss
	public static void main(String[] args){ //declare function main
		
		int dimension, result = 0; //declare int variable

		// create Scanner object
		Scanner input = new Scanner(System.in);

		//print prompt message
		System.out.println("please input dimension: ");

		//get input of dimension
		dimension = input.nextInt();

		//create array
		int[][] matrix = new int[dimension][dimension];

		//get input of matrix
		if(dimension == 2 || dimension == 3){
				for(int i = 0; i < dimension; ++i){
					for(int j = 0; j < dimension; ++j){
						System.out.print("please input [" + (i + 1) + ']' + '[' + (j + 1) + "]: ");
						matrix[i][j] = input.nextInt();
						System.out.println();
					}
				}
		}else{ //if dimension inputed is unaccaptable, print information
			System.out.println("The dimension is unacceptable");
		}

		if(dimension == 2){ // if the dimension is 2, calculate determinant of 2x2
			result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else if(dimension == 3){ // if the dimension is 3, calculate determinant of 3x3
			result = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
		}

		// print the determinant of the matrix
		System.out.println("Determinant: " + result);
	}
}