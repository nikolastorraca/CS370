import java.util.Random;

public class Consumer extends java.lang.Thread {

	Buffer buff;
	int sumOfPrimes;
	int count;
	int id;
	int primeSeed;

	public Consumer(Buffer buff, int count, int id) {

		this.buff = buff;
		this.count = count;
		this.id = id;
	}

	@Override
	public void run()  {

		for(int i = 0; i<count; i++){
			
			try {
				consumeFromBuffer();
			}
			catch(InterruptedException ie) {
				break;
			}	
		}
    }

	public synchronized void consumeFromBuffer() 
	throws InterruptedException {
		
		while(buff.isEmpty()) {
			this.wait();
		}
		int randomPrime = (int)buff.get();
		System.out.println("[Generator " + id + "]: inserted " + randomPrime + " at index " + "TODO" + " at time " + Coordinator.getTime());
		this.notify();
	}
}