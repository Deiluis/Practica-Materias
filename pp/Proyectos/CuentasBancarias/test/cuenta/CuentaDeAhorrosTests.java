package cuenta;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class CuentaDeAhorrosTests {

	CuentaDeAhorros ca;
	
	@BeforeEach
	void prepararTests() {
		ca = new CuentaDeAhorros();
	}
	
	@Test
	void ahorrosComienzaEnCero() {
		
		// Arrange
		double ahorros;
		
		// Act
		ahorros = ca.consultarAhorros();
		
		// Assert
		assertEquals(ahorros, 0, "Falló, no comienza en 0.");
		
		// Annihilate
	}
	
	@Test
	void reservaAhorrosCorrectamente() {
		
		// Arrange
		double deposito = 500d, ahorros = 200d;
		boolean resultado1, resultado2, resultado3;
		
		// Act
		resultado1 = ca.reservarAhorros(ahorros); // Fallo
		resultado2 = ca.reservarAhorros(-ahorros); // Fallo
		ca.depositar(deposito);
		resultado3 = ca.reservarAhorros(ahorros); // Éxito
		
		// Assert
		assertEquals(ca.consultarSaldo(), deposito - ahorros, "Falló, no se reservó el monto correspondiente.");
		assertEquals(ca.consultarAhorros(), ahorros, "Falló, no se reservó el monto correspondiente.");
		assertFalse(resultado1, "Falló, se reservó con saldo en 0.");
		assertFalse(resultado2, "Falló, se reservó un monto negativo.");
		assertTrue(resultado3, "Falló, no se reservó el monto correspondiente.");
		
		// Annihilate
	}

	@Test
	void reintegraAhorrosCorrectamente() {
		
		// Arrange
		double deposito = 500d, ahorros = 200d;
		boolean resultado1, resultado2, resultado3;
		
		ca.depositar(deposito);
		
		// Act
		resultado1 = ca.reintegrarAhorros(ahorros); // Fallo
		resultado2 = ca.reintegrarAhorros(-ahorros); // Fallo
		ca.reservarAhorros(ahorros);
		resultado3 = ca.reintegrarAhorros(ahorros); // Éxito
		
		// Assert
		assertEquals(ca.consultarSaldo(), deposito, "Falló, no se reintegró el monto correspondiente.");
		assertEquals(ca.consultarAhorros(), 0, "Falló, no se reintegró el monto correspondiente.");
		assertFalse(resultado1, "Falló, se reintegró con ahorros en 0.");
		assertFalse(resultado2, "Falló, se reintegró un monto negativo.");
		assertTrue(resultado3, "Falló, no se reintegró el monto correspondiente.");
		
		// Annihilate
	}
	
}
