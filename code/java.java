import java.io.*;
import java.util.*;
import java.math.*;
public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		int tests = in.nextInt();
		for (int noT = 1; noT <= tests && in.hasNext(); ++noT) (new Task()).solve(noT, in, out);
		out.close();
	}
}
class Task { 
	public void solve(int testNumber, InputReader in, PrintWriter out) { 
		// Implementation here.
	} 
}
class InputReader {
	BufferedReader reader;
	StringTokenizer tokenizer;
	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}
	public boolean hasNext() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) {
				return false;
			}
		}
		return tokenizer.hasMoreTokens();
	}
	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}
}