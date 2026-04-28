package paquete;

import java.util.Comparator;

public class ComparadorComplejo implements Comparator<Complejo> {

	@Override
	public int compare(Complejo comp1, Complejo comp2) {
		return Double.compare(comp1.obtenerParteReal(), comp2.obtenerParteReal());
	}
	
}
