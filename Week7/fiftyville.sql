-- Keep a log of any SQL queries you execute AS you solve the mystery.
-- All you know is that the theft took place on July 28, 2023 and that it took place ON Humphrey Street.
-- Let's see crime report info
SELECT id,
       description
FROM crime_scene_reports
WHERE year = 2023
       AND month = 7
       AND day = 28
       AND street = 'Humphrey Street'
LIMIT 10;
-- took place at 10:15am; 3 witnesses mentioned bakery
-- Go to interviews info
SELECT name,
       transcript
FROM interviews
WHERE year = 2023
       AND month = 7
       AND day = 28
       AND transcript LIKE '%bakery%';
-- Ruth: security footage, 10 minutes within the theft --> bakery_security_logs
-- Eugene: thief withdraw some money from atm --> atm_transactions
-- Raymond: talked to them for less than a minute;plan to take earliest flight next day --> phone call
-- Let's see atm_transactions:
SELECT account_number
FROM atm_transactions
WHERE year = 2023
       AND month = 7
       AND day = 28
LIMIT 10;
-- what is transaction type:
SELECT transaction_type
FROM atm_transactions
LIMIT 10;
-- what is atm location:
SELECT atm_location
FROM atm_transactions
LIMIT 10;
-- atm suspect:
SELECT account_number,
       amount
FROM atm_transactions
WHERE year = 2023
       AND month = 7
       AND day = 28
       AND transaction_type = 'withdraw'
       AND atm_location = 'Humphrey Lane';
-- amount maybe related to ticket fee
-- got some account numbers, let's see who they are
-- suspects from atm_transactions:
SELECT name
FROM people
WHERE id IN (
              SELECT person_id
              FROM bank_accounts
              WHERE account_number IN (
                            SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2023
                                   AND month = 7
                                   AND day = 28
                                   AND transaction_type = 'withdraw'
                                   AND atm_location = 'Humphrey Lane'
                     )
       ) -- 
       -- suspects from security logs
SELECT *
FROM bakery_security_logs
WHERE year = 2023
       AND month = 7
       AND day = 28
       AND hour = 10
       AND minute BETWEEN 5 AND 25;
-- narrow down the suspect!!
-- if Raymond lies, then atm_transactions and bakery_security_logs are true:
SELECT p.name
FROM people AS p
       JOIN bakery_security_logs AS b ON p.license_plate = b.license_plate
       JOIN bank_accounts AS ba ON ba.person_id = p.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
WHERE a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane'
       AND b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 5 AND 25;
-- no result
-- suspects from phone call within 1 minute
SELECT *
FROM phone_calls
LIMIT 10;
SELECT *
FROM people
LIMIT 10;
-- duration is counted by sec
SELECT p.name
FROM people AS p
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- got some suspects from phone phone_calls
-- let's move to airport and flight information
SELECT *
FROM airports
LIMIT 10;
-- we should focus on airport CSF , id = 8
-- flights info can't identify who the thief is 
-- if Ruth lies,then atm_transactions and phone_calls are true:
SELECT name
FROM people AS p
       JOIN bank_accounts AS ba ON ba.person_id = p.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane'
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- no result
-- if Eugene lies, then bakery_security_logs and phone_calls are true:
SELECT p.name
FROM people AS p
       JOIN bakery_security_logs AS b ON b.license_plate = p.license_plate
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 5 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- 4 suspects?!2 Kelsey?
-- btw, I find that time frame should be 15 - 25
-- who make the phone call and drive out of bakery?
SELECT DISTINCT p.name,
       b.activity,
       b.minute
FROM people AS p
       JOIN bakery_security_logs AS b ON b.license_plate = p.license_plate
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- let's nest all together
SELECT DISTINCT p.name
FROM people AS p
       JOIN bank_accounts AS ba ON ba.person_id = p.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
       JOIN bakery_security_logs AS b ON b.license_plate = p.license_plate
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60
       AND a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane';
-- no result!
-- I reread the interviews with the three men, and my earlier judgment was wrong, and the three men's statements should be taken as correct
-- I suppose: the accomplice(other end of phone) get money and buy ticket
-- receiver get money
-- caller drive the car
-- so the caller is:
SELECT DISTINCT p.name
FROM people AS p
       JOIN bakery_security_logs AS b ON b.license_plate = p.license_plate
       JOIN phone_calls AS c ON p.phone_number = c.caller
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- Bruce, Sofia, Diana, Kelsey 
-- the receiver is: 
SELECT DISTINCT p.name
FROM people AS p
       JOIN bank_accounts AS ba ON ba.person_id = p.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
       JOIN phone_calls AS c ON p.phone_number = c.receiver
WHERE a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane'
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60;
-- Jack, Anna
-- oh,wait!!there is a passengers table!
-- .schema passengers
-- .schema flights
-- .schema airports
SELECT *
FROM airports;
-- CSF,id = 8
SELECT id,
       hour,
       minute
FROM flights
WHERE year = 2023
       AND month = 7
       AND day = 29
       AND origin_airport_id = 8
ORDER BY hour,
       minute;
-- the earliest flight is id = 36
-- let's see the passengers on this flight
SELECT name
FROM people AS p
       JOIN passengers AS pa ON p.passport_number = pa.passport_number
WHERE pa.flight_id = 36;
-- let's go back and see the phone calls!!
SELECT p1.name AS caller_name,
       p2.name AS receiver_name
FROM phone_calls c
       JOIN people p1 ON p1.phone_number = c.caller
       JOIN people p2 ON p2.phone_number = c.receiver
       JOIN bakery_security_logs AS b ON b.license_plate = p1.license_plate
       JOIN bank_accounts AS ba ON ba.person_id = p2.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60
       AND a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane';
-- only Sofia and Jack!
SELECT p1.name AS caller_name,
       p2.name AS receiver_name
FROM phone_calls c
       JOIN people p1 ON p1.phone_number = c.caller
       JOIN people p2 ON p2.phone_number = c.receiver
       JOIN bakery_security_logs AS b ON b.license_plate = p1.license_plate
       JOIN bank_accounts AS ba ON ba.person_id = p2.id
       JOIN atm_transactions AS a ON a.account_number = ba.account_number
       JOIN passengers AS pa ON p1.passport_number = pa.passport_number
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60
       AND a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Humphrey Lane'
       AND pa.flight_id = 36;
-- I add flight info this time, Sofia is ON THE PLANE!!!
-- Now, let's find out where did she go?
SELECT city
FROM airports a
WHERE a.id = (
              SELECT destination_airport_id
              FROM flights f
              WHERE f.origin_airport_id = 8
                     AND f.id = 36
       );
-- New York City, bro!
-- Oh no!
-- I reread the interviews with the three men and realized that I was wrong about the location of the ATM; and that the thief was the one who withdrew the money, drove away from the bakery, and made the phone call
-- the ATM is on Leggett Street!
SELECT p1.name AS caller_name,
       p2.name AS receiver_name
FROM phone_calls c
       JOIN people p1 ON p1.phone_number = c.caller
       JOIN people p2 ON p2.phone_number = c.receiver
       JOIN bakery_security_logs b ON b.license_plate = p1.license_plate
       JOIN bank_accounts ba ON ba.person_id = p1.id
       JOIN atm_transactions a ON a.account_number = ba.account_number
       JOIN passengers pa ON p1.passport_number = pa.passport_number
WHERE b.year = 2023
       AND b.month = 7
       AND b.day = 28
       AND b.hour = 10
       AND b.minute BETWEEN 15 AND 25
       AND c.year = 2023
       AND c.month = 7
       AND c.day = 28
       AND c.duration <= 60
       AND a.year = 2023
       AND a.month = 7
       AND a.day = 28
       AND a.transaction_type = 'withdraw'
       AND a.atm_location = 'Leggett Street'
       AND pa.flight_id = 36;
-- So, Bruce, Robin, NewYork
