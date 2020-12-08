import java.util.regex.*;

public class test {
	public static void main (String args[]) {
		if (args.length != 1) {
			System.out.println ("Useage: programmname string-to-match");
			return;
		}
		Pattern p;
		Matcher m;
		p = Pattern.compile ("\\d");
		m = p.matcher (args[0]);
		while (m.find()) {
			String str = m.group ();
			System.out.print (str);
		}
		System.out.println();
	}
}
