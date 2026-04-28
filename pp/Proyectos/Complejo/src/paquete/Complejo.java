package paquete;

import java.util.Objects;
// import static java.lang.Math.*;

public class Complejo implements Comparable<Complejo> {
	private double real, imag;
	private static int valor;
	private static final double PI = 3.141592; 
	
	public Complejo() {
		this.real = 0d;
		this.imag = 0d;
	}
	
	public Complejo(double real, double imag) {
		this.real = real;
		this.imag = imag;
	}
	
	public Complejo sumar(Complejo comp) {
		return new Complejo(
			real + comp.real, 
			imag + comp.imag
		);
	}

	public Complejo sumar(double real, double imag) {
		return new Complejo(
			this.real + real, 
			this.imag + imag
		);
	}
	
	public static Complejo sumar(Complejo comp1, Complejo comp2) {
		return new Complejo(
			comp1.real + comp2.real, 
			comp1.imag + comp2.imag
		);
	}
	
	public double obtenerModulo() {
		return Math.sqrt(real * real + imag * imag);
	}
	
	public double obtenerParteReal() {
		return this.real;
	}
	
	public double obtenerParteImag() {
		return this.imag;
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(imag, real);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) // Misma referencia.
			return true;
		if (obj == null) // Si el objeto es nulo.
			return false;
		if (getClass() != obj.getClass()) // Verifica si son de la misma clase.
			return false;
		Complejo other = (Complejo) obj; // Castea a Complejo.
		return Double.doubleToLongBits(imag) == Double.doubleToLongBits(other.imag)
				&& Double.doubleToLongBits(real) == Double.doubleToLongBits(other.real);
	}

	@Override
	public int compareTo(Complejo comp) {
		
		int cmp = Double.compare(this.real, comp.real);
		
		if (cmp != 0)
			return cmp;
		
		return Double.compare(this.imag, comp.imag);
	}
	
	@Override
	public String toString() {
//		return "Complejo [real=" + real + ", imag=" + imag + "]";
		return real + (imag > 0 ? "+" : "") + imag + "i";
	}
	
	@Override
	public Complejo clone() throws CloneNotSupportedException {
		// TODO Auto-generated method stub
		return (Complejo) super.clone();
	}

	@Override
	protected void finalize() throws Throwable {
		// TODO Auto-generated method stub
		super.finalize();
	}
}
