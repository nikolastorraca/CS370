
public class Consumer extends java.lang.Thread {

	Buffer buff;
	static int sumOfPrimes = 0;
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
				System.out.println("In Consumer try block");
				consumeFromBuffer();
			}
			catch(InterruptedException ie) {
				break;
			}	
		}
    }

	private void consumeFromBuffer() 
	throws InterruptedException {
		
		synchronized(buff) {
			System.out.println("In comsumeFromBuffer method");
			while(buff.isEmpty()) {
				System.out.println("Buff is empty. " + Thread.currentThread().getName() + " is waiting.");
				buff.wait();
			}
			//Thread.sleep(1000);
			System.out.println("Made it past waiting (consumer)");
			int randomPrime = (int)buff.get();
			sumOfPrimes += randomPrime;
			System.out.println("[Consumer " + id + "]: consumed " + randomPrime + " at index " + "TODO" + " at time " + Coordinator.getTime());
			buff.notifyAll();
		}
	}

	public static int getSumOfConsumedPrimes() {
		return sumOfPrimes;
	}
}