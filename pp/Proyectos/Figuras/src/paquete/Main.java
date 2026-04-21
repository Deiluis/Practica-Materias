package paquete;

public class Main {
	public static void main(String[] args) {
		
		double radio = 5, altura = 5;
		
		Circulo c = new Circulo(radio);
		
		System.out.println(c.getRadio());
		System.out.println(c.getSuperficie());
		System.out.println(c.getPerimetro());
		
		Cilindro cil = new Cilindro(radio, altura);
		
		System.out.println(cil.getRadio());
		System.out.println(cil.getAltura());
		System.out.println(cil.getSuperficie());
		System.out.println(cil.getPerimetro());
		System.out.println(cil.getVolumen());
	}
}
