
public class Consumer extends java.lang.Thread {

	Buffer buff;
	static int sumOfPrimes = 0;
	int count;
	int id;

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

	private void consumeFromBuffer() 
	throws InterruptedException {
		
		synchronized(buff) {

			// while buffer is empty, wait for a Generator to add an item to the buffer
			while(buff.isEmpty()) {
				buff.wait();
			}

			// remove item from buffer, print data and notifyAll to notify Generator threads that an item has been consumed from the buffer
			int randomPrime = (int)buff.get();
			sumOfPrimes += randomPrime;
			System.out.println("[Consumer " + id + "]: consumed " + randomPrime + " at index " + buff.conIndex() + " at time " + Coordinator.getTime());
			buff.notifyAll();
		}
	}

	public static int getSumOfConsumedPrimes() {
		
		return sumOfPrimes;
	}
}