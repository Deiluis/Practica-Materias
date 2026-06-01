package cuenta;

import transaccion.Transaccion;

public class CuentaDeAhorros extends Cuenta {
	private double ahorros;
	
	public double consultarAhorros() {
		return ahorros;
	}
	
	public boolean reservarAhorros(double monto) {
		
		if (monto <= 0 || monto > saldo)
			return false;
		
		Transaccion t;
		
		try {
			t = new Transaccion(Transaccion.motivo.RESERVA_AHORROS, monto);
			
			saldo -= monto;
			ahorros += monto;
			transacciones.add(t);
		} catch (Exception e) {
			System.out.println(e.getMessage());
			return false;
		}
		
		return true;
	}
	
	public boolean reintegrarAhorros(double monto) {
		
		if (monto <= 0 || monto > ahorros)
			return false;
		
		Transaccion t;
		
		try {
			t = new Transaccion(Transaccion.motivo.REINTEGRO_AHORROS, monto);
			
			saldo += monto;
			ahorros -= monto;
			transacciones.add(t);
		} catch (Exception e) {
			System.out.println(e.getMessage());
			return false;
		}
		
		return true;
	}
	
	@Override
	protected double consultarMontoLimite() {
		return saldo;
	}
}
