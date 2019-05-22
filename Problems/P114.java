import java.util.HashMap;

//Michael Rokas
//May 22nd 2019

class P114 {
	private static HashMap<Integer, Long> numCombosCache;
    
    public static void main(String[] args) {
        numCombosCache = new HashMap<Integer, Long>();
        
		System.out.println(numCombos(50));
	}

	private static long numCombos(int spaces) {
		if(spaces < 3)
			return 1;
			
		if(numCombosCache.containsKey(spaces))
		    return numCombosCache.get(spaces);

		long sum = 1;

		sum += numCombos(spaces-1);

		for(int i = 3; i < spaces; i++)
			sum += numCombos(spaces-i-1);


        numCombosCache.put(spaces, sum);
		return sum;
	}
}