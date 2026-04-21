package paquete;

public class Circulo {
	private double radio;
	
	public Circulo (double radio) {
		this.radio = radio;
	}
	
	public Circulo () {
		radio = 1;
	}
	
	public double getRadio() {
		return radio;
	}
	
	public boolean setRadio(double radio) {
		if (radio <= 0)
			return false;
		
		this.radio = radio;
		return true;
	}
	
	public double getPerimetro() {
		return 2 * Math.PI * radio;
	}
	
	public boolean setPerimetro(double perimetro) {
		if (perimetro <= 0)
			return false;
		
		radio = perimetro / (2 * Math.PI);
		return true;
	}
	
	public double getSuperficie() {
		return Math.PI * radio * radio;
	}
	
	public boolean setSuperficie(double superficie) {
		if (superficie <= 0)
			return false;
		
		radio = Math.sqrt(superficie / Math.PI);
		return true;	
	}
}
