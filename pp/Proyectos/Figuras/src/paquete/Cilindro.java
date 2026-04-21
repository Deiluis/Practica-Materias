package paquete;

public class Cilindro extends Circulo {
	private double altura;
	
	public Cilindro (double radio, double altura) {
		super(radio);
		this.altura = altura;
	}
	
	public double getAltura () {
		return altura;
	}
	
	public boolean setAltura (double altura) {
		if (altura <= 0)
			return false;
		
		this.altura = altura;
		return true;
	}
	
	public double getVolumen () {
		return super.getSuperficie() * altura;
	}
	
	public boolean setVolumen (double volumen) {
		if (volumen <= 0)
			return false;
		
		double ratio = this.getVolumen() / volumen;
		altura *= ratio;
		this.setRadio(this.getRadio() * ratio);
		
		return true;
	}
	
	@Override
	public double getSuperficie () {
		double supTapa = super.getSuperficie();
		double supLateral = super.getPerimetro() * altura;
		return 2 * supTapa + supLateral;
	}
}
