class People {
	protected double weight, height;

	public void speakHello() {
		System.out.println("yayawawa");
	}

	public void averageHeight() {
		height = 173;
		System.out.println("average height:" + height);
	}

	public void averageWeight() {
		weight = 70;
		System.out.println("average weight:" + weight);
	}
}

class ChinaPeople extends People {
	public void speakHello() {
		System.out.println("你好,吃饭了吗?");
	}

	public void averageHeight() {
		height = 173;
		System.out.println("中国人的平均身高：" + height + "厘米");
	}

	public void averageWeight() {
		weight = 67.34;
		System.out.println("中国人的平均体重：" + weight + "公斤");
	}

	public void chinaGongfu() {
		System.out.println("坐如钟,站如松,睡如弓");
	}
}

class AmericanPeople extends People {
	public void speakHello() {
		System.out.println("How do You do");
	}

	public void averageHeight() {
		height = 188;
		System.out.println("Amerian Average height:" + height + " cm");
	}

	public void averageWeight() {
		weight = 80.23;
		System.out.println("Amerian Average weight:" + weight + " kg");
	}

	public void americanBoxing() {
		System.out.println("直拳、钩拳");
	}
}

class BeijingPeople extends ChinaPeople {
	public void speakHello() {
		System.out.println("您好");
	}

	public void averageHeight() {
		height = 16;
		System.out.println("北京人的平均身高：" + height + "厘米");
	}

	public void averageWeight() {
		weight = 6;
		System.out.println("北京人的平均体重：" + weight + "公斤");
	}

	public void beijingOpera() {
		System.out.println("京剧术语");
	}
}

public class Example {
	public static void main(String args[]) {
		ChinaPeople chinaPeople = new ChinaPeople();
		AmericanPeople americanPeople = new AmericanPeople();
		BeijingPeople beijingPeople = new BeijingPeople();
		chinaPeople.speakHello();
		americanPeople.speakHello();
		beijingPeople.speakHello();
		chinaPeople.averageHeight();
		americanPeople.averageHeight();
		beijingPeople.averageHeight();
		chinaPeople.averageWeight();
		americanPeople.averageWeight();
		beijingPeople.averageWeight();
		chinaPeople.chinaGongfu();
		americanPeople.americanBoxing();
		beijingPeople.beijingOpera();
		beijingPeople.chinaGongfu();
	}
}
