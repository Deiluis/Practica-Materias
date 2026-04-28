package paquete;

public class Punto {
	private double x, y;
	
	public Punto (double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double obtenerX() {
		return x;
	}
	
	public double obtenerY() {
		return y;
	}
	
	public void cambiarX(double nuevoX) {
		x = nuevoX;
	}
	
	public void cambiarY(double nuevoY) {
		y = nuevoY;
	}
	
	public boolean estaSobreEjeX() {
		return y == 0;
	}
	
	public boolean estaSobreEjeY() {
		return x == 0;
	}
	
	public boolean esElOrigen() {
		return x == 0 && y == 0;
	}
	
	public double distanciaAlOrigen() {
		return Math.sqrt(x * x + y * y);
	}
	
	public double distanciaAotroPunto(Punto otro) {
		double x2 = otro.obtenerX();
		double y2 = otro.obtenerY();
		double dx = x - x2;
		double dy = y - y2;
		
		return Math.sqrt(dx * dx + dy * dy);
	}
}
