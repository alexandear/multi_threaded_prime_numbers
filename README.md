# Client Server Prime Numbers

Client-server application (implement TCP-sockets) which calculates prime numbers for intervals.

## Continuos Integration

| Build server | Platform | Build status |
|--------------|----------|--------------|
| AppVeyor     | Windows  | [![Build status](https://ci.appveyor.com/api/projects/status/kpl6belbl8lo4lbd/branch/master?svg=true)](https://ci.appveyor.com/project/alexandear/multi-threaded-prime-numbers/branch/master) |
| Travis       | Linux    | [![Build Status](https://travis-ci.org/alexandear/multi_threaded_prime_numbers.svg?branch=master)](https://travis-ci.org/alexandear/multi_threaded_prime_numbers) |

## Code Coverage

[![codecov](https://codecov.io/gh/alexandear/multi_threaded_prime_numbers/branch/master/graph/badge.svg)](https://codecov.io/gh/alexandear/multi_threaded_prime_numbers)

## Description

### Client

1. Load intervals from specified xml-based file.
1. Start standalone thread for each interval:
   - Send request to Server to calculate prime numbers for each interval.
   - Receive prime numbers for each interval.
   - Store prime numbers to shared container;
1. Save unique prime numbers from shared container to xml-based file (primes tag);

### Server

1. Wait request from Client with interval.
1. For each interval start standalone thread for calculating prime numbers only.
1. Send calculated prime numbers back to Client.
