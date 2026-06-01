package composite;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Grupo implements Pintable {
	
	private List<Pintable> pintables = new ArrayList<>();
	
	public boolean aniadir(Pintable p) {
		return pintables.add(p);
	}
	
	@Override
	public void pintar() {
		
		Pintable p;
		
		for (Iterator<Pintable> it = pintables.iterator(); it.hasNext();) {
			p = (Pintable) it.next();
			p.pintar();
		}
	}

	@Override
	public boolean obtenerPintada() {
		
		if (pintables.size() == 0)
			return false;
		
		boolean pintada = true;
		Pintable p;
		
		for (Iterator<Pintable> it = pintables.iterator(); it.hasNext() && pintada;) {
			p = (Pintable) it.next();
			pintada = p.obtenerPintada();
		}
		
		return pintada;
	}
	
	@Override
	public double obtenerSuperficieTotalCm2() {
		
		double superficieCm2 = 0;
		Pintable p;
		
		for (Iterator<Pintable> it = pintables.iterator(); it.hasNext();) {
			p = (Pintable) it.next();
			superficieCm2 += p.obtenerSuperficieTotalCm2();
		}
		
		return superficieCm2;
	}
}
