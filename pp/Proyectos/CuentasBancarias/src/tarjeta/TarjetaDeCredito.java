package tarjeta;

import java.util.ArrayList;
import java.util.NoSuchElementException;

import cuenta.Cuenta;

public class TarjetaDeCredito {

	private Cuenta cuenta;
	private double tope, utilizado;
	// Podría ser tranquilamente un array estático con la cantidad de elementos que indique mesesDeudaMax.
	private ArrayList<Double> deudaMensual = new ArrayList<>();
	private int mesesDeudaMax;
	public static final double PORC_COMISION = 0.03;
	
	public TarjetaDeCredito(Cuenta cuenta, double tope, int mesesDeudaMax) throws Exception {
		
		if (cuenta == null)
			throw new Exception("Se debe indicar una cuenta a asociar.");
		
		if (tope <= 0)
			throw new Exception("El tope debe ser positivo.");
		
		if (mesesDeudaMax <= 0)
			throw new Exception("La cantidad de meses de deuda debe ser positiva.");
		
		this.cuenta = cuenta;
		this.tope = tope;
		this.mesesDeudaMax = mesesDeudaMax;
	}

	public boolean efectuarCompra(Cuenta destino, double monto) {
		
		if (deudaMensual.size() == mesesDeudaMax || utilizado + monto > tope)
			return false;
		
		utilizado += monto;
		
		return destino.depositar(monto);
	}
	
	public boolean debitarCompras() {
		
		if (utilizado == 0)
			return false;
		
		double debito = utilizado * (1 + PORC_COMISION);
		
		if (!cuenta.extraer(debito)) {
			deudaMensual.add(debito);
			return false;
		}
		
		utilizado = 0;
		return true;
	}
	
	public boolean debitarDeudaMensual() {
		
		try {
			double deudaMasAntigua = (double) deudaMensual.getFirst();
			
			if (!cuenta.extraer(deudaMasAntigua))
				return false;
			
			deudaMensual.removeFirst();
			
		} catch (NoSuchElementException e) {
			return false;
		}
		
		return true;
	}
	
	public ArrayList<Double> obtenerDeudaMensual () {
		return deudaMensual;
	}
}
