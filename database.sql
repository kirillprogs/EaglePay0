DROP TABLE regularPayment;
DROP TABLE deposit;
DROP TABLE transfer;
DROP TABLE transferDaemon;
DROP TABLE card;
DROP TABLE account;
DROP TABLE person;

CREATE TABLE person
(
    ipn        INTEGER     PRIMARY KEY,
    passport   CHAR(8)     UNIQUE,
    pib        VARCHAR(50) NOT NULL,
    birth_date DATE        NOT NULL,
    email      VARCHAR(50) NOT NULL
);

CREATE TABLE account
(
    ipn        INTEGER     PRIMARY KEY,
    pib        VARCHAR(50) NOT NULL,
    birth_date DATE        NOT NULL,
    init_date  DATE        NOT NULL DEFAULT CURRENT_DATE,
    email      VARCHAR(50) NOT NULL
);

CREATE TABLE card
(
    card_number CHAR(16)     PRIMARY KEY,
    pin_code    CHAR(4)      NOT NULL,
    ipn         INTEGER      NOT NULL,
    balance     NUMERIC(8,2) NOT NULL,
    init_date   DATE         NOT NULL DEFAULT CURRENT_DATE,
    end_date    DATE         NOT NULL DEFAULT (CURRENT_DATE + interval '5 years'),
    FOREIGN KEY (ipn)
        REFERENCES account (ipn)
);

CREATE TABLE transferDaemon
(
    tr_d_id            SERIAL       PRIMARY KEY,
    card_from          CHAR(16)     NOT NULL,
    card_to            CHAR(16)     NOT NULL,
    amount             NUMERIC(8,2) NOT NULL,
    next_transfer_date DATE         NOT NULL,
    frequency          INTERVAL     NOT NULL,
    FOREIGN KEY (card_from)
        references card (card_number),
    FOREIGN KEY (card_to)
        references card (card_number)
);

CREATE TABLE transfer
(
    tr_id     SERIAL       PRIMARY KEY,
    card_from CHAR(16)     NOT NULL,
    card_to   CHAR(16)     NOT NULL,
    amount    NUMERIC(8,2) NOT NULL,
    tr_d_id   INTEGER,
    FOREIGN KEY (card_from)
        references card (card_number),
    FOREIGN KEY (card_to)
        references card (card_number),
    FOREIGN KEY (tr_d_id)
        REFERENCES transferDaemon( tr_d_id)
);

CREATE TABLE deposit
(
    dep_id         SERIAL  PRIMARY KEY,
    ipn            INTEGER      NOT NULL,
    payout_card    CHAR(16)     NOT NULL,
    amount         NUMERIC(8,2) NOT NULL,
    intr_rate_year NUMERIC(4,3) NOT NULL,
    end_date       DATE         NOT NULL,
    years          INTEGER      NOT NULL,
    FOREIGN KEY (ipn)
        REFERENCES account (ipn),
    FOREIGN KEY (payout_card)
        references card (card_number)
);

CREATE TABLE regularPayment
(
    id         SERIAL       PRIMARY KEY,
    from_acc   INTEGER      NOT NULL,
    to_acc     INTEGER      NOT NULL,
    amount     NUMERIC(8,2) NOT NULL,
    setup_date DATE         NOT NULL     DEFAULT CURRENT_DATE,
    diff_days  INTEGER      NOT NULL,
    end_date   DATE         NOT NULL     DEFAULT CURRENT_DATE,
    FOREIGN KEY (from_acc)
        REFERENCES account (ipn),
    FOREIGN KEY (to_acc)
        REFERENCES account (ipn)
);

/* Populate tables with initial data */
