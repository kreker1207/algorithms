import java.util.Scanner;
public class lab9 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		System.out.print("Input a number 1<n<256: ");
		int n = input.nextInt();
		activity[] a = new activity[n];
		for (int i = 0; i < a.length; i++) {
			int k = i+1;
			a[i] = new activity(0,0);
			System.out.print("Input start of the "+k+" activity: ");
			a[i].start = input.nextInt();
			System.out.print("Input end of the "+k+" activity: ");
			a[i].end = input.nextInt();
		}
		boolean it = true;
		int temp;
		while (it) {
			it = false;
			for (int i = 1; i < a.length; i++) {
				if (a[i].end < a[i - 1].end) {
					temp = a[i].end;
					a[i].end = a[i-1].end;
					a[i-1].end = temp;
					temp = a[i].start;
					a[i].start = a[i-1].start;
					a[i-1].start = temp;
					it = true;
				}
		}
	}
		System.out.println("Activities, sorted by end time:");
		for (int i = 0; i < a.length; i++) System.out.println("activity "+(i+1)+" (start) = "+a[i].start+", activity "+(i+1)+" (end) = "+a[i].end);
		int[] sa = new int[n];
		int p = 1, count = 0;
		while(p<n) {
			if (a[p].end != 0){
				for(int i = p; i < a.length; i++) {
					if(a[p-1].end > a[i].start && a[i].start != 0) {
						a[i].start = 0;
						a[i].end = 0;
					}
				}
			}
			p++;
		}
		for (int i = 0; i < a.length; i++) if(a[i].start != 0) count++;
		System.out.println(count);
}
}
class activity {
	int start;
	int end;
	{
		start = 0;
		end = 0;
	}
	public activity (int start, int end) {
		this.start = start;
		this.end = end;
	}
}
