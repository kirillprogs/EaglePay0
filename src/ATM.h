#pragma once
#include <iostream>
#include "Bank.h"
#include <map>

class ATM
{
private:
	unsigned int _ATM_id;
	const Bank& _bank;
	std::string _address;
	Card* _card;
	std::map<double, unsigned int> _deposits_info;

	std::string _error_message;
public:
	ATM(unsigned int ATM_id, const Bank& bank, const std::string& address) : _ATM_id(ATM_id), _bank(bank), _address(address)
	{
		_deposits_info[0.01] = 1;          // interest rate = 1%, interval - 1 year
		_deposits_info[0.02] = 2;          // interest rate = 2%, interval - 2 year
		_deposits_info[0.03] = 3;		   // interest rate = 3%, interval - 3 year
	}

	bool loadCard();
	bool checkPin(const char*);
	inline unsigned int getId() { return _ATM_id; }
	inline const std::string& getBankName() { return _bank.getName(); }
	inline const std::string& getAddress() { return _address; }
	inline const std::map<double, unsigned int>& getDepInfo() { return _deposits_info; }
	bool makeTransfer(const char*, double);
	bool createDeposit(long long int, const char*, double amount, double rate, const Interval&);
	bool createTransferDaemon(const char*, double, const Date&, const Interval&);
	bool cashOut(double);
	bool cashIn(double);

	inline const Card* getCard() { return _card; };

};