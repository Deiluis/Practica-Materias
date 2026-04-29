package paquete;

public abstract class Vehiculo {
	
	protected static int indice = 1;
	protected String identificador;
	protected Paquete paquete;
	
	public Vehiculo() {
		this.identificador = this.getClass().getSimpleName() + "-" + String.format("%03d", indice);
		indice++;
	}
	
	public Vehiculo(String identificador) {
		this.identificador = identificador;
		indice++;
	}
	
	private boolean puedeCargar(Paquete paquete) {
		if (this.paquete != null)
			return false;
		
		if (paquete.getPesoKg() > getPesoMaxKg())
			return false;
		
		if (paquete.getDistanciaKm() > getDistanciaMaxKm())
			return false;
		
		return true;
	}
	
	public boolean cargar(Paquete paquete) {
		
		if (!puedeCargar(paquete))
			return false;
		
		this.paquete = paquete;
		return true;
	}
	
	public Paquete entregar() {
		
		if (paquete == null)
			return null;
		
		Paquete paqueteAux = paquete;
		paquete.setEntregado(true);
		
		return paqueteAux;
	}
	
	public abstract double getPesoMaxKg();
	public abstract double getDistanciaMaxKm();
}
