// Student: Haoyu Wang
// id: a1785394


// create functions to print and reverse elements

class Problem01 {  //declare calss
	public static void printArray(int [] array){ // declare method to print interger array

		System.out.print('[');

		for(int i = 0; i< array.length - 1; i++){ // print array
			System.out.print(array[i] + ",");
		}

		System.out.print(array[array.length - 1]);
		System.out.println(']');
	}

	public static void printArray(float [] array){ // declare method to print float array

		System.out.print('[');

		for(int i = 0; i< array.length - 1; i++){ // print array
			System.out.print(array[i] + ",");
		}

		System.out.print(array[array.length - 1]);
		System.out.println(']');
	}

	public static void printArray(String [] array){ // declare method to print string array

		System.out.print('[');

		for(int i = 0; i< array.length - 1; i++){ // print array
			System.out.print(array[i] + ",");
		}

		System.out.print(array[array.length - 1]);
		System.out.println(']');
	}

	public static int [] reverseArray(int [] array){ // declare method to reverse the order of the elements of interger array

		int [] arrayReversed = new int[array.length]; // create new array
		// reverse array
		for(int i = 0; i< array.length; i++){ 
			arrayReversed[arrayReversed.length - i - 1] = array[i];
		}

		return arrayReversed;
	}

	public static String [] reverseArray(String [] array){ // declare method to reverse the order of the elements of string array

		String [] arrayReversed = new String[array.length];
		// reverse array
		for(int i = 0; i< array.length; i++){
			arrayReversed[arrayReversed.length - i - 1] = array[i]; // create new array
		}

		return arrayReversed;
	}

	public static float [] reverseArray(float [] array){ // declare method to reverse the order of the elements of float array

		float [] arrayReversed = new float[array.length];
		// reverse array
		for(int i = 0; i< array.length; i++){
			arrayReversed[arrayReversed.length - i - 1] = array[i]; // create new array
		}

		return arrayReversed;
	}
}


