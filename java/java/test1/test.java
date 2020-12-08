import java.util.regex.*;

public class test {
	public static void main (String args[]) {
		if (args.length != 1) {
			System.out.println ("Useage: programmname string-to-match");
			return;
		}
		Pattern p;
		Matcher m;
		p = Pattern.compile ("[24680]A[13579]{2}");
		m = p.matcher (args[0]);
		while (m.find()) {
			String str = m.group ();
			System.out.print ("从" + m.start() + "到" + m.end() + "匹配模式子序列：");
			System.out.println (str);
		}
	}
}
