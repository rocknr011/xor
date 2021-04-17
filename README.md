# xor

Small and simple program that uses the **XOR** cipher to encrypt and decrypt files.

## Requirements

GCC compiler.

## Compilation

Run `make` command in root directory of the project.

## Usage

```
./xor --help
Usage: xor [options]

  -h, --help       Show help message and quit.
  -i, --in-file    Specify source file.
  -o, --out-file   Specify out file.
  -k, --key-file   Specify file contained xor key.
```

The program can also use _stdin/stdout_ and get _xor_ key from the environment
variable _XOR_KEY_.

## Goals

The code is written for real web-project and is used to encrypt configuration files. It is written in C for fun too.

## License

This project is licensed under the terms of the [MIT](LICENSE) license.
