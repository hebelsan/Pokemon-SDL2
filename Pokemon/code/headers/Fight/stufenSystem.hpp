/*
 * stufenSystem.hpp
 *
 *  Created on: 02.05.2018
 *      Author: Alexander
 */

#ifndef FIGHT_STUFENSYSTEM_HPP_
#define FIGHT_STUFENSYSTEM_HPP_

class StufenSystem{
public:
	StufenSystem() {
		_atkStufe = 0;
		_spzAtkStufe = 0;
		_defStufe = 0;
		_spzDefStufe = 0;
		_initStufe = 0;
	}

	void resetStufenSystem() {
		_atkStufe = 0;
		_spzAtkStufe = 0;
		_defStufe = 0;
		_spzDefStufe = 0;
		_initStufe = 0;
	}

	int getAtkStufe() const {
		return _atkStufe;
	}
	float getAtkFaktor() {
		return getFaktor(_atkStufe);
	}
	void increaseAtkStufe() {
		if (_atkStufe < 6)
			_atkStufe++;
	}
	void lowerAtkStufe(int atkStufe) {
		if (_atkStufe > -6)
			_atkStufe--;
	}

	int getDefStufe() const {
		return _defStufe;
	}
	float getDefFaktor() {
		return getFaktor(_defStufe);
	}
	void increaseDefStufe() {
		if (_defStufe < 6)
			_defStufe++;
	}
	void lowerDefStufe() {
		if (_defStufe > -6)
			_defStufe--;
	}

	int getInitStufe() const {
		return _initStufe;
	}
	float getInitFaktor() {
		return getFaktor(_initStufe);
	}
	void increaseInitStufe(int initStufe) {
		if (_initStufe < 6)
			_initStufe++;
	}
	void lowerInitStufe(int initStufe) {
		if (_initStufe > -6)
			_initStufe--;
	}

	int getSpzAtkStufe() const {
		return _spzAtkStufe;
	}
	float getSpzAtkFaktor() {
		return getFaktor(_spzAtkStufe);
	}
	void increaseSpzAtkStufe() {
		if (_spzAtkStufe < 6)
			_spzAtkStufe++;
	}
	void lowerSpzAtkStufe() {
		if (_spzAtkStufe > -6)
			_spzAtkStufe--;
	}

	int getSpzDefStufe() const {
		return _spzDefStufe;
	}
	float getSpzDefFaktor() {
		return getFaktor(_spzDefStufe);
	}
	void increaseSpzDefStufe(int spzDefStufe) {
		if (_spzDefStufe < 6)
			_spzDefStufe++;
	}
	void lowerSpzDefStufe(int spzDefStufe) {
		if (_spzDefStufe > -6)
			_spzDefStufe--;
	}

private:
	int _atkStufe;
	int _spzAtkStufe;
	int _defStufe;
	int _spzDefStufe;
	int _initStufe;

	float getFaktor(int stufe) {
		if (stufe >= 0) {
			return (1.0f + (stufe/(float)2));
		} else {
			return (2/ (2 + (-stufe)));
		}
	}
};



#endif /* FIGHT_STUFENSYSTEM_HPP_ */
