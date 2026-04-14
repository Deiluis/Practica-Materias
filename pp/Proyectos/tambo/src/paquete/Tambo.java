package paquete;

public class Tambo {
	private int totalProd = 0;
	private int cantOrdenes = 0;
	
	boolean registrarOrdene (int litros) {
		if (litros > 0) {
			totalProd += litros;
			cantOrdenes++;
			return true;
		}
		
		return false;
	}
	
	float obtenerPromedioLitros () {
		return cantOrdenes > 0 ? (float) totalProd / cantOrdenes : 0; 
	}
	
	int obtenerTotalProducido () {
		return totalProd;
	}
}
