package inodo;

import java.util.TreeSet;
import java.util.Iterator;
import java.util.Set;

public class Directorio extends Inodo {

	private Set<Inodo> inodos = new TreeSet<>();
	
	public Directorio (String nombre) throws Exception {
		super(nombre);
	}

	public boolean guardar(Inodo i) {
		return inodos.add(i);
	}
	
	@Override
	public int obtenerTamanoEnKB() {
		
		int tamano = 0;
		
		for (Inodo i : inodos)
			tamano += i.obtenerTamanoEnKB();

		return tamano;
	}
	
	@Override
	public int obtenerCantidadArchivos() {
		
		int archivos = 1;
		
		for (Inodo i : inodos)
			archivos += i.obtenerCantidadArchivos();
		
		return archivos;
	}
	
	@Override
	public Inodo buscar(String nombre) {
		
		Inodo inodo = null;
		
		if (this.nombre == nombre)
			return this;
		
		for (Iterator<Inodo> iterator = inodos.iterator(); iterator.hasNext() && inodo == null;) {
			inodo = (Inodo) iterator.next();
			inodo = inodo.buscar(nombre);
		}
		
		return inodo;
	}
	
	public Set<Inodo> obtenerContenidos() {
		return inodos;
	}
}
