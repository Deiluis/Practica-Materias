package paquete;

public class Main {
	public static void main(String[] args) {
		
		ContadorGanado contadorGanado = new ContadorGanado();
		
		for (int i = 0; i < 10001; i++)
			contadorGanado.incrementar();
		
		System.out.println(contadorGanado.mostrar());
		contadorGanado.reiniciar();
		System.out.println(contadorGanado.mostrar());
		
	}
}
