package composite;

public class Forma implements Pintable {

	private boolean pintada;
	private double superficieCm2;
	
	public Forma(double superficieCm2) throws Exception {
		
		if (superficieCm2 <= 0)
			throw new Exception("La superficie debe ser positiva");
			
		this.pintada = false;
		this.superficieCm2 = superficieCm2;
	}
	
	@Override
	public void pintar() {
		pintada = true;
	}

	@Override
	public boolean obtenerPintada() {
		return pintada;
	}
	
	@Override
	public double obtenerSuperficieTotalCm2() {
		return superficieCm2;
	}
}