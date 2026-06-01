package state;

public class TankModeSiegeState implements TankState {

	@Override
	public TankState moverse() {
		return this;
	}
	
	@Override
	public TankState atacar() {
		return new TankModeTankState();
	}
	
}
