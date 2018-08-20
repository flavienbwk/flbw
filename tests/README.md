# Test files

You can compile and run thoses test files by running `make test` from the root project directory.

:information_source: **Tip for benchmarking** : the `time` linux command displays the execution time of a command. Example: `time flbw enc password mytext`.

## Tests

:white_check_mark: Test of integrity & benchmark (TIB) :
```bash
make tib 
./tib
```

:white_check_mark: Test of integrity & benchmark with bruteforce protection (TIBP) :
```bash
make tibp
./tibp
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

## Text generator

You will fin a text generator under `./text_generator` for you to generate a bunch of data.

Use it like that :
```bash
apt-get install libtext-lorem-perl -y   # Install the dependency.
./text_generator.sh > generated.txt     # Save the lorem ipsum in "generated.txt".
```

You could easily make your own benchmark the algorithm by for example running :
```bash
./text_generator.sh > generated.txt
time flbw encf password generated.txt encrypted.txt
time flbw decf password encrypted.txt decrypted.txt
```