abstract class Abs {
	public abstract void f (int x);
	public abstract void g (int x, int y);
	public abstract double h (double x);
}

class child1 extends Abs {
	public void f (int x) {
		System.out.println ("child1: x = " + x);
	}

	public void g (int x, int y) {
		System.out.println ("child1: x = " + x + " y = " + y);
	}

	public double h (double x) {
		System.out.println ("child1: x = " + x);
		return x;
	}
}

class child2 extends Abs {
	public void f (int x) {
		System.out.println ("child2: x = " + x);
	}

	public void g (int x, int y) {
		System.out.println ("child2: x = " + x + " y = " + y);
	}

	public double h (double x) {
		System.out.println ("child2: x = " + x);
		return x;
	}
}

class child3 extends Abs {
	public void f (int x) {
		System.out.println ("child3: x = " + x);
	}

	public void g (int x, int y) {
		System.out.println ("child3: x = " + x + " y = " + y);
	}

	public double h (double x) {
		System.out.println ("child3: x = " + x);
		return x;
	}
}

public class test2 {
	public static void main (String[] args) {
		Abs a;
		a = new child1();
		a.f(1);
		a.g(1, 2);
		a.h(3.0);

		a = new child2();
		a.f(1);
		a.g(1, 2);
		a.h(3.0);

		a = new child3();
		a.f(1);
		a.g(1, 2);
		a.h(3.0);
	}
}

