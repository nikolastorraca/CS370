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
				System.out.println("In Generator Try block");
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
			System.out.println("In addToBuffer method");
			while(buff.capacity() == buff.size()) {
				System.out.println("Buffer is full " + Thread.currentThread().getName() + " is waiting");
				buff.wait();
			}
			//Thread.sleep(1000);
			System.out.println("Made it past the waiting (Gen)");
			buff.add(randomPrime);
			sumOfPrimes += randomPrime;
			System.out.println("[Generator " + id + "]: inserted " + randomPrime + " at index " + "TODO" + " at time " + Coordinator.getTime());
			buff.notifyAll();
		}
	}

	public int findNthPrime(int randomN) {
		
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
		System.out.println("The " + randomN +"th prime num is: " + nthPrime);
		return nthPrime;
	}

	public static int getSumOfConsumedPrimes() {
		return sumOfPrimes;
	}
}
