/* Written by Kyrylo Pervushyn on 12/11/23 */
#ifndef EAGLEPAY0_DEPOSIT_H
#define EAGLEPAY0_DEPOSIT_H

#include <string>
#include "../Utils.h"

using std::string;

class Deposit {
private:
	const long long int _id;
	const long long int _account_ipn;
	string _payout_card_number;
	double _amount;
	const double _intr_rate_year;
	Date _end_date;
	const unsigned int _years;

public:
	Deposit(const long long int id,
			const long long int account_ipn,
			string& payout_card,
			double amount,
			const double intr_rate_year,
			string& end_date,
			unsigned int years) :_id(id), _account_ipn(account_ipn), _payout_card_number(payout_card),
								 _amount(amount), _intr_rate_year(intr_rate_year), _end_date(end_date), _years(years) {}
	~Deposit() {

	};

	inline const long long int id() const { return _id; };
	inline const long long int account_ipn() const { return _account_ipn; };
	inline const string& number_payout_card() const { return _payout_card_number; };
	inline double amount() const { return _amount; };
	inline const double intr_rate_year() const { return _intr_rate_year; };
	inline const Date& end_date() const { return _end_date; };
	inline const unsigned int years() const { return _years; };
};

ostream& operator<<(ostream & os, const Deposit&);

#endif //EAGLEPAY0_DEPOSIT_H
