public class Storage {
	public static void main (String[] args) {
		class StoreStuff {
			int store (String s) {
				return s.length();
			}
		}
		StoreStuff x = new StoreStuff();
		System.out.println (x.store("abc"));
	}
}
