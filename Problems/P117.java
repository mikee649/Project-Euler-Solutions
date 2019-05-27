import java.util.HashMap;

//Michael Rokas
//May 27th 2019

class P117 {
	private static HashMap<Integer, Long> numWaysCache;

	public static void main(String[] args) {
		numWaysCache = new HashMap<Integer, Long>();
		System.out.println(numWays(50));
	}

	private static long numWays(int numSquares) {
		if(numSquares == 0)
			return 1;
		if (numSquares < 0 )
			return 0;

		if(numWaysCache.containsKey(numSquares))
			return numWaysCache.get(numSquares);

		long val = numWays(numSquares-1) + numWays(numSquares-2) + numWays(numSquares-3) + numWays(numSquares-4);
		numWaysCache.put(numSquares, val);

		return val;
	}
}