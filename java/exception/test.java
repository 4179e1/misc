class MyException extends Exception {
	String message;
	MyException (int n) {
		message =  "Error: m > 1000";
	}

	public String getMessage() {
		return message;
	}
}

class Student {
	public void speak (int m) throws MyException {
		if (m > 1000) {
			MyException ex = new MyException(m);
			throw (ex);
		}
		System.out.println ("m = " + m);
	}
}

public class test {
	public static void main (String args[]) {
		Student s = new Student();
		try {
			s.speak (999);
			s.speak (1000);
			s.speak (1001);
		} catch (MyException e) {
			System.out.println (e.getMessage());
		}
	}
}
