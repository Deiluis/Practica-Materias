package paquete;

import java.util.Objects;

public class Rango implements Comparable<Rango>{
	private double limI, limS;
	private boolean incluyeLimI, incluyeLimS;
	
	private Rango (double limI, double limS, boolean incluyeLimI, boolean incluyeLimS) {
		this.limI = limI;
		this.limS = limS;
		this.incluyeLimI = incluyeLimI;
		this.incluyeLimS = incluyeLimS;
	}
	
	public static Rango crearRangoAbierto(double limI, double limS) {
		return new Rango(limI, limS, false, false);
	}
	
	public static Rango crearRangoAbiertoAIzquierda(double limI, double limS) {
		return new Rango(limI, limS, false, true);
	}
	
	public static Rango crearRangoAbiertoADerecha(double limI, double limS) {
		return new Rango(limI, limS, true, false);
	}
	
	public static Rango crearRangoCerrado(double limI, double limS) {
		return new Rango(limI, limS, true, true);
	}
	
	public boolean incluyeA(double num) {
		if (incluyeLimI) {
			if (incluyeLimS)
				return Double.compare(num, limI) >= 0 && Double.compare(num, limS) <= 0;
			
			return Double.compare(num, limI) >= 0 && Double.compare(num, limS) < 0;	
		}
			
		if (incluyeLimS)
			return Double.compare(num, limI) > 0 && Double.compare(num, limS) <= 0;	
		
		return Double.compare(num, limI) > 0 && Double.compare(num, limS) < 0;	
	}
	
	public boolean incluyeA(Rango r) {
		
		if (Double.compare(limI, r.limI) != 0 && Double.compare(limS, r.limS) != 0)
			return incluyeA(r.limI) && incluyeA(r.limS);
		
		if (Double.compare(limI, r.limI) == 0) {
			if (!incluyeLimI && r.incluyeLimI)
				return false;
		}
		
		if (Double.compare(limS, r.limS) == 0) {
			if (!incluyeLimS && r.incluyeLimS)
				return false;
		}
		
		return true;
	}

	public boolean intersectaCon (Rango r) {
		return (incluyeA(r.limI) || incluyeA(r.limS)) && (r.incluyeA(limI) || r.incluyeA(limS));
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(incluyeLimI, incluyeLimS, limI, limS);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Rango other = (Rango) obj;
		return incluyeLimI == other.incluyeLimI && incluyeLimS == other.incluyeLimS
				&& Double.doubleToLongBits(limI) == Double.doubleToLongBits(other.limI)
				&& Double.doubleToLongBits(limS) == Double.doubleToLongBits(other.limS);
	}

	// Esta mal poner todos los criterios de desempate acá?
//	@Override
//	public int compareTo(Rango r) {
//		// Pendiente
//		return 0;
//	}
	
	@Override
	public String toString() {
		return (incluyeLimI ? "[" : "(") + limI + ", " + limS + (incluyeLimS ? "]" : ")");
		
//		return "Rango [limI=" + limI + ", limS=" + limS + ", incluyeLimI=" + incluyeLimI + ", incluyeLimS="
//				+ incluyeLimS + "]";
	}
	
	
	// Inmutabilidad?
	
	
	public static Rango crearRangoReales() {
		return new Rango(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY, false, false);
	}
	
	public Rango sumarCon(Rango r) {
		Rango rangoMin = 
			Double.compare(this.limI, r.limI) < 0 ? this : r;
		Rango rangoMax = 
				Double.compare(this.limI, r.limI) > 0 ? this : r;
		
		return new Rango(
			rangoMin.limI, 
			rangoMax.limS, 
			rangoMin.incluyeLimI,
			rangoMax.incluyeLimS
		);
	}
	
	
	// Intersectar pendiente
	
	// Esto debería generar un rango nuevo?
	public Rango desplazar(double despl) {
		return new Rango(limI + despl, limS + despl, incluyeLimI, incluyeLimS);
	}
}
