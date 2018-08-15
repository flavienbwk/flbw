# What is FLBW ?

FLBW is a dynamic C++ encryption algorithm allowing you to encrypt a string with or without a password.

By dynamic, it means able to return a different string each time the same plain string is submitted.

Actual version : __0.1__
We use [CryptoPP](https://github.com/weidai11/cryptopp) for the hash algorithms.

You can play a [demo here via a web interface](http://flavien.berwick.fr/projects/flbw) (PHP version of the algorithm).

## Installation

Classic install :

```bash
make
./flbw # ... (see usage below)
```

Tests & benchmark install :

```bash
make test
./flbw_test
```

## Usage

You have two ways of using the FLBW algorithm :
- Encrypt or decrypt a __string__.
- Encrypt or decrypt a __file__.


```bash
./flbw 1 mypassword mystring # Encrypt mystring with mypassword, and prints the result
./flbw 2 mypassword VGhhdCdzIGp1c3QgYSBkZW1v # Decrypt a string with mypassword, and prints the result

./flbw 3 mypassword myfile.txt # Encrypt the content of myfile.txt with mypassword, and prints the result
./flbw 3 mypassword myfile.txt output.txt # Encrypt the content of myfile.txt with mypassword, and saves the result in output.txt
./flbw 4 mypassword output.txt # Decrypt the content of output.txt with mypassword, and prints the result
```

:information_source: To test and benchmark FLBW on your machine, you can use the following command to generate a Lorem Ipsum text file : `./text_generator > myfile.txt`, in combination with the `./flbw 4 [...]` command.

## Functioning

See the following schematics to understand how FLBW roughly work.

### Encryption mechanism

<img align="center" src="https://i.imgur.com/mUTqn5p.png"/>