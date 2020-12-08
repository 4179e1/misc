interface ComputerWeight {
	public double computeWeight();
}

class Television implements ComputerWeight {
	public double computeWeight() {
		return 45.5;
	}
}

class Computer implements ComputerWeight {
	public double computeWeight() {
		return 65.5;
	}
}

class WashMachine implements ComputerWeight {
	public double computeWeight() {
		return 145;
	}
}

class Car {
	ComputerWeight[] goods;
	double totalWeights = 0;

	Car(ComputerWeight[] goods) {
		this.goods = goods;
	}

	public double getTotalWeights() {
		totalWeights = 0;
		for (int k = 0; k < goods.length; k++) {
			totalWeights = totalWeights + goods[k].computeWeight();
		}
		return totalWeights;
	}
}

public class Road {
	public static void main(String args[]) {
		ComputerWeight[] goodsOne = new ComputerWeight[50], goodsTwo = new ComputerWeight[22];
		for (int i = 0; i < goodsOne.length; i++) {
			if (i % 3 == 0)
				goodsOne[i] = new Television();
			else if (i % 3 == 1)
				goodsOne[i] = new Computer();
			else if (i % 3 == 2)
				goodsOne[i] = new WashMachine();
		}
		for (int i = 0; i < goodsTwo.length; i++) {
			if (i % 3 == 0)
				goodsTwo[i] = new Television();
			else if (i % 3 == 1)
				goodsTwo[i] = new Computer();
			else if (i % 3 == 2)
				goodsTwo[i] = new WashMachine();
		}
		Car 大货车 = new Car(goodsOne);
		System.out.println("大货车装载的货物重量:" + 大货车.getTotalWeights());
		Car 小货车 = new Car(goodsTwo);
		System.out.println("小货车装载的货物重量:" + 小货车.getTotalWeights());
	}
}
