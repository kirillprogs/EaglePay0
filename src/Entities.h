#pragma once
#include <iostream>
#include "Utils.h"
using std::string;
using std::ostream;

class Account {
private:
	const long long int _ipn;
	const string _pib;
	const Date _birth_date;
	const Date _init_date;
	const string _email;
public:
	Account(long long int ipn,
			string& pib,
			string& birth_date,
			string& init_date,
			string& email) : _ipn(ipn), _pib(pib), _birth_date(Date(birth_date)),
							 _init_date(Date(init_date)), _email(email) {};

	~Account() {};
	inline long long int ipn() const { return _ipn; };
	inline const string& pib() const { return _pib; };
	inline const Date& birth_date() const { return _birth_date; };
	inline const Date& init_date() const { return _init_date; };
	inline const string& email() const { return _email; };
};

class Card {
private:
	const string _card_number;
	string _pin_code;
	const long long int _account_ipn;
	double _balance;
	const Date _init_date;
	const Date _end_date;
	Account* _account;

	void loadAccount();
public:

	Card(string& card_number,
		 string& pin_code,
		 long long int account_ipn,
		 double balance,
		 string& init_date,
		 string& end_date) : _card_number(card_number), _pin_code(pin_code), _account_ipn(account_ipn),
							 _balance(balance), _init_date(Date(init_date)), _end_date(Date(end_date)), _account(0) {};
	~Card() {
		if (_account != 0)
			delete _account;
	}
	inline const string& card_number() const { return _card_number; };
	inline const string& pin_code() const { return _pin_code; };
	inline long long int account_ipn() const { return _account_ipn; };
	inline double balance() const { return _balance; };
	inline const Date& init_date() const { return _init_date; };
	inline const Date& end_date() const { return _end_date; };

	inline const Account& account()
	{
		if (_account == 0)
			loadAccount();
		return *_account;
	};

	void setPinCode(string&);
	double put(double amount);
	double withdraw(double amount);
};

class Transfer {
private:
	const long long int _transfer_id;
	const string _number_card_from;
	const string _number_card_to;
	const double _amount;
	const Date _date;

	Card* _card_from;
	Card* _card_to;

	void loadCardFrom();
	void loadCardTo();

public:
	Transfer(long long int transfer_id,
			 string& number_card_from,
			 string& number_card_to,
			 double amount,
			 string& date) : _transfer_id(transfer_id), _number_card_from(number_card_from),
							 _number_card_to(number_card_to), _amount(amount), _date(Date(date)), _card_from(0), _card_to(0) {};
	~Transfer() {
		if (_card_from != 0)
			delete _card_from;
		if (_card_to != 0)
			delete _card_to;
	}

	inline long long int transfer_id() const { return _transfer_id; }
	inline const string& number_card_from() const { return _number_card_from; }
	inline const string& number_card_to() const { return _number_card_to; };
	inline double amount() const { return _amount; };
	inline const Date& date() const { return _date; };

	inline Card& card_from() {
		if (_card_from == 0)
			loadCardFrom();
		return *_card_from;
	};
	inline Card& card_to() {
		if (_card_to == 0)
			loadCardTo();
		return *_card_to;
	};
};

class TransferDaemon {
private:
	const long long int _td_id;
	bool _active;
	const string _number_card_from;
	const string _number_card_to;
	const double _amount;
	const Date _next_transfer_date;
	const Interval _frequency;
	Transfer* _transfers;
	Card* _card_from;
	Card* _card_to;
	void loadTransfers();
	void loadCardFrom();
	void loadCardTo();

public:
	TransferDaemon(const long long int td_id,
				   string& card_from,
				   string& card_to,
				   double amount,
				   string& next_transfer_date,
				   string& frequency,
				   bool active = true) :_td_id(td_id), _active(active), _number_card_from(card_from), _number_card_to(card_to), _amount(amount),
									   _next_transfer_date(next_transfer_date), _frequency(frequency), _transfers(0),
									   _card_to(0), _card_from(0) {};
	~TransferDaemon() {
		if (_transfers != 0)
			delete[] _transfers;
		if (_card_from != 0)
			delete _card_from;
		if (_card_to != 0)
			delete _card_to;
	};

	Transfer& createTransfer();
	inline void deactivate() { _active = false; };
	inline void activate() { _active = true; };

	inline long long int td_id() const { return _td_id; };
	inline bool active() const { return _active; };
	inline const string& number_card_from() const { return _number_card_from; };
	inline const string& number_card_to() const { return _number_card_to; };
	inline double amount() const { return _amount; };
	inline const Date& next_transfer_date() const { return _next_transfer_date; };
	inline const Interval& frequency() const { return _frequency; };

	inline Transfer* transfers() {
		if (_transfers == 0)
			loadTransfers();
		return _transfers;
	};

	inline Card& card_from() {
		if (_card_from == 0)
			loadCardFrom();
		return *_card_from;
	};
	inline Card& card_to() {
		if (_card_to == 0)
			loadCardTo();
		return *_card_to;
	};

};

class Deposit {
private:
	const long long int _id;
	const long long int _account_ipn;
	string _number_payout_card;
	double _amount;
	const double _intr_rate_year;
	Date _end_date;
	const unsigned int _years;

	Account* _account;
	Card* _payout_card;

	void loadAccount();
	void loadCard();
public:
	Deposit(const long long int id,
			const long long int account_ipn,
			string& payout_card,
			double amount,
			const double intr_rate_year,
			string& end_date,
			unsigned int years) :_id(id), _account_ipn(account_ipn), _number_payout_card(payout_card),
								 _amount(amount), _intr_rate_year(intr_rate_year), _end_date(end_date), _years(years),
								 _account(0), _payout_card(0) {}
	~Deposit() {
		if (_account != 0)
			delete _account;
		if (_payout_card != 0)
			delete _payout_card;
	};

	inline const long long int id() const { return _id; };
	inline const long long int account_ipn() const { return _account_ipn; };
	inline const string& number_payout_card() const { return _number_payout_card; };
	inline double amount() const { return _amount; };
	inline const double intr_rate_year() const { return _intr_rate_year; };
	inline const Date& end_date() const { return _end_date; };
	inline const unsigned int years() const { return _years; };

	inline Account& account() {
		if (_account == 0)
			loadAccount();
		return *_account;
	};
	inline Card& payout_card() {
		if (_payout_card == 0)
			loadCard();
		return *_payout_card;

	};
};


ostream& operator<<(ostream& os, const Account&);
ostream& operator<<(ostream& os, const Card&);
ostream& operator<<(ostream& os, const Transfer&);
ostream& operator<<(ostream& os, const TransferDaemon&);
ostream& operator<<(ostream& os, const Deposit&);