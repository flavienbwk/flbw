# What is FLBW ?

FLBW is a dynamic and lightweight C++ encryption algorithm allowing you to encrypt a string with or without a password.

This algorithm generates a different string each time the same plain string is submitted, even with the same password.  
It also provides a customisable difficulty bruteforce protection.

Actual version : _(cpp)_ __0.7__

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
flbw enc[bp 250000] password string # Add "bp" if you want to enable "bruteforce protection".
flbw encf[bp 250000] password file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw encbyf[bp 250000] passwordfile.txt file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.

> For decryption :
flbw dec[bp 250000] password encryptedstring
flbw decf[bp 250000] password encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw decbyf[bp 250000] passwordfile.txt encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
```

The `[bp 250000]` sequence is optional. It is used to enable bruteforce protection to a difficulty of `250000`.  
You can modify it at your will, `250000` is just a reference.

## Bruteforce protection

:warning: Enabling bruteforce protection greatly increases the security of your encryption but also greatly increases the encryption/decryption time.

:warning: The version __0.6__ of FLBW introduces the possibility to encrypt with bruteforce protection for decryption. While it's working, it's not a long-term solution. It will be reviewed in the next releases.

## Tests

Instructions for tests are in the [`tests`](./tests) directory.

## Encryption mechanism

See the following schematics to understand how FLBW roughly work.

<p align="center">
    <img src="https://i.imgur.com/mUTqn5p.png"/>
</p>