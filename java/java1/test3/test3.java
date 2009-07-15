interface Itf {
	public abstract void f (int x);
	public abstract void g (int x, int y);
	public abstract double h (double x);
}

class child1 implements Itf {
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

public class test3 {
	public static void main (String[] args) {
		Itf i;
		i = new child1();
		i.f(1);
		i.g(1, 2);
		i.h(3.0);
	}
}

