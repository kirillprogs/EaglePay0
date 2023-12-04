#pragma once
#include "ATM.h"

class ATMView
{
public:
	ATMView(ATM& atm) : _atm(atm) {}
	void run();

private:
	ATM& _atm;
};
