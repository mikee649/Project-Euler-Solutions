import java.util.HashMap;

//Michael Rokas
//May 22nd 2019

class P115 {
	private static HashMap<Integer, Long> fillCountCache;
    
    public static void main(String[] args) {
        fillCountCache = new HashMap<Integer, Long>();
        
        final int m = 50;
        int n = m;
        
        while(fillCount(m, n) < 1000000)
            n++;
            
		System.out.println(n);
	}

	private static long fillCount(int m, int n) {
		if(n < m)
			return 1;
			
		if(fillCountCache.containsKey(n))
		    return fillCountCache.get(n);

		long sum = 1;

		sum += fillCount(m, n-1);

		for(int i = m; i < n; i++)
			sum += fillCount(m, n-i-1);


        fillCountCache.put(n, sum);
		return sum;
	}
}