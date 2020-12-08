import java.util.*;

class MyKey implements Comparable {
	int number = 0;
	MyKey (int number) {
		this.number = number;
	}
	public int compareTo (Object b) {
		MyKey st = (MyKey) b;
		if ((this.number - st.number) == 0) {
			return -1;
		}
		else {
			return (this.number - st.number);
		}
	}
}

class Hd {
	String name = null;
	int price, size;

	Hd (int p, int s, String name) {
		price = p;
		size = s;
		this.name = name;
	}
}

public class test {
	public static void main (String[] args) {
		Hd hd1 = new Hd(100, 20, "HD1");
		Hd hd2 = new Hd(20, 100, "HD2");
		Hd hd3 = new Hd(30, 90, "HD3");
		Hd hd4 = new Hd(40, 80, "HD4");
		Hd hd5 = new Hd(50, 70, "HD5");
		Hd hd6 = new Hd(60, 60, "HD6");
		Hd hd7 = new Hd(70, 50, "HD7");
		Hd hd8 = new Hd(80, 40, "HD8");
		Hd hd9 = new Hd(90, 30, "HD9");
		Hd hd10 = new Hd(100, 100, "HD10");

		TreeMap<MyKey, Hd> treemap = new TreeMap<MyKey, Hd>();

		treemap.put(new MyKey(hd1.price), hd1);
		treemap.put(new MyKey(hd2.price), hd2);
		treemap.put(new MyKey(hd3.price), hd3);
		treemap.put(new MyKey(hd4.price), hd4);
		treemap.put(new MyKey(hd5.price), hd5);
		treemap.put(new MyKey(hd6.price), hd6);
		treemap.put(new MyKey(hd7.price), hd7);
		treemap.put(new MyKey(hd8.price), hd8);
		treemap.put(new MyKey(hd9.price), hd9);
		treemap.put(new MyKey(hd10.price), hd10);
		Collection<Hd> collection = treemap.values();
		Iterator<Hd> iter = collection.iterator();
		System.out.println("按价格排列:");
		while(iter.hasNext()) {
			Hd te = iter.next();
			System.out.printf ("%s, %d\n", te.name, te.price);
		}
		System.out.println();

		treemap.clear();
		treemap.put(new MyKey(hd1.size), hd1);
		treemap.put(new MyKey(hd2.size), hd2);
		treemap.put(new MyKey(hd3.size), hd3);
		treemap.put(new MyKey(hd4.size), hd4);
		treemap.put(new MyKey(hd5.size), hd5);
		treemap.put(new MyKey(hd6.size), hd6);
		treemap.put(new MyKey(hd7.size), hd7);
		treemap.put(new MyKey(hd8.size), hd8);
		treemap.put(new MyKey(hd9.size), hd9);
		treemap.put(new MyKey(hd10.size), hd10);
		collection = treemap.values();
		iter = collection.iterator();
		System.out.println("按价格排列:");
		while(iter.hasNext()) {
			Hd te = iter.next();
			System.out.printf ("%s, %d\n", te.name, te.size);
		}
		System.out.println();
	}

}
