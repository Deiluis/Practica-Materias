package paquete;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		List<Integer> lista = new LinkedList<>();
		
		// Agregar elementos
		lista.add(24);
		lista.add(38); // Redimensionamiento.
		// Redimensionamiento, si pongo un indice que ya existe empuja a los que haya despues.
		lista.add(2, -1);
		
		// Mostrar
		// Es un vector, tiene implementado automaticamente el toString().
		System.out.println(lista);
		System.out.println("Cantidad de elementos de lista: " + lista.size());
		
		// Consulta
		// Si consulto un indice que esta por afuera de los bounds, arroja una excepción.
		System.out.println(lista.get(1));
		System.out.println(lista.contains(38));
		System.out.println(lista.indexOf(38));
	
		// Inmutable: No se puede modificar mientras recorro.
		for (int num : lista)
			System.out.println(num);
		
		// Ordenamiento
		lista.sort(null);
		System.out.println(lista);
		Collections.reverse(lista);
		System.out.println(lista);
		
		// Devolver como vector
		lista.toArray();
		
		// Eliminar
		// Remove devuelve el elemento que eliminó.
		System.out.println("Se eliminó el elemento: " + lista.remove(0));
		System.out.println(lista);
		System.out.println(lista.remove((Integer) 38));
		System.out.println(lista);
		
		// Elimina toda la lista
		lista.clear();
		System.out.println(lista);
		
		
		// ------------------------------------------------
		
		Set<String> conjunto = new TreeSet<>();
		
		conjunto.add("Diego");
		conjunto.add("María");
		conjunto.add("Aldo");
		conjunto.add("Tiago");
		conjunto.add("Aldo"); // No se inserta, esta repetido.
		
		// Orden según hashes en la hashtable.
		// Orden según comparación en el treeset.
		System.out.println(conjunto);
		System.out.println(conjunto.contains("María"));
		conjunto.remove("María");
		System.out.println(conjunto.contains("María"));
		conjunto.clear();
		System.out.println(conjunto);
		
		
		// ------------------------------------------------
		
		Map<String, Integer> mapa = new TreeMap<>();
		
		// Orden según hashes en el hashmap.
		// Orden según comparación en el treemap.
		mapa.put("Carlos", 3);
		mapa.put("Roberto", 4);
		mapa.put("Hernesto", 7); // Por qué con H?
		mapa.put("Jorge", 1);
		mapa.put("Ricardo", 9);
		
		// Ante claves repetidas, actualiza el valor.
		mapa.put("Carlos", 28);
		
		System.out.println(mapa);
		
		System.out.println("Valor de la clave 'Carlos': " + mapa.get("Carlos"));
		System.out.println("Contiene la clave Jorge: " + mapa.containsKey("Jorge"));
		System.out.println("Contiene valor 9: " + mapa.containsValue(9));
		
		for (String nombre : mapa.keySet()) {
			System.out.println(nombre);
		}
	}

}
