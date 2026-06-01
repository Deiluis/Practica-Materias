package main;

import inodo.*;

public class Main {

	public static void main(String[] args) {
		
		try {
			Inodo f1 = new Archivo("prueba.txt", 20);
			Inodo f2 = new Archivo("libro.pdf", 4096);
			Inodo f3 = new Archivo("carpincho.png", 2004);
			
			System.out.println(f1.obtenerNombre());
			System.out.println(f1.obtenerCantidadArchivos());
			System.out.println(f1.obtenerTamanoEnKB());
			System.out.println(f1.buscar("prueba.txt"));
			
			Directorio d1, d2, d3, d4;
			d1 = new Directorio("Varios");
			d2 = new Directorio("Miscelaneos");
			d3 = new Directorio("Otros");
			d4 = new Directorio("Etc");
			
			System.out.println(d1.obtenerNombre());
			System.out.println(d1.obtenerCantidadArchivos());
			System.out.println(d1.obtenerTamanoEnKB());
			System.out.println(d1.buscar("prueba.txt"));
			
			d1.guardar(f3);
			d2.guardar(f1);
			d1.guardar(d2);
			d1.guardar(d4);
			
			System.out.println(d1.obtenerCantidadArchivos());
			System.out.println(d1.obtenerTamanoEnKB());
			System.out.println(d1.obtenerContenidos());
			System.out.println(d1.buscar("prueba.txt"));
			System.out.println(f1.equals(d1.buscar("prueba.txt")));
			
			Inodo l1 = new Enlace("f1.lnk", f1);
			
			d3.guardar(l1);
			d3.guardar(f2);
			
			System.out.println(d3.obtenerCantidadArchivos());
			System.out.println(d3.obtenerTamanoEnKB());
			System.out.println(d3.obtenerContenidos());
			System.out.println(d3.buscar("f1.lnk"));
			
			System.out.println(f1.equals(((Enlace) l1).obtenerReferenciado()));
			
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

}
