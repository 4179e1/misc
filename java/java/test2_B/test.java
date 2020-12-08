import java.util.*;
public class test{
	public static void main (String[] args) {
		if (args.length != 1) {
			System.out.println ("Useage: programmname string-to-match");
			return;
		}
		String s = new String (args[0]);
		char[] a = s.toCharArray ();
		int index = 0;
		for(int i = 0; i<a.length; i++) {
			if (Character.isDigit (a[i])) {
				System.out.print (a[i]);
			}

		}
		System.out.println ();
	}

}
