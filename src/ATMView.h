#pragma once
#include "ATM.h"

class ATMView
{
private:
	ATM& _atm;

public:
	ATMView(ATM& atm) : _atm(atm) {}
	void run();
};
