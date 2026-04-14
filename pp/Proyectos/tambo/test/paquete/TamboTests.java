package paquete;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TamboTests {

	Tambo tambo;
	
	@BeforeEach
	void prepararTests () {
		tambo = new Tambo();
	}
	
	@Test
	void litrosValidosOrdene() {
		// Assert
		assertEquals(tambo.registrarOrdene(-1), false);
		assertEquals(tambo.registrarOrdene(0), false);
		assertEquals(tambo.registrarOrdene(1), true);
	}
	
	@Test
	void promedioValidoSinOrdenes() {
		// Assert
		assertEquals(tambo.obtenerPromedioLitros(), 0);
	}
	
	@Test
	void promedioValidoConOrdenes() {
		// Arrange
		int ordenes[] = {2, 4, 5, 6};
		float esperado = 0;
		
		// Act 
		for (int i = 0; i < ordenes.length; i++) {
			tambo.registrarOrdene(ordenes[i]);
			esperado += ordenes[i];
		}
		
		esperado /= ordenes.length;
			
		// Assert
		assertEquals(tambo.obtenerPromedioLitros(), esperado);
	}
	
	@Test
	void totalProducidoCorrecto() {
		// Arrange
		int ordenes[] = {2, 4, 5, 6};
		int esperado = 0;
		
		// Act 
		for (int i = 0; i < ordenes.length; i++) {
			tambo.registrarOrdene(ordenes[i]);
			esperado += ordenes[i];
		}
		
		// Assert
		assertEquals(tambo.obtenerTotalProducido(), esperado);
	}
}
