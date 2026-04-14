package paquete;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ContadorGanadoTests {

	ContadorGanado cg;
	
	@BeforeEach
	void prepararTest() {
		cg = new ContadorGanado();
	}
	
	@Test
	void comienzaEnCero() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		// Vacío en este caso.
		
		// Assert
		assertEquals(cg.mostrar(), 0, "Falló. No comienza en cero.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void incrementaDeAUno() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		cg.incrementar();
		
		// Assert
		assertEquals(cg.mostrar(), 1, "Falló. No incrementó de a uno.");
		
		// Annihilate
		// Vacío en este caso.
	}

	@Test
	void reiniciarDespuesDe9999() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		for (int i = 0; i < 10002; i++)
			cg.incrementar();
		
		// Assert
		assertEquals(cg.mostrar(), 2, "Falló. No reinició.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
}
