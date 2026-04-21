package paquete;

public class Cilindro2 {
	private Circulo circulo;
	private double altura;
	
	public Cilindro2 (double radio, double altura) {
		this.circulo = new Circulo(radio);
		this.altura = altura;
	}
	
	public double getRadio() {
		return circulo.getRadio();
	}
	
	public double getAltura() {
		return altura;
	}
	
	public double getSuperficie() {
		return 2 * circulo.getSuperficie() + circulo.getRadio() * altura;
	}
	
	public double getVolumen();
}
