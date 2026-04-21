package paquete;

public class Cerradura {
	
	private int clave;
	private int cantFallosMax;
	private int cantExitos = 0;
	private int cantFallos = 0;
	private boolean abierta = true;
	private boolean bloqueada = false;
	
    public Cerradura(
    	int claveDeApertura,
        int cantidadDeFallosConsecutivosQueLaBloquean
    ) {
    	clave = claveDeApertura;
    	cantFallosMax = cantidadDeFallosConsecutivosQueLaBloquean;
    }
    
	public boolean abrir(int clave) {
	
		if (abierta || bloqueada)
			return false;
		
		if (this.clave == clave) {
			cantExitos++;
			cantFallos = 0;
			return true;
		}
		
		cantFallos++;
		
		// Por las dudas, ante falta de atomicidad en memoria compartida de hilos.
		bloqueada = cantFallos >= cantFallosMax;
		
		return false;
	}
	
	public void cerrar() {
		// El enunciado pide indicar pre y pos condiciones.
		if (!abierta)
			abierta = false;
	}
	
	public boolean estaAbierta() {
		return abierta;
	}
	
	public boolean estaCerrada() {
		return !abierta;
	}
	
	public boolean fueBloqueada() {
		return bloqueada;
	}
	
	public int contarAperturasExitosas() {
		return cantExitos;
	}
	
	public int contarAperturasFallidas() {
		return cantFallos;
	}
}