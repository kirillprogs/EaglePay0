/* Written by Kyrylo Pervushyn on 12/11/23 */
#ifndef EAGLEPAY0_TRANSFERDAEMON_H
#define EAGLEPAY0_TRANSFERDAEMON_H

#include <string>
#include "../Utils.h"
#include "Transfer.h"

using std::string;

class TransferDaemon {
private:
	const long long int _td_id;
	bool _active;
	const string _number_card_from;
	const string _number_card_to;
	const double _amount;
	const Date _next_transfer_date;
	const Interval _frequency;


public:
	TransferDaemon(const long long int td_id,
				   string& card_from,
				   string& card_to,
				   double amount,
				   string& next_transfer_date,
				   string& frequency,
				   bool active = true) :_td_id(td_id), _active(active), _number_card_from(card_from), _number_card_to(card_to), _amount(amount),
										_next_transfer_date(next_transfer_date), _frequency(frequency) {};
	~TransferDaemon() {

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
};

ostream& operator<<(ostream& os, const TransferDaemon&);

#endif //EAGLEPAY0_TRANSFERDAEMON_H
