package paquete;

public class Bicicleta extends Vehiculo {
	public static final double DISTANCIA_MAX_KM = 3;
	public static final double PESO_MAX_KG = 5;
	
	public Bicicleta(String identificador) {
		super(identificador);
	}
	
//	public Bicicleta() {
//		this("Bicicleta-" + String.format("%03d", indice));
//	}
	
	@Override
	public double getPesoMaxKg() {
		return PESO_MAX_KG;
	}
	
	@Override
	public double getDistanciaMaxKm() {
		return DISTANCIA_MAX_KM;
	}
}
