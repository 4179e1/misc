public class Sort {
	public static void main (String[] args) {
		int[] arrayofInt = {32, 87, 3, 589, 12, 1076, 2000, 8, 622, 127};

		for (int i = arrayofInt.length; --i > 0;) {
			for (int j = 0; j < i; j++) {
				if (arrayofInt[j] > arrayofInt[j+1]){
					int temp = arrayofInt[j];
					arrayofInt[j] = arrayofInt[j+1];
					arrayofInt[j+1] = temp;
				}
			}
		}

		for (int i =0; i < arrayofInt.length; i++) {
			System.out.print (arrayofInt[i] + "\t");
		}
		System.out.println();
	}
}
