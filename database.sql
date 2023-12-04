DROP TABLE person;
DROP TABLE deposit;
DROP TABLE transfer;
DROP TABLE transferDaemon;
DROP TABLE card;
DROP TABLE account;

CREATE TABLE account
(
    ipn       INTEGER PRIMARY KEY,
    pib       VARCHAR(50) NOT NULL,
    age       INT         NOT NULL,
    init_date DATE DEFAULT CURRENT_DATE,
    email     VARCHAR(50)
);

CREATE TABLE card
(
    card_number CHAR(16) PRIMARY KEY,
    pin_code char(4) NOT NULL,
    ipn INTEGER NOT NULL,
    balance NUMERIC(8,2) NOT NULL,
    init_date DATE NOT NULL DEFAULT CURRENT_DATE,
    end_date DATE NOT NULL DEFAULT (CURRENT_DATE + interval '5 years'),
    FOREIGN KEY (ipn)
        REFERENCES account (ipn)
);

CREATE TABLE transferDaemon
(
    tr_d_id SERIAL PRIMARY KEY,
    card_from CHAR(16) NOT NULL,
    card_to CHAR(16) NOT NULL,
    amount NUMERIC(8,2) NOT NULL,
    next_transfer_date DATE NOT NULL,
    frequency INTERVAL NOT NULL,
    FOREIGN KEY (card_from)
        references card (card_number),
    FOREIGN KEY (card_to)
        references card (card_number)
);

CREATE TABLE transfer
(
    tr_id SERIAL PRIMARY KEY,
    card_from CHAR(16) NOT NULL,
    card_to CHAR(16) NOT NULL,
    amount NUMERIC(8,2) NOT NULL,
    tr_d_id INTEGER,
    FOREIGN KEY (card_from)
        references card (card_number),
    FOREIGN KEY (card_to)
        references card (card_number),
    FOREIGN KEY (tr_d_id)
        REFERENCES transferDaemon( tr_d_id)
);

CREATE TABLE deposit
(
    dep_id SERIAL PRIMARY KEY,
    ipn INTEGER NOT NULL,
    payout_card char(16) NOT NULL,
    amount NUMERIC(8,2) NOT NULL,
    intr_rate_year NUMERIC(4,3) NOT NULL,
    end_date DATE NOT NULL,
    years INTEGER NOT NULL,
    FOREIGN KEY (ipn)
        REFERENCES account (ipn),
    FOREIGN KEY (payout_card)
        references card (card_number)
);
