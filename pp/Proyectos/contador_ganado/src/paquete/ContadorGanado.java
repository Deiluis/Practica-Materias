package paquete;

public class ContadorGanado {
	private int valor = 0;
	private final int tope = 10000;
	
	void incrementar() {
		valor++;
		
		if (valor >= tope)
			valor = 0;
	}
	
	void reiniciar() {
		valor = 0;
	}
	
	int mostrar() {
		return valor;
	}
}