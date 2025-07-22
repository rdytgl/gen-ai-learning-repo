-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Firstly, I manually looked at the crime_scene_reports table to look for
-- exact crime for more details. Here is what it said:
-- "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the
-- time – each of their interview transcripts mentions the bakery."

-- Given this, I am to look at the interviews table, matching the date of
-- July 28, 2024 and interviews that contain the word bakery
SELECT name, transcript FROM interviews
    WHERE
        year = 2024
        AND month = 7
        AND day = 28
        AND transcript LIKE '%bakery%';

-- We have gotten some idea on the identity of the thief. Let us first focus on
-- Ruth's account of the events.
SELECT people.name, people.license_plate
    FROM people
    JOIN bakery_security_logs bsl1 ON bsl1.license_plate = people.license_plate
    WHERE
        bsl1.year = 2024
        AND bsl1.month = 7
        AND bsl1.day = 28
        AND bsl1.hour = 10
        AND bsl1.minute >= 15
        AND bsl1.minute <= 25
        AND bsl1.activity = 'exit';

-- We currently have 8 suspects based on Ruth's account. We will now tackle
-- Eugene's account of events so we can further narrow down the suspect list

SELECT people.name, ba.account_number
    FROM people
    JOIN bank_accounts ba ON people.id = ba.person_id
    JOIN atm_transactions atm ON ba.account_number = atm.account_number
    WHERE
        atm.year = 2024
        AND atm.month = 7
        AND atm.day = 28
        AND atm.atm_location = 'Leggett Street'
        AND atm.transaction_type = 'withdraw';

-- Finally tackling Ramond's testimony, let's focus on the phone calls first.
SELECT
    caller.name AS caller_name,
    receiver.name AS receiver_name,
    phone_calls.duration
    FROM phone_calls
    JOIN people AS caller ON phone_calls.caller = caller.phone_number
    JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
    WHERE
        phone_calls.duration < 60
        AND phone_calls.year = 2024
        AND phone_calls.month = 7
        AND phone_calls.day = 28;

-- Based on Raymond's account, the suspect mentioned that they will get on the first
-- flight out of Fiftyville. Let's get the flight details first:
SELECT
    flights.id,
    flights.hour,
    flights.minute,
    origin.abbreviation AS origin_icao,
    origin.full_name AS origin_airport,
    origin.city AS origin_city,
    dest.abbreviation AS dest_icao,
    dest.full_name AS dest_airport,
    dest.city AS dest_city
    FROM flights
    JOIN airports AS origin ON flights.origin_airport_id = origin.id
    JOIN airports AS dest ON flights.destination_airport_id = dest.id
    WHERE
        flights.year = 2024
        AND flights.month = 7
        AND flights.day = 29
        AND origin.city = 'Fiftyville'
        ORDER BY flights.hour, flights.minute
        LIMIT 1;

-- We now know that the suspect has fled Fiftyville at 8:20 AM and is bound for
-- New York City (LGA). We got flight_id 36 here but I also want to not assume this.
-- Thus I would use subquery here
SELECT people.name, passengers.flight_id, passengers.passport_number
    FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE passengers.flight_id IN (
        SELECT
        flights.id
        FROM flights
        JOIN airports AS origin ON flights.origin_airport_id = origin.id
        WHERE
            flights.year = 2024
            AND flights.month = 7
            AND flights.day = 29
            AND origin.city = 'Fiftyville'
            ORDER BY flights.hour, flights.minute
            LIMIT 1
    );

-- By this time, we have determined that:
-- The suspect is Bruce,
-- fleeing to New York City
-- and was helped by Robin
