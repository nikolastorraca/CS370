import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;
import java.io.*;

class Coordinator {
	public static void main(String[] args) {

		if(args.length != 2) {
			System.out.println("Please run program again with 2 agruments.");
		}

	    int seed = Integer.parseInt((args[0]));
	    int primeSeed = Integer.parseInt((args[1]));
	
		Random randomWithSeed = new Random(seed);
		int buffSize = randomWithSeed.nextInt(10-5+1) + 5;
		int numItems = randomWithSeed.nextInt(30-10+1) + 10;
		int numConsumers = randomWithSeed.nextInt(5-2+1) + 2;
		int numGenerators = randomWithSeed.nextInt(5-2+1) + 2;
        Buffer myBuffer = new Buffer(buffSize);

		int count = numItems/numGenerators;
		int remainder = numItems%numGenerators;
		int countLast;
		if(remainder != 0)
			countLast = count + remainder;
		else
			countLast = count;

	    // Create/Start Generator threads
        Generator[] genThreads = new Generator[numGenerators];
        for(int i = 0; i < numGenerators-1; i++) 
            genThreads[i] = new Generator(myBuffer, count, (i+1), primeSeed);  
		
		genThreads[numGenerators-1] = new Generator(myBuffer, countLast, (numGenerators+1), primeSeed);
		
		for(int i = 0; i < numGenerators; i++)
			genThreads[i].start();

		// Create/Start Generator threads
		Consumer[] conThreads = new Consumer[numConsumers];
		for(int i = 0; i < numConsumers-1; i++)
			conThreads[i] = new Consumer(myBuffer, count, (i+1));
		
	    conThreads[numConsumers-1] = new Consumer(myBuffer, countLast, (numConsumers+1));

		for(int i = 0; i < numConsumers; i++)
			conThreads[i].start();

		// TODO: When threads terminate, make final calculations

	}

	//Call this function from your generator or your consumer to get the time stamp to be displayed
	public static String getTime() {
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}