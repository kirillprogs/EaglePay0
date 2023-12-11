/* Written by Kyrylo Pervushyn on 12/11/23 */
#ifndef EAGLEPAY0_ACCOUNT_H
#define EAGLEPAY0_ACCOUNT_H

#include <string>
#include "../Utils.h"

using std::string;

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

ostream& operator<<(ostream& os, const Account&);

#endif //EAGLEPAY0_ACCOUNT_H
