package paquete;

import composite.Forma;
import composite.Grupo;

public class Main {

	public static void main(String[] args) {
		
		final double coberturaTempCm2 = 100d;
		
		try {
			Forma f1, f2, f3, f4;
			Grupo g1, g2;
			double supTotalCm2;
			
			f1 = new Forma(50d);
			f2 = new Forma(75d);
			f3 = new Forma(30.5d);
			f4 = new Forma(24.6d);
			
			g1 = new Grupo();
			g2 = new Grupo();
			
			g1.aniadir(f1);
			g1.aniadir(f2);
			g1.aniadir(f3);
			
			System.out.println(g1.obtenerSuperficieTotalCm2());
			
			g2.aniadir(f4);
			g1.aniadir(g2);
			
			System.out.println(g1.obtenerSuperficieTotalCm2());
			System.out.println(g2.obtenerSuperficieTotalCm2());
			
			supTotalCm2 = g1.obtenerSuperficieTotalCm2();
			
			System.out.println(Math.ceil(supTotalCm2 / coberturaTempCm2));
			
		} catch (Exception e) {
			// TODO: handle exception
		}
		
	}

}
