/* Written by Kyrylo Pervushyn on 12/11/23 */
#ifndef EAGLEPAY0_CARD_H
#define EAGLEPAY0_CARD_H

#include <string>
#include "../Utils.h"

using std::string;

class Card {
private:
	const string _card_number;
	string _pin_code;
	const long long int _account_ipn;
	double _balance;
	const Date _init_date;
	const Date _end_date;

public:

	Card(string& card_number,
		 string& pin_code,
		 long long int account_ipn,
		 double balance,
		 string& init_date,
		 string& end_date) : _card_number(card_number), _pin_code(pin_code), _account_ipn(account_ipn),
							 _balance(balance), _init_date(Date(init_date)), _end_date(Date(end_date)) {};
	~Card() {}
	inline const string& card_number() const { return _card_number; };
	inline const string& pin_code() const { return _pin_code; };
	inline long long int account_ipn() const { return _account_ipn; };
	inline double balance() const { return _balance; };
	inline const Date& init_date() const { return _init_date; };
	inline const Date& end_date() const { return _end_date; };


	void setPinCode(string&);
	double put(double amount);
	double withdraw(double amount);
};

ostream& operator<<(ostream& os, const Card&);

#endif //EAGLEPAY0_CARD_H
