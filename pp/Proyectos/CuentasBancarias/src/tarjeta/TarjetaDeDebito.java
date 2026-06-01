package tarjeta;

import cuenta.Cuenta;

public class TarjetaDeDebito {
	
	private Cuenta cuenta;
	
	public TarjetaDeDebito(Cuenta cuenta) throws Exception {
		
		if (cuenta == null)
			throw new Exception("Se debe indicar una cuenta a asociar.");
		
		this.cuenta = cuenta;
	}

	public boolean efectuarCompra(Cuenta destino, double monto) {
		return cuenta.transferir(destino, monto);
	}
}
