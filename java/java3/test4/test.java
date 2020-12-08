import java.util.*;

public class test {
	public static void main (String[] args) {
		HashSet<Integer> A = new HashSet<Integer>(),
						B = new HashSet<Integer>();
		HashSet<Integer> temp1 = new HashSet<Integer>();
		HashSet<Integer> temp2 = new HashSet<Integer>();

		A.add(1);
		A.add(2);
		A.add(3);
		A.add(4);
		B.add(1);
		B.add(3);
		B.add(7);
		B.add(9);
		B.add(11);

		temp1 = (HashSet<Integer>)A.clone();
		temp2 = (HashSet<Integer>)B.clone();
		temp1.retainAll(temp2);
		System.out.print ("A与B的交集为：");
		Iterator<Integer> iter = temp1.iterator();
		while (iter.hasNext()) {
			Integer te = iter.next();
			System.out.printf ("%d, ", te.intValue());
		}
		System.out.println();

		temp1 = (HashSet<Integer>)A.clone();
		temp2 = (HashSet<Integer>)B.clone();
		temp1.addAll(temp2);
		System.out.print ("A与B的并集为：");
		iter = temp1.iterator();
		while (iter.hasNext()) {
			Integer te = iter.next();
			System.out.printf ("%d, ", te.intValue());
		}
		System.out.println();

		temp1 = (HashSet<Integer>)A.clone();
		temp2 = (HashSet<Integer>)B.clone();
		temp1.removeAll(temp2);
		System.out.print ("A与B的差集为：");
		iter = temp1.iterator();
		while (iter.hasNext()) {
			Integer te = iter.next();
			System.out.printf ("%d, ", te.intValue());
		}
		System.out.println();
	}
}
