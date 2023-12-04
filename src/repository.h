/* Written by Kyrylo Pervushyn on 11/18/23 */
#ifndef EAGLEPAY_REPOSITORY_H
#define EAGLEPAY_REPOSITORY_H

#include <postgresql/libpq-fe.h>

template<class Type, class Id>
class Repository {
protected:
	PGconn *_connection;
public:
	explicit Repository(PGconn *connection) { _connection = connection; }
	virtual ~Repository() = 0;
};

/*class AddressRepository : public Repository<Address, int> {
public:
	explicit AddressRepository(PGconn *connection) : Repository(connection) { }
	virtual ~AddressRepository() { }
};
*/

#endif //EAGLEPAY_REPOSITORY_H
