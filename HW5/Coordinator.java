import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;
import java.io.*;

class Coordinator {
	public static void main(String[] args) throws InterruptedException {


		if(args.length != 2) {
			System.out.println("Please run program again with 2 agruments.");
			System.exit(0);
		}

	    int seed = Integer.parseInt((args[0]));
	    int primeSeed = Integer.parseInt((args[1]));
	
		Random randomWithSeed = new Random(seed);
		int buffSize = randomWithSeed.nextInt(10-5+1) + 5;
		int numItems = randomWithSeed.nextInt(30-10+1) + 10;
		int numConsumers = randomWithSeed.nextInt(5-2+1) + 2;
		int numGenerators = randomWithSeed.nextInt(5-2+1) + 2;
        Buffer myBuffer = new Buffer(buffSize);

		System.out.println("[Coordinator] Buffer Size: " + buffSize);
		System.out.println("[Coordinator] Total Items: " + numItems);
		System.out.println("[Coordinator] No. of Generators: " + numGenerators);
		System.out.println("[Coordinator] No. of Consumers: " + numConsumers);

		// calculate how much data each generator needs to produce
		int genCount = numItems/numGenerators;
		int genRemainder = numItems%numGenerators;
		int genCountLast;
		if(genRemainder != 0)
			genCountLast = genCount + genRemainder;
		else
			genCountLast = genCount;

		// calculate how much data each consumer needs to consume
		int conCount = numItems/numConsumers;
		int conRemainder = numItems%numConsumers;
		int conCountLast;
		if(conRemainder != 0)
			conCountLast = conCount + conRemainder;
		else
			conCountLast = conCount;

	    // Create/Start Generator threads
        Generator[] genThreads = new Generator[numGenerators];
        for(int i = 0; i < numGenerators-1; i++) 
            genThreads[i] = new Generator(myBuffer, genCount, (i+1), primeSeed);  
		
		genThreads[numGenerators-1] = new Generator(myBuffer, genCountLast, (numGenerators+1), primeSeed);
		
		for(int i = 0; i < numGenerators; i++)
			genThreads[i].start();

		// Create/Start Generator threads
		Consumer[] conThreads = new Consumer[numConsumers];
		for(int i = 0; i < numConsumers-1; i++)
			conThreads[i] = new Consumer(myBuffer, conCount, (i+1));
		
	    conThreads[numConsumers-1] = new Consumer(myBuffer, conCountLast, (numConsumers+1));

		for(int i = 0; i < numConsumers; i++)
			conThreads[i].start();

		// Wait for threads to terminate...
		for(int i = 0; i < numGenerators; i++)
			genThreads[i].join();

		for(int i = 0; i < numConsumers; i++)
			conThreads[i].join();


		if(Generator.getSumOfConsumedPrimes() == Consumer.getSumOfConsumedPrimes())
			System.out.println("The generated & consumed sums of primes are the same as shown: " + Generator.getSumOfConsumedPrimes());
		else
			System.out.println("Whoops! The generated & consumed sums are not the same...");
	}

	public static String getTime() {
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}