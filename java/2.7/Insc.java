public class Insc {
	public static void main (String[] args) {
		System.out.println ("StaticInt.i = " + StaticInt.i);
		StaticInt si1 = new StaticInt();
		StaticInt si2 = new StaticInt();
		System.out.println ("si1.i = " + si1.i);
		System.out.println ("si2.i = " + si2.i);
		Increme.increment();
		System.out.println ("After Increme.increment called: ");
		System.out.println ("si1.i = " + si1.i);
		System.out.println ("si2.i = " + si2.i);
		si1.i = 3;
		System.out.println ("After st1.i = 3");
		System.out.println ("si1.i = " + si1.i);
		System.out.println ("si2.i = " + si2.i);
		System.out.println ("Create another StaticInt si3");
		StaticInt si3 = new StaticInt();
		System.out.println ("si3.i = " + si3.i);
	}
}

class StaticInt {
	static int i = 11;
}

class Increme {
	static void increment() {
		StaticInt.i++;
	}
}
