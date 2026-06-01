package state;

public class Tank {

	private TankState estado;
	
	public void moverse() {
		estado = estado.moverse();
	}
	
	public void atacar() {
		estado = estado.atacar();
	}
	
}