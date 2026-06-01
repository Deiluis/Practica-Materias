package state;

public class TankModeTankState implements TankState {

	@Override
	public TankState moverse() {
		return new TankModeSiegeState();
	}
	
	@Override
	public TankState atacar() {
		return this;
	}
}
