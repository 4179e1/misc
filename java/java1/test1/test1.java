class Parent {
	public int f(int a, int b) {
		int var1 = 0;
		int var2 = 0;
		int temp = 0;

		if (a > b) {
			temp = a;
			a = b;
			b = temp;
		}

		var1 = a;
		var2 = b;

		while (var2 != 0)
		{
			temp = var1 % var2;
			var1 = var2;
			var2 = temp;
		}

		return var1;
	}
}

class Child extends Parent {
	public int f (int a, int b) {
		int m = super.f(a, b);
		return ((a*b) / m);
	}
}

public class test1 {
	public static void main (String[] args) {
		Parent p = new Parent();
		System.out.println ("The GCD of 4 and 6 is " + p.f(4, 6));
		Child c = new Child();
		System.out.println ("The LCM of 4 and 6 is "+c.f(4, 6));
	}
}
