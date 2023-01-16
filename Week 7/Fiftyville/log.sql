-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema;


SELECT * FROM crime_scene_reports
WHERE month = 7 AND day = 28;
-- Took place at 10:15am at the Humphrey Street bakery


SELECT * FROM interviews
WHERE year = 2021 AND month = 7 AND day >= 28;
-- Ruth say they leave the bakey parking lot within 10 mins of the theft
-- Eugene recognized the thieft in the morning at the ATM on Leggett Street withdrawing some money
-- Raymond said the thieft called someone and they talked for less than a minute, and the thieft say that they were planning the earliest flight tomorrow (the 29)


SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25;
-- Suspects licence plates:
-- 10:16     | exit     | 5P2BI95
-- 10:18     | exit     | 94KL13X -----> Biggest suspect
-- 10:18     | exit     | 6P58WS2
-- 10:19     | exit     | 4328GD8
-- 10:20     | exit     | G412CB7
-- 10:21     | exit     | L93JTIZ
-- 10:23     | exit     | 322W7JE
-- 10:23     | exit     | 0NTHK55


SELECT * FROM people
WHERE license_plate = "5P2BI95";
-- 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X


SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";
-- 28296815 | 2021 | 7 | 28 | Leggett Street | withdraw | 20


SELECT * FROM bank_accounts
WHERE account_number = 28296815;
-- person id: 686048


SELECT * FROM people
WHERE id = 686048;
-- suspect name: Bruce
-- suspect phone number: (367) 555-5533
-- suspect passport number: 5773159633
-- suspect licence plate: 94KL13X


SELECT * FROM phone_calls
WHERE caller = "(367) 555-5533";
-- Accomplice phone number: (375) 555-8161


SELECT * FROM people
WHERE phone_number = "(375) 555-8161";
-- Accomplice name: Robin


SELECT * FROM passengers
WHERE passport_number = 5773159633;
-- Bruce traveled in flight 36


SELECT * FROM flights
WHERE id = 36;
-- The destination of the flight is 4


SELECT * FROM airports;
-- 4  | LGA | LaGuardia Airport | New York City