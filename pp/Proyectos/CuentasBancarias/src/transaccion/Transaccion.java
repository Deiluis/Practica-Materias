package transaccion;

public class Transaccion {
	private motivo motivo;
	private double monto;
	
	public static enum motivo {
		DEPOSITO,
		EXTRACCION,
		ENVIO_TRANSFERENCIA,
		RECEPCION_TRANSFERENCIA,
		RESERVA_AHORROS,
		REINTEGRO_AHORROS
	}
	
	public Transaccion(motivo motivo, double monto) throws Exception {
		
		if (motivo == null)
			throw new Exception("Se debe indicar el motivo.");
		
		if (monto <= 0)
			throw new Exception("El monto debe ser positivo.");
		
		this.motivo = motivo;
		this.monto = monto;
	}
	
	public motivo consultarMotivo() {
		return motivo;
	}
	
	public double consultarMonto() {
		return monto;
	}

	@Override
	public String toString() {
		return "Transaccion [motivo=" + motivo + ", monto=" + monto + "]";
	}
}