package cuenta;

public class CuentaCorriente extends Cuenta {
	private double descubierto;
	
	public CuentaCorriente(double descubierto) throws Exception {
		
		if (descubierto <= 0)
			throw new Exception("El monto descubierto debe ser positivo.");
		
		this.descubierto = descubierto;
	}
	
//	@Override
//	public boolean extraer(double monto) {
//		
//		if (monto <= 0 || monto > saldo + descubierto)
//			return false;
//		
//		saldo -= monto;
//		
//		return true;
//	}
//	
//	@Override
//	public boolean transferir(Cuenta destino, double monto) {
//		
//		if (monto <= 0 || monto > saldo + descubierto)
//			return false;
//		
//		saldo -= monto;
//		destino.saldo += monto;
//		
//		return true;
//	}
	
	@Override
	protected double consultarMontoLimite() {
		return saldo + descubierto;
	}
}
