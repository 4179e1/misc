public class Rainbow {
	public static void main (String[] args) {
		COR atc = new COR();
		System.out.println ("atc.IRC = " + atc.IRC);
		atc.changeColor(7);
		atc.changeHue(77);
		System.out.println ("After change, atc.IRC = " + atc.IRC);
		System.out.println ("atc.hue = " + atc.hue);
	}
}

class COR {
	int IRC = 0;
	int hue = 0;
	void changeHue (int newHue) {
		hue = newHue;
	}
	int changeColor (int newColor) {
		return IRC = newColor;
	}
}
