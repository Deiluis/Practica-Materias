package paquete;

import java.util.Arrays;

public class Main {

	public static void main(String[] args) throws CloneNotSupportedException {
		
		Complejo z1 = new Complejo(-20, 3.2);
		Complejo z2 = new Complejo(-20, 3.2);
		Complejo z3 = z1.sumar(z2);
		Complejo z4 = z1.sumar(5.6, -8.32);
		// Complejo z5 = z3.clone();
		Complejo z5 = Complejo.sumar(z1, z2);
		
		ComparadorComplejo cc = new ComparadorComplejo();
		
		Complejo arrComplejos[] = {z1, z2, z3, z4, z5};
		
		// Toma el criterio de comparación del compareTo de Complejo.
		Arrays.sort(arrComplejos);
		System.out.println(Arrays.toString(arrComplejos));
		
		// Toma el criterio de comparación del comparador. Tiene que ser compatible con la clase Complejo.
		Arrays.sort(arrComplejos, cc);
		System.out.println(Arrays.toString(arrComplejos));
		
		if (cc.compare(z1, z2) > 0)
			System.out.println("z1 es mayor a z2");
		else if (cc.compare(z1, z2) < 0)
			System.out.println("z1 es menor a z2");
		else
			System.out.println("z1 es igual a z2");
		
		System.out.println(z1.toString());
		System.out.println(z2.toString());
		System.out.println(z5.toString());
	}

}
