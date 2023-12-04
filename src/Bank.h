#pragma once
#include <string>
#include "Entities.h"
#include <postgresql/libpq-fe.h>

class Bank
{
public:
	Bank(std::string name, PGconn* connection) : _name(name), _connection(connection) {}

	inline const std::string& getName() const { return _name; }

	inline bool isConnected() const { return _connection != nullptr; }
	Card* getCard (const char* card_number) const;
	Account* getAccount(unsigned long long _ipn) const;
	ErrorType* makeTransfer(const char* card_number_from, const char* card_number_to, double amount) const;
	void cashOut(const char* card_number, double amount) const;
	void cashIn(const char* card_number, double amount) const;
	ErrorType* createTransferDaemon(const char* card_number_from, const char* card_number_to, double amount, Interval frequency, Date init_date) const;
	ErrorType* makeDeposit(unsigned long long _ipn, const char* payout_card_number, double amount, double rate, double years, Date end_date) const;


private:
	std::string _name;
	PGconn* _connection;
};

enum class ErrorType
{
	CARD_IS_NOT_FOUND,
	CARD_IS_EXPIRED
};