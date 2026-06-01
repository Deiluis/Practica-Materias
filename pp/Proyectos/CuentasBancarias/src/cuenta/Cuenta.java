package cuenta;
import java.util.ArrayList;
import java.util.List;

import transaccion.Transaccion;

public abstract class Cuenta {
	
	protected int id;
	protected double saldo; // Sería preferible utilizar BigDecimal.
	protected List<Transaccion> transacciones = new ArrayList<>();
	
	protected static int indice = 1;
	
	public Cuenta() {
		id = indice;
		indice++;
	}
	
	public int consultarId() {
		return id;
	}
	
	public double consultarSaldo() {
		return saldo;
	}
	
	public boolean depositar(double monto) {
		
		if (monto <= 0)
			return false;
				
		Transaccion t;
		
		try {
			t = new Transaccion(Transaccion.motivo.DEPOSITO, monto);
		} catch (Exception e) {
			// De que otra forma puede manejarse un caso así?
			System.out.println(e.getMessage());
			return false;
		}
		
		saldo += monto;
		transacciones.add(t);
		
		return true;
	}
	
	public boolean extraer(double monto) {
		
		if (monto <= 0 || monto > consultarMontoLimite())
			return false;
		
		Transaccion t;
		
		try {
			t = new Transaccion(Transaccion.motivo.EXTRACCION, monto);
			
			saldo -= monto;
			transacciones.add(t);
		} catch (Exception e) {
			System.out.println(e.getMessage());
			return false;
		}
		
		return true;
	}
	
	// Se necesitaría algún mecanismo que haga esta operación atómica.
	public boolean transferir(Cuenta destino, double monto) {
		
		if (monto <= 0 || monto > consultarMontoLimite())
			return false;
		
		Transaccion t1, t2;
		
		try {
			t1 = new Transaccion(Transaccion.motivo.ENVIO_TRANSFERENCIA, monto);
			t2 = new Transaccion(Transaccion.motivo.RECEPCION_TRANSFERENCIA, monto);
			
			saldo -= monto;
			destino.saldo += monto;
			
			transacciones.add(t1);
			destino.transacciones.add(t2);
			
		} catch (Exception e) {
			System.out.println(e.getMessage());
			return false;
		} 
		
		return true;
	}
	
	public List<Transaccion> consultarTransacciones() {
		return transacciones;
	}
	
	protected abstract double consultarMontoLimite();
}
