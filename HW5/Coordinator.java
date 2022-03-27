import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;
import java.io.*;

class Coordinator {
	public static void main(String[] args) {


		int primeSeed = Integer.parseInt((args[0]));
		System.out.println(primeSeed);
		Random randomWithSeed = new Random(primeSeed);
		int buffSize = randomWithSeed.nextInt(10-5+1) + 5;
		int numItems = randomWithSeed.nextInt(30-10+1) + 10;
		int numConsumers = randomWithSeed.nextInt(5-2+1) + 2;
		int numGenerators = randomWithSeed.nextInt(5-2+1) + 2;
		System.out.println(buffSize);
		System.out.println(numItems);
		System.out.println(numConsumers);
		System.out.println(numGenerators);
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