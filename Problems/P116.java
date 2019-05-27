import java.util.HashMap;

//Michael Rokas
//May 27th 2019

class P116 {
	private static HashMap<String, Long> numWaysCache;

	public static void main(String[] args) {
		numWaysCache = new HashMap<String, Long>();

		long sum = numWays(50, 2, false) + numWays(50, 3, false) + numWays(50, 4, false);
		System.out.println(sum);
	}

	private static long numWays(int numSquares, int tileLength, boolean tileUsed) {
		if(tileLength >  numSquares)
			return tileUsed ? 1 : 0;

		String key = numSquares + "," + tileLength + "," + tileUsed;

		if(numWaysCache.containsKey(key))
			return numWaysCache.get(key);

		long val = numWays(numSquares-1, tileLength, tileUsed) + numWays(numSquares-tileLength, tileLength, true);
		numWaysCache.put(key, val);

		return val;
	}
}