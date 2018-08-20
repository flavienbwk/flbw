# What is FLBW ?

FLBW is a dynamic and lightweight C++ encryption algorithm allowing you to encrypt a string with or without a password.

This algorithm generates a different string each time the same plain string is submitted, even with the same password.

Actual version : _(cpp)_ __0.5__

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
flbw enc password string
flbw encf password file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw encbyf passwordfile.txt file.txt [encrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.

> For decryption :
flbw dec password encryptedstring
flbw decf password encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
flbw decbyf passwordfile.txt encryptedfile.txt [decrypted_destination.txt] # Last parameter is optional, the result will be printed if not specified.
```

:information_source: To test and benchmark FLBW on your machine, you can use the following command to generate a Lorem Ipsum text file : `./text_generator > myfile.txt`, in combination with the `./flbw 4 [...]` command.

## Tests


:white_check_mark: Test of integrity & benchmark (TIB) :
```bash
make tib 
./tib
```

:white_check_mark: Test of random attack (RA) :
```bash
make tra
./tra
```

:white_check_mark: Test of files integrity (FI) :
```bash
make tfi
./tfi
```

## Functioning

See the following schematics to understand how FLBW roughly work.

### Encryption mechanism

<p align="center">
    <img src="https://i.imgur.com/mUTqn5p.png"/>
</p>