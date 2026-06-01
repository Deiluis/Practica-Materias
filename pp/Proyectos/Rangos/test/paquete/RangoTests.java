package paquete;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class RangoTests {

	Rango r1, r2, r3, r4, r5, r6, r7, r8;
	
	@Test
	void creaRangosAbiertos() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		// Act
		r1 = Rango.crearRangoAbierto(limI, limS);
		r2 = Rango.crearRangoAbierto(limS, limI);
		
		// Assert
		assertEquals(r1.obtenerLimInferior(), limI, "El rango falló, lim inferior inconrrecto.");
		assertEquals(r1.obtenerLimSuperior(), limS, "El rango falló, lim superior inconrrecto.");
		assertEquals(
			r1.obtenerIncluyeLimInferior(), 
			false, 
			"El rango falló, se incluye lim inferior."
		);
		assertEquals(
			r1.obtenerIncluyeLimSuperior(), 
			false, 
			"El rango falló, se incluye lim superior."
		);
		
		assertNull(r2, "El rango falló, se creó con los límites invertidos.");
		
		// Annihilate
	}
	
	@Test
	void creaRangosAbiertosAIzquierda() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		// Act
		r1 = Rango.crearRangoAbiertoAIzquierda(limI, limS);
		r2 = Rango.crearRangoAbiertoAIzquierda(limS, limI);
		
		// Assert
		assertEquals(r1.obtenerLimInferior(), limI, "El rango falló, lim inferior inconrrecto.");
		assertEquals(r1.obtenerLimSuperior(), limS, "El rango falló, lim superior inconrrecto.");
		assertEquals(
			r1.obtenerIncluyeLimInferior(), 
			false, 
			"El rango falló, se incluye lim inferior."
		);
		assertEquals(
			r1.obtenerIncluyeLimSuperior(), 
			true, 
			"El rango falló, no se incluye lim superior."
		);
		
		assertNull(r2, "El rango falló, se creó con los límites invertidos.");
		
		// Annihilate
	}
	
	@Test
	void creaRangosAbiertosADerecha() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		// Act
		r1 = Rango.crearRangoAbiertoADerecha(limI, limS);
		r2 = Rango.crearRangoAbiertoADerecha(limS, limI);
		
		// Assert
		assertEquals(r1.obtenerLimInferior(), limI, "El rango falló, lim inferior inconrrecto.");
		assertEquals(r1.obtenerLimSuperior(), limS, "El rango falló, lim superior inconrrecto.");
		assertEquals(
			r1.obtenerIncluyeLimInferior(), 
			true, 
			"El rango falló, no se incluye lim inferior."
		);
		assertEquals(
			r1.obtenerIncluyeLimSuperior(), 
			false, 
			"El rango falló, se incluye lim superior."
		);
		
		assertNull(r2, "El rango falló, se creó con los límites invertidos.");
		
		// Annihilate
	}
	
	@Test
	void creaRangosCerrados() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		// Act
		r1 = Rango.crearRangoCerrado(limI, limS);
		r2 = Rango.crearRangoCerrado(limS, limI);
		
		// Assert
		assertEquals(r1.obtenerLimInferior(), limI, "El rango falló, lim inferior inconrrecto.");
		assertEquals(r1.obtenerLimSuperior(), limS, "El rango falló, lim superior inconrrecto.");
		assertEquals(
			r1.obtenerIncluyeLimInferior(), 
			true, 
			"El rango falló, no se incluye lim inferior."
		);
		assertEquals(
			r1.obtenerIncluyeLimSuperior(), 
			true, 
			"El rango falló, no se incluye lim superior."
		);
		
		assertNull(r2, "El rango falló, se creó con los límites invertidos.");
		
		// Annihilate
	}
	
	@Test
	void incluyeEscalar() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		double incluido = 5;
		double excluido = 20;
		
		r1 = Rango.crearRangoAbierto(limI, limS);
		r2 = Rango.crearRangoAbiertoAIzquierda(limI, limS);
		r3 = Rango.crearRangoAbiertoADerecha(limI, limS);
		r4 = Rango.crearRangoCerrado(limI, limS);
		
		// Act
		
		// Assert
		assertTrue(r1.incluyeA(incluido), "El rango abierto falló, no incluye un escalar dentro del mismo.");
		assertFalse(r1.incluyeA(excluido), "El rango abierto falló, incluye un escalar fuera del mismo.");
		assertFalse(r1.incluyeA(limI), "El rango abierto falló, incluye su limite inferior.");
		assertFalse(r1.incluyeA(limS), "El rango abierto falló, incluye su limite superior.");

		assertTrue(r2.incluyeA(incluido), "El rango abierto a izquierda falló, no incluye un escalar dentro del mismo.");
		assertFalse(r2.incluyeA(excluido), "El rango abierto a izquierda falló, incluye un escalar fuera del mismo.");
		assertFalse(r2.incluyeA(limI), "El rango abierto a izquierda falló, incluye su limite inferior.");
		assertTrue(r2.incluyeA(limS), "El rango abierto a izquierda falló, no incluye su limite superior.");
		
		assertTrue(r3.incluyeA(incluido), "El rango abierto a derecha falló, no incluye un escalar dentro del mismo.");
		assertFalse(r3.incluyeA(excluido), "El rango abierto a derecha falló, incluye un escalar fuera del mismo.");
		assertTrue(r3.incluyeA(limI), "El rango abierto a derecha falló, no incluye su limite inferior.");
		assertFalse(r3.incluyeA(limS), "El rango abierto a derecha falló, incluye su limite superior.");
		
		assertTrue(r4.incluyeA(incluido), "El rango cerrado falló, no incluye un escalar dentro del mismo.");
		assertFalse(r4.incluyeA(excluido), "El rango cerrado falló, incluye un escalar fuera del mismo.");
		assertTrue(r4.incluyeA(limI), "El rango cerrado falló, no incluye su limite inferior.");
		assertTrue(r4.incluyeA(limS), "El rango cerrado falló, no incluye su limite superior.");
		
		// Annihilate
		
	}
	
	// Pendiente: Incluye rango.
	
	@Test
	void compruebaInterseccionEnAbierto() {
		
		// Arrange
		r1 = Rango.crearRangoAbierto(1, 10);
		r2 = Rango.crearRangoAbierto(5, 15);
		r3 = Rango.crearRangoAbierto(15, 25);
		r4 = Rango.crearRangoAbierto(-20, -10);
		r5 = Rango.crearRangoAbierto(10, 20);
		r6 = Rango.crearRangoAbiertoADerecha(10, 20);
		r7 = Rango.crearRangoAbierto(-10, 1);
		r8 = Rango.crearRangoAbiertoAIzquierda(-10, 1);
		
		// Act
		
		// Assert
		assertTrue(r1.intersectaCon(r2), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r3), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r4), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r5), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r6), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r7), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r8), "El rango falló, intersecta a uno que no debería.");
		
		// Annihilate
		
	}
	
	@Test
	void compruebaInterseccionEnAbiertoAIzquierda() {
		
		// Arrange
		r1 = Rango.crearRangoAbiertoAIzquierda(1, 10);
		r2 = Rango.crearRangoAbierto(5, 15);
		r3 = Rango.crearRangoAbierto(15, 25);
		r4 = Rango.crearRangoAbierto(-20, -10);
		r5 = Rango.crearRangoAbierto(10, 20);
		r6 = Rango.crearRangoAbiertoADerecha(10, 20);
		r7 = Rango.crearRangoAbierto(-10, 1);
		r8 = Rango.crearRangoAbiertoAIzquierda(-10, 1);
		
		// Act
		
		// Assert
		assertTrue(r1.intersectaCon(r2), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r3), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r4), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r5), "El rango falló, intersecta a uno que no debería.");
		assertTrue(r1.intersectaCon(r6), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r7), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r8), "El rango falló, intersecta a uno que no debería.");
		
		// Annihilate
		
	}
	
	@Test
	void compruebaInterseccionEnAbiertoADerecha() {
		
		// Arrange
		r1 = Rango.crearRangoAbiertoADerecha(1, 10);
		r2 = Rango.crearRangoAbierto(5, 15);
		r3 = Rango.crearRangoAbierto(15, 25);
		r4 = Rango.crearRangoAbierto(-20, -10);
		r5 = Rango.crearRangoAbierto(10, 20);
		r6 = Rango.crearRangoAbiertoADerecha(10, 20);
		r7 = Rango.crearRangoAbierto(-10, 1);
		r8 = Rango.crearRangoAbiertoAIzquierda(-10, 1);
		
		// Act
		
		// Assert
		assertTrue(r1.intersectaCon(r2), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r3), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r4), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r5), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r6), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r7), "El rango falló, intersecta a uno que no debería.");
		assertTrue(r1.intersectaCon(r8), "El rango falló, no intersecta a uno que debería.");
		
		// Annihilate
		
	}
	
	@Test
	void compruebaInterseccionEnCerrado() {
		
		// Arrange
		r1 = Rango.crearRangoCerrado(1, 10);
		r2 = Rango.crearRangoAbierto(5, 15);
		r3 = Rango.crearRangoAbierto(15, 25);
		r4 = Rango.crearRangoAbierto(-20, -10);
		r5 = Rango.crearRangoAbierto(10, 20);
		r6 = Rango.crearRangoAbiertoADerecha(10, 20);
		r7 = Rango.crearRangoAbierto(-10, 1);
		r8 = Rango.crearRangoAbiertoAIzquierda(-10, 1);
		
		// Act
		
		// Assert
		assertTrue(r1.intersectaCon(r2), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r3), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r4), "El rango falló, intersecta a uno que no debería.");
		assertFalse(r1.intersectaCon(r5), "El rango falló, intersecta a uno que no debería.");
		assertTrue(r1.intersectaCon(r6), "El rango falló, no intersecta a uno que debería.");
		assertFalse(r1.intersectaCon(r7), "El rango falló, intersecta a uno que no debería.");
		assertTrue(r1.intersectaCon(r8), "El rango falló, no intersecta a uno que debería.");
		
		// Annihilate
		
	}
	
	@Test
	void compruebaIgualdadEnAbierto() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		r1 = Rango.crearRangoAbierto(limI, limS);
		r2 = Rango.crearRangoAbierto(limI, limS);
		r3 = Rango.crearRangoAbiertoADerecha(limI, limS);
		r4 = Rango.crearRangoAbiertoAIzquierda(limI, limS);
		r5 = Rango.crearRangoAbiertoAIzquierda(limI, limS);
		
		// Act
		
		// Assert
		assertTrue(r1.equals(r2), "El rango falló, no detecta como igual a uno que lo es.");
		assertFalse(r1.equals(r3), "El rango falló, detecta como igual a uno que no lo es.");
		assertFalse(r1.equals(r4), "El rango falló, detecta como igual a uno que no lo es.");
		assertFalse(r1.equals(r5), "El rango falló, detecta como igual a uno que no lo es.");
		
		
		// Annihilate
		
	}
	
	// Pendiente: Igualdad en las variantes.
	
	@Test
	void generaString() {
		
		// Arrange
		double limI = 1;
		double limS = 10;
		
		r1 = Rango.crearRangoAbierto(limI, limS);
		r2 = Rango.crearRangoAbiertoAIzquierda(limI, limS);
		r3 = Rango.crearRangoAbiertoADerecha(limI, limS);
		r4 = Rango.crearRangoCerrado(limI, limS);
		
		// Act
		
		// Assert
		assertEquals(r1.toString(), "(" + limI + ", " + limS + ")", "El rango falló, el string no coindice.");
		assertEquals(r2.toString(), "(" + limI + ", " + limS + "]", "El rango falló, el string no coindice.");
		assertEquals(r3.toString(), "[" + limI + ", " + limS + ")", "El rango falló, el string no coindice.");
		assertEquals(r4.toString(), "[" + limI + ", " + limS + "]", "El rango falló, el string no coindice.");
		
		// Annihilate
		
	}
	
}
