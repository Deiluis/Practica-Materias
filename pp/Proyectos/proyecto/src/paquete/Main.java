package paquete;

public class Main {
	
	public static void main(String[] args) {

		int m[][] = {
			{1,2,3},
			{4,0,6},
			{7,8,9}
		};
		
		
		// System.out.println("La multiplicación de los elementos de m " + (esMultElemNula(m) ? "es nula." : "no es nula."));
		diagonales(m);
	}
	
	public static boolean esMultElemNula (int[][] m) {
		
		boolean nula = false;
		
		for (int i = 0; i < m.length && !nula; i++) {
			for (int j = 0; j < m[0].length && !nula; j++) {
				if (m[i][j] == 0)
					nula = true;
			}
		}
			
		return nula;
	}
	
	public static void diagonales (int[][] m) {

		for (int i = m.length -1; i >= 0; i--) {
			for (int j = 0; j < m.length - i; j++) {
				System.out.print(m[i+j][j] + " ");
			}
			System.out.println();
		}
		
		for (int j = 1; j < m.length; j++) {
			for (int i = 0; i < m.length - j; i++) {
				System.out.print(m[i][i+j] + " ");
			}
			System.out.println();
		}
		
	}
}