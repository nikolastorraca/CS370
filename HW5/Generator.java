import java.util.Random;

public class Generator extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;
	Buffer buff;
	int sumOfPrimes;
	int count;
	int id;
	int primeSeed;

	public Generator(Buffer buff, int count, int id, int primeSeed) {
		//Assign values to the variables
		randomWithSeed = new Random(primeSeed);
		this.buff = buff;
		this.count = count;
		this.id = id;
		this.primeSeed = primeSeed;
	}

	@Override
	public void run()  {
		/* 
		Insert the N-th prime to the buffer as much as the count.
        The random number N is produced by random generator. Check the range in the HW description.
        You can generate a random number in range [1, 10] as:
        int randomN = randomWithSeed.nextInt(10-1+1) + 1;
		*/
		while(buff.capacity() == buff.size()) {
			wait();
		}
		int randomN = randomWithSeed.nextInt(31-3+1) + 3;
		int randomPrime = findNthPrime(randomN);
		for(int i = 0; i<count; i++){
			buff.add(randomPrime);
			notify();
		}
		
			
			

	}

	public int findNthPrime(int randomN) {
		return 0;
	}
}
