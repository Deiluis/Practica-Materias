package inodo;

public class Archivo extends Inodo {

	private int tamanoEnKB;
	
	public Archivo (String nombre, int tamanoEnKB) throws Exception {
		super(nombre);
		
		if (tamanoEnKB <= 0)
			throw new Exception("El tamaño debe ser positivo.");
			
		this.tamanoEnKB = tamanoEnKB;
	}
	
	@Override
	public int obtenerTamanoEnKB() {
		return this.tamanoEnKB;
	}
	
	@Override
	public int obtenerCantidadArchivos() {
		return 1;
	}
}