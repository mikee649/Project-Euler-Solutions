import java.util.regex.*;  

//Michael Rokas
//May 21st 2019

class P206 {
	public static void main(String[] args) {
		long i = 1010101010;	//sqrt(1020304050607080900)

		String regex = "1\\d2\\d3\\d4\\d5\\d6\\d7\\d8\\d9\\d0";

		while(!Pattern.matches(regex, "" + i*i))
			i += 10;	//increase by 10 becasause the final number
						//will have to be divisible by 10

		System.out.println(i);
	}
}