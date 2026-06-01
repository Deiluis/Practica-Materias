package inodo;

public class Enlace extends Inodo {

	private Inodo ref;
	public static final int TAMANO_KB = 4;
	
	public Enlace(String nombre, Inodo ref) throws Exception {
		super(nombre);
		
		if (ref == null)
			throw new Exception("Se debe referenciar un inodo válido.");
		
		this.ref = ref;
	}
	
	@Override
	public int obtenerTamanoEnKB() {
		return TAMANO_KB;
	}
	
	@Override
	public int obtenerCantidadArchivos() {
		return 1;
	}
	
	public Inodo obtenerReferenciado() {
		return ref;
	}
}
