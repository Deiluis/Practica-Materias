package paquete;

public class Camioneta extends Vehiculo {
	
	public static final double DISTANCIA_MAX_KM = 100;
	public static final double PESO_MAX_KG = 100;
	public static final double CAPACIDAD_COMBUSTIBLE_L = 10;
	public static final double CONSUMO_POR_KM_EN_L = 0.02;
	public static final int CANT_MAX_PAQUETES = 5;
	
	private Paquete paquetes[];
	private double combustibleL = 10;
	
	public Camioneta(String identificador) {
		this.identificador = identificador;
		indice++;
	}
	
	public Camioneta() {
		this("Camioneta-" + String.format("%03d", indice));
	}
	
	private boolean puedeCargar(Paquete paquete) {
		if (paquetes.length > CANT_MAX_PAQUETES)
			return false;
		
		if (paquete.getPesoKg() > getPesoMaxKg())
			return false;
		
		if (paquete.getDistanciaKm() > getDistanciaMaxKm())
			return false;
		
		paquetes.
		
		return true;
	}
	
	public boolean cargar(Paquete paquete) {
		
		if (!puedeCargar(paquete))
			return false;
		
		this.paquete = paquete;
		return true;
	}
	
	@Override
	public Paquete entregar() {
		
		if (paquete == null)
			return null;
		
		double consumision = 
			2 * paquete.getDistanciaKm() * CONSUMO_POR_KM_EN_L;
			
		if (consumision >= combustibleL)
			return null;
			
		combustibleL -= consumision;
		
		Paquete paqueteAux = paquete;
		paquete.setEntregado(true);
		
		return paqueteAux;
	}
	
	public double cargarCombustible(double litros) {
		
		if (Double.compare(combustibleL, CAPACIDAD_COMBUSTIBLE_L) == 0) 
			return 0;

		double capRestante = CAPACIDAD_COMBUSTIBLE_L - combustibleL;
		double cargado = Math.max(capRestante, litros);
		
		combustibleL += cargado;
		return cargado;
	}
	
	@Override
	public double getPesoMaxKg() {
		return PESO_MAX_KG;
	}
	
	@Override
	public double getDistanciaMaxKm() {
		return DISTANCIA_MAX_KM;
	}
	
}
