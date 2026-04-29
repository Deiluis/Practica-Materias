package paquete;

public class Paquete {
	private double pesoKg;
	private double distanciaKm;
	private boolean entregado;
	
	public Paquete(double pesoKg, double distanciaKm) {
		this.pesoKg = pesoKg;
		this.distanciaKm = distanciaKm;
		this.entregado = false;
	}
	
	public double getPesoKg() {
		return pesoKg;
	}
	
	public double getDistanciaKm() {
		return distanciaKm;
	}	
	
	public boolean getEntregado() {
		return entregado;
	}
	
	public void setEntregado(boolean entregado) {
		this.entregado = entregado;
	}
}
