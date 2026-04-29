package paquete;

public class Moto extends Vehiculo {
	public static final double DISTANCIA_MAX_KM = 10;
	public static final double PESO_MAX_KG = 10;
	public static final double CAPACIDAD_COMBUSTIBLE_L = 10;
	public static final double CONSUMO_POR_KM_EN_L = 0.050;
	
	private double combustibleL = 10;

	public Moto(double combustibleL) {
		super();
		this.combustibleL = combustibleL;
	}
	
	public Moto(String identificador, double combustibleL) {
		super(identificador);
		this.combustibleL = combustibleL;
	}


	// Depende de que tanto
	
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
