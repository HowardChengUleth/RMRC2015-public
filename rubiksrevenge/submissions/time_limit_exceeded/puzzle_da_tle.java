import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

public class puzzle_da_tle {

	private static final int N = 4;
	private static final int SHIFT = 2;
	private static final int MASK = 3;

	private static final String colors = "RGBY";

	private int[][] g;
	private Map<Integer, Integer> seen;
	private Queue<Integer> q;

	private int solvedCode;

	public puzzle_da_tle() {
		g = new int[N][N];
		seen = new HashMap<Integer, Integer>();
		q = new LinkedList<Integer>();

		solvedCode = 0;
		for (int row = 1; row < N; row++) {
			for (int col = 0; col < N; col++) {
				solvedCode <<= SHIFT;
				solvedCode |= row;
			}
		}
	}

	private int encode() {
		int code = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				code <<= SHIFT;
				code |= g[i][j];
			}
		}
		return code;
	}

	private void decode(int code) {
		for (int i = N - 1; i >= 0; i--) {
			for (int j = N - 1; j >= 0; j--) {
				g[i][j] = code & MASK;
				code >>= SHIFT;
			}
		}
	}

	/**
	 * Make a move in-place
	 * 
	 * @param idx
	 *            Index of the row or column
	 * @param type
	 *            row(0) or column(1)
	 * @param dir
	 *            right/down (0) or left/up(1)
	 */
	private void move(int idx, int type, int dir) {
		if (type == 0) {
			if (dir == 0) {
				int saved = g[idx][N - 1];
				for (int col = N - 1; col > 0; col--) {
					g[idx][col] = g[idx][col - 1];
				}
				g[idx][0] = saved;
			} else {
				int saved = g[idx][0];
				for (int col = 0; col < N - 1; col++) {
					g[idx][col] = g[idx][col + 1];
				}
				g[idx][N - 1] = saved;
			}
		} else {
			if (dir == 0) {
				int saved = g[N - 1][idx];
				for (int row = N - 1; row > 0; row--) {
					g[row][idx] = g[row - 1][idx];
				}
				g[0][idx] = saved;
			} else {
				int saved = g[0][idx];
				for (int row = 0; row < N - 1; row++) {
					g[row][idx] = g[row + 1][idx];
				}
				g[N - 1][idx] = saved;
			}
		}
	}

	private int solve(int code) {

		seen.clear();
		q.clear();

		seen.put(code, 0);
		q.add(code);
		while (!q.isEmpty()) {
			code = q.poll();
			int moves = seen.get(code);
			if (code == solvedCode)
				return moves;

			decode(code);
			for (int idx = 0; idx < N; idx++) {
				for (int type = 0; type < 2; type++) {
					for (int dir = 0; dir < 2; dir++) {
						move(idx, type, dir);
						int nextCode = encode();
						move(idx, type, 1 - dir);
						if (!seen.containsKey(nextCode)) {
							seen.put(nextCode, moves + 1);
							q.add(nextCode);
						}
					}
				}
			}
		}

		return -1;

	}

	private void printErrorAndExit(Scanner sc, String msg) {
		sc.close();
		System.err.println(msg);
		System.exit(-1);
	}

	private void work() {
		Scanner sc = new Scanner(System.in);
		int code = 0;
		for (int i = 0; i < N; i++) {
			char[] ca = sc.next().toCharArray();
			if (ca.length != N) {
				printErrorAndExit(sc, String.format(
						"Expected %d characters but got %d", N, ca.length));
			}
			for (int j = 0; j < N; j++) {
				code <<= SHIFT;
				int color = colors.indexOf(ca[j]);
				if (color < 0) {
					printErrorAndExit(sc,
							String.format("Unexpected color |%c|", ca[j]));
				}
				code |= color;
			}
		}
		System.out.println(solve(code));
		sc.close();
	}

	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		new puzzle_da_tle().work();
		long t = System.currentTimeMillis() - startTime;
		System.err.printf("Elapsed time: %02d:%02d:%02d.%03d\n",
				t / 1000 / 3600, ((t / 1000) % 3600) / 60, (t / 1000) % 60,
				t % 1000);
	}

}
