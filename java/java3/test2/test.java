import java.util.*;

public class test {
	public static void main (String[] args) {
		if (args.length != 6) {
			System.out.println ("Useage: progammname y1 m1 d1 y2 m2 d2");
			return;
		}

      int yearOne=Integer.parseInt(args[0]);
      int monthOne=Integer.parseInt(args[1]);
      int dayOne=Integer.parseInt(args[2]);
      int yearTwo=Integer.parseInt(args[3]);
      int monthTwo=Integer.parseInt(args[4]);
      int dayTwo=Integer.parseInt(args[5]);
      Calendar calendar= Calendar.getInstance();
      calendar.set (yearOne, monthOne, dayOne); 

      long timeOne=calendar.getTimeInMillis() ;
      calendar.set (yearTwo, monthTwo, dayTwo);
      long timeTwo= calendar.getTimeInMillis() ;

      long days= (timeTwo - timeOne) / (1000*60*60*24);
      System.out.println(yearOne+"年"+monthOne+"月"+dayOne+"日和"
                         +yearTwo+"年"+monthTwo+"月"+dayTwo+"相隔"+days+"天");
	}
}
