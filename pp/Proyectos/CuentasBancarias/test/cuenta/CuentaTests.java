package cuenta;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class CuentaTests {

//	Cuenta c;
//
//	@BeforeEach
//	void prepararTests() {
//		c = new Cuenta();
//	}
//	
//	@Test
//	void saldoComienzaEnCero() {
//		
//		// Arrange
//		double saldo;
//		
//		// Act
//		saldo = c.consultarSaldo();
//		
//		// Assert
//		assertEquals(saldo, 0, "Falló, no comienza en 0.");
//		
//		// Annihilate
//	}
//	
//	@Test
//	void depositaCorrectamente() {
//		
//		// Arrange
//		double monto = 500d;
//		boolean resultado1, resultado2, resultado3;
//		
//		// Act
//		resultado1 = c.depositar(monto); // Éxito
//		resultado2 = c.depositar(-monto); // Fallo
//		resultado3 = c.depositar(0); // Fallo
//		
//		// Assert
//		assertEquals(c.consultarSaldo(), monto, "Falló, no depositó el monto correspondiente.");
//		assertTrue(resultado1, "Falló, no depositó el monto correspondiente.");
//		assertFalse(resultado2, "Falló, depositó un monto erróneo.");
//		assertFalse(resultado3, "Falló, depositó un monto erróneo.");
//		
//		// Annihilate
//	}
//	
//	@Test
//	void extraeCorrectamente() {
//		
//		// Arrange
//		double deposito = 500d, extraccion = 200d;
//		boolean resultado1, resultado2, resultado3;
//		
//		// Act
//		resultado1 = c.extraer(extraccion); // Fallo
//		resultado2 = c.extraer(-extraccion); // Fallo
//		c.depositar(deposito);
//		resultado3 = c.extraer(extraccion); // Éxito
//		
//		// Assert
//		assertEquals(c.consultarSaldo(), deposito - extraccion, "Falló, no se extrajo el monto correspondiente.");
//		assertFalse(resultado1, "Falló, extrajo con saldo en 0.");
//		assertFalse(resultado2, "Falló, extrajo un monto negativo.");
//		assertTrue(resultado3, "Falló, no se extrajo el monto correspondiente.");
//		
//		// Annihilate
//	}
//	
//	@Test
//	void transfiereCorrectamente() {
//		
//		// Arrange
//		Cuenta destino = new Cuenta();
//		double deposito = 500d, transferencia = 200d;
//		boolean resultado1, resultado2, resultado3;
//		
//		// Act
//		resultado1 = c.transferir(destino, transferencia); // Fallo
//		resultado2 = c.transferir(destino, -transferencia); // Fallo
//		c.depositar(deposito);
//		resultado3 = c.transferir(destino, transferencia); // Éxito
//		
//		// Assert
//		assertEquals(c.consultarSaldo(), deposito - transferencia, "Falló, no se transfirió el monto correspondiente.");
//		assertEquals(destino.consultarSaldo(), transferencia, "Falló, no se transfirió el monto correspondiente.");
//		assertFalse(resultado1, "Falló, se transfirió con saldo en 0.");
//		assertFalse(resultado2, "Falló, se transfirió un monto negativo.");
//		assertTrue(resultado3, "Falló, no se transfirió el monto correspondiente.");
//		
//		// Annihilate
//	}

}
