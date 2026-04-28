package paquete;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class PuntoTests {

	Punto punto;
	
	@BeforeEach
	void prepararTests () {
		punto = new Punto(0, 0);
	}
	
	@Test
	void cambiaCorrectamente() {
		// Arrange
		double x = 5d;
		double y = 7d;
		
		// Act
		punto.cambiarX(x);
		punto.cambiarY(y);
		
		// Assert
		assertEquals(punto.obtenerX(), x, "Falló. X no comienza en el valor especificado.");
		assertEquals(punto.obtenerY(), y, "Falló. Y no comienza en el valor especificado.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void verificaSobreEjeX() {
		// Arrange
		double x = 5d;
		double y = 0d;
		
		// Act
		punto.cambiarX(x);
		punto.cambiarY(y);
		
		// Assert
		assertTrue(punto.estaSobreEjeX(), "Falló. No verifica que este sobre el eje X.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void verificaSobreEjeY() {
		// Arrange
		double x = 0d;
		double y = 7d;
		
		// Act
		punto.cambiarX(x);
		punto.cambiarY(y);
		
		// Assert
		assertTrue(punto.estaSobreEjeY(), "Falló. No verifica que este sobre el eje Y.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void verificaOrigen() {
		// Arrange
		// Vacío en este caso.
		
		// Act
		// Vacío en este caso.
		
		// Assert
		assertTrue(punto.esElOrigen(), "Falló. No verifica que sea el origen.");
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void distanciaAlOrigenCorrecta() {
		// Arrange
		double x = 5d;
		double y = 7d;
		
		// Act
		punto.cambiarX(x);
		punto.cambiarY(y);
		
		// Assert
		assertEquals(
				punto.distanciaAlOrigen(), 
				Math.sqrt(x * x + y * y), 
				"Falló. La distancia calculada es incorrecta"
		);
		
		// Annihilate
		// Vacío en este caso.
	}
	
	@Test
	void distanciaAOtroPuntoCorrecta() {
		// Arrange
		double x1 = 5d;
		double y1 = 7d;
		double x2 = -3d;
		double y2 = 6d;
		double distancia, dx, dy;
		
		Punto puntoA = punto;
		Punto puntoB = new Punto(x2, y2);
		
		// Act
		puntoA.cambiarX(x1);
		puntoA.cambiarY(y1);
		
		dx = x1 - x2;
		dy = y1 - y2;
		
		distancia = Math.sqrt(dx * dx + dy * dy);
		
		// Assert
		assertEquals(
				punto.distanciaAotroPunto(puntoB), 
				distancia,
				"Falló. La distancia calculada es incorrecta"
		);
		
		// Annihilate
		// Vacío en este caso.
	}

}
