package inodo;

import java.util.Objects;

public abstract class Inodo implements Comparable<Inodo> {
	
	protected String nombre;
	
	protected Inodo(String nombre) throws Exception {
		
		if (nombre == null || nombre.trim() == "")
			throw new Exception("El " + this.getClass().getSimpleName().toLowerCase() + " necesita un nombre.");
			
		this.nombre = nombre;
	}
	
	public String obtenerNombre() {
		return this.nombre;
	}
	
	public abstract int obtenerTamanoEnKB();
	
	public abstract int obtenerCantidadArchivos();
	
	public Inodo buscar(String nombre) {
		return this.nombre == nombre ? this : null;
	}
	
	@Override
	public int compareTo(Inodo inodo) {
		return this.nombre.compareTo(inodo.nombre);
	}

	@Override
	public int hashCode() {
		return Objects.hash(nombre);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Inodo other = (Inodo) obj;
		return Objects.equals(nombre, other.nombre);
	}
}
