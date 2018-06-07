# nanosleep-cli
A linux shell wrapper for nanosleep() from coreutils.

This code will repeat nanosleep for the remaining time if it is interrupted, to ensure completion of the requested time.

## Build
`$ gcc -o nanosleep nanosleep.c`

## Usage
`$ nanosleep [time] [debug]`

time  - Positive long integer number of nanoseconds (Default: 1000)

debug - Any value, enabling debug output

## Examples
`$ ./nanosleep`

```
$ ./nanosleep 5000 1`
nanosleep called with 0 s + 5000 ns requested`
Nano sleep successfull for 0 s + 5000 ns
```

```
$ ./nanosleep 1100000000 1
nanosleep called with 1 s + 100000000 ns requested
Nano sleep successfull for 1 s + 100000000 ns
```

```
$ ./nanosleep -42 1
nanosleep called with 0 s + -42 ns requested
Please enter value between 0 and 2^63
```
