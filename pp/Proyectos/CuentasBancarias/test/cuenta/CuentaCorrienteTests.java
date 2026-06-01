package cuenta;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class CuentaCorrienteTests {

	CuentaCorriente cc;
	double descubierto;
	
	@BeforeEach
	void prepararTests() {
		descubierto = 2000d;
		
		try {
			cc = new CuentaCorriente(descubierto);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
	
	@Test
	void extraeCorrectamente() {
		
		// Arrange
		double deposito = 500d, extraccion = descubierto + 200d;
		boolean resultado1, resultado2, resultado3;
		
		// Act
		resultado1 = cc.extraer(extraccion); // Fallo
		resultado2 = cc.extraer(-extraccion); // Fallo
		cc.depositar(deposito);
		resultado3 = cc.extraer(extraccion); // Éxito
		
		// Assert
		assertEquals(cc.consultarSaldo(), deposito - extraccion, "Falló, no se extrajo el monto correspondiente.");
		assertFalse(resultado1, "Falló, extrajo con saldo en 0 y un monto mayor al descubierto.");
		assertFalse(resultado2, "Falló, extrajo un monto negativo.");
		assertTrue(resultado3, "Falló, no se extrajo el monto correspondiente.");
		
		// Annihilate
	}
	
	@Test
	void transfiereCorrectamente() {
		
		// Arrange
		Cuenta destino = new CuentaDeAhorros();
		double deposito = 500d, transferencia = descubierto + 200d;
		boolean resultado1, resultado2, resultado3;
		
		// Act
		resultado1 = cc.transferir(destino, transferencia); // Fallo
		resultado2 = cc.transferir(destino, -transferencia); // Fallo
		cc.depositar(deposito);
		resultado3 = cc.transferir(destino, transferencia); // Éxito
		
		// Assert
		assertEquals(cc.consultarSaldo(), deposito - transferencia, "Falló, no se transfirió el monto correspondiente.");
		assertEquals(destino.consultarSaldo(), transferencia, "Falló, no se transfirió el monto correspondiente.");
		assertFalse(resultado1, "Falló, se transfirió con saldo en 0 y un monto mayor al descubierto.");
		assertFalse(resultado2, "Falló, se transfirió un monto negativo.");
		assertTrue(resultado3, "Falló, no se transfirió el monto correspondiente.");
		
		// Annihilate
	}

}
