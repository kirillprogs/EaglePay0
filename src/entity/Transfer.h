/* Written by Kyrylo Pervushyn on 12/11/23 */
#ifndef EAGLEPAY0_TRANSFER_H
#define EAGLEPAY0_TRANSFER_H

#include <string>
#include "../Utils.h"

using std::string;

class Transfer {
private:
	const long long int _transfer_id;
	const string _number_card_from;
	const string _number_card_to;
	const double _amount;
	const Date _date;

public:
	Transfer(long long int transfer_id,
			 string& number_card_from,
			 string& number_card_to,
			 double amount,
			 string& date) : _transfer_id(transfer_id), _number_card_from(number_card_from),
							 _number_card_to(number_card_to), _amount(amount), _date(Date(date)) {};
	~Transfer() {
	}

	inline long long int transfer_id() const { return _transfer_id; }
	inline const string& number_card_from() const { return _number_card_from; }
	inline const string& number_card_to() const { return _number_card_to; };
	inline double amount() const { return _amount; };
	inline const Date& date() const { return _date; };
};

ostream& operator<<(ostream& os, const Transfer&);

#endif //EAGLEPAY0_TRANSFER_H
