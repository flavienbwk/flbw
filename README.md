# What is FLBW ?

FLBW is a dynamic and lightweight C++ encryption algorithm allowing you to encrypt a string with or without a password.

This algorithm generates a different string each time the same plain string is submitted, even with the same password.
It also provides a customisable difficulty bruteforce protection.

Actual version : _(cpp)_ __0.6__

## Installation

Classic install for permanent usage :
```bash
sudo make install
flbw # ... (see usage below)
```

:information_source: You can uninstall with `sudo make uninstall`.

Classic install for temporary usage :
```bash
make
./flbw # ... (see usage below)
```

## Usage

You have two ways of using the FLBW algorithm :
- Encrypt or decrypt a __string__.
- Encrypt or decrypt a __file__.


```bash
> For encryption :
flbw enc[bp] password string # Add "bp" if you want to enable "bruteforce protection".
flbw encf[bp] password file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw encbyf[bp] passwordfile.txt file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.

> For decryption :
flbw dec[bp] password encryptedstring
flbw decf[bp] password encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw decbyf[bp] passwordfile.txt encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
```

:information_source: To test and benchmark FLBW on your machine, you can use the following command to generate a Lorem Ipsum text file : `./text_generator > myfile.txt`, in combination with the `./flbw 4 [...]` command.

## Bruteforce protection

By default, the bruteforce protection key and difficulty is `234567`.
You can modify it to increase your bruteforce protection in [`flbw.cpp`, line 10](flbw.cpp#L10).

:warning: Enabling bruteforce protection greatly increases the security of your encryption but also greatly increases the encryption/decryption time.

:warning: The version __0.6__ of FLBW introduces the possibility to encrypt with bruteforce protection for decryption. While it's working, it's not a long-term solution. It will be reviewed in the next releases.

## Tests

Instructions for tests are in the [`tests`](./tests) directory.

### Encryption mechanism

See the following schematics to understand how FLBW roughly work.

<p align="center">
    <img src="https://i.imgur.com/mUTqn5p.png"/>
</p>