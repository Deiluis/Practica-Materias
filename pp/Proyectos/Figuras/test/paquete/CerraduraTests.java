package paquete;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class CerraduraTests {

	Cerradura cerradura;
	int clave = 1234;
	int cantFallosMax = 3;
	
	@BeforeEach
	void prepararTests() {
		cerradura = new Cerradura(clave, cantFallosMax);
	}
	
	@Test
	void comienzaAbierta() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		// Vacío en este caso.

		// Assert
		assertTrue(cerradura.estaAbierta(), "Falló. Inicialmente debe estar abierta.");
		assertFalse(cerradura.estaCerrada(), "Falló. Inicialmente debe estar abierta.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void abreCorrectamenteConClave() {
		// Arrange
		cerradura.cerrar();
		
		// Act
		// Vacío en este caso.
			
		// Assert
		assertTrue(cerradura.abrir(clave), "Falló. No abrió correctamente con su clave.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void noAbreConClaveErronea() {
		// Arrange
		int otraClave = clave + 1;
		cerradura.cerrar();
		
		// Act
		// Vacío en este caso.
			
		// Assert
		assertFalse(cerradura.abrir(otraClave), "Falló. Abrió con una clave erronea.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void cierraCorrectamente() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		cerradura.cerrar();
		
		// Assert
		assertTrue(cerradura.estaCerrada(), "Falló. No se cerró correctamente.");
		assertFalse(cerradura.estaAbierta(), "Falló. No se cerró correctamente.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void seBloqueaAnteFallosMax() {
		// Arrange
		int otraClave = clave + 1;
		cerradura.cerrar();
		
		// Act
		for (int i = 0; i < cantFallosMax; i++)
			cerradura.abrir(otraClave);
		
		// Assert
		assertFalse(cerradura.abrir(clave), "Falló. Abrió estando bloqueada.");
		assertTrue(cerradura.fueBloqueada(), "Falló. No se bloqueó correctamente.");
		
		// Annihilate
		// Vacío en este caso.
	}

}
