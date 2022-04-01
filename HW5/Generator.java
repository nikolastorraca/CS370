import java.util.Random;

public class Generator extends java.lang.Thread {

	Random randomWithSeed;
	Buffer buff;
	int count;
	int id;
	int primeSeed;
	static int sumOfPrimes = 0;

	public Generator(Buffer buff, int count, int id, int primeSeed) {

		randomWithSeed = new Random(primeSeed);
		this.buff = buff;
		this.count = count;
		this.id = id;
		this.primeSeed = primeSeed;
	}

	@Override
	public void run()  {

		// Thread needs to add 'count' items to the buffer
		for(int i = 0; i<count; i++){
		
			try {
				int randomN = randomWithSeed.nextInt(31-3+1) + 3;
				int randomPrime = findNthPrime(randomN);
				addToBuffer(randomPrime);
			}
			catch(InterruptedException ie) {
				break;
			}	
		}
	}

	private void addToBuffer(int randomPrime) 
	throws InterruptedException {
		
		synchronized(buff) {

			// while buffer is full, wait for consumer to consume an item
			while(buff.capacity() == buff.size()) {
				buff.wait();
			}

			// add item to buffer, print data and call notifyAll to notify consumer threads that an item has been added to the buffer
			buff.add(randomPrime);
			sumOfPrimes += randomPrime;
			System.out.println("\033[0;4m[Generator " + id + "]: inserted " + randomPrime + " at index " + buff.genIndex() + " at time\033[0;0m " + Coordinator.getTime());
			buff.notifyAll();
		}
	}

	private int findNthPrime(int randomN) {
		
		int nthPrime = 1;
		int count = 0;
		int i;
		while(count < randomN) {
			nthPrime += 1;
			for(i = 2; i <= nthPrime; i++) {
				if(nthPrime % i == 0) {
					break;
				}
			}
			if (i == nthPrime)
				count++;
		}
		return nthPrime;
	}

	public static int getSumOfConsumedPrimes() {

		return sumOfPrimes;
	}
}
