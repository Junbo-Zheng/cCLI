# cCLI - c Command Line Interface For Embedded Devices

## Overview
- Plain C Command Line Interface library for using in the embedded devices.
- It has been ported to the STM32 platform(STM32F407 with μcosIII RTOS), using the serial port as the command entry.
- Decoupled it as an independent library. It can run on any device, not just embedded devices. Of course, the most important thing is to provide debug capabilities for embedded devices.
- The current processing ends with the end character `\r\n`, which is not necessary, it can be modified according to the real environment.
- It is very lightweight and convenient, because only three APIs are provided to use：
  - cli_init: CLI library initial
      ```c++
      void cli_init(void);
      ```
  - cli_readline: The main entry point for cli to be received and processed data, which come from your terminal, or serial port, etc.
      ```c++
      void cli_readline(const char* data, uint16_t data_len);
      ```
  - cli_register: The debug commands to be processed need to be registered in advance
      ```c++
      int cli_register(const char* cmd, const char* brief, cli_cmd_func_t func);
      ```
- For debugging, I added [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) compile option. Of course, it is disabled by default, just ignore it if you don't care about it.

## Features highlights
- support command library argc max configure, it is 10 by default
- support command library console prompt configure, it is `cli>` by default
- support command library console log, it should be replaced with your log module, such as `syslog`
- support command library console log level configure, it is `CLI_LOG_LEVEL_ALL` by default
- support help command register by default, it would help to show all cli register command list
- support `str2hex` and `str2dec` function to parse command arguments
- blazing fast, non-blocking
- dedicated for embedded systems
- multi-platform and portable

## Licensing
[cCLI](https://github.com/Junbo-Zheng/cCLI) is licensed under the Apache license, Check the [LICENSE](./LICENSE) file.

## Getting Started
Clone the repo, install dependencies, and serve:
```shell
sudo apt-get install -y cmake gcc git
git clone git@github.com:Junbo-Zheng/cCLI.git
```

### Build on Ubuntu 20.04.5 LTS and macOS 13.3
```shell
$ mkdir -p build
$ cd build
$ cmake ..
$ make -j
$ ./cCli
```
Or even better for build:
```shell
$ cmake -H. -Bbuild
$ cd --build build -j # add `-j <n>` with cmake >= 3.12
$ ./build/cCli
```

### Run
[demo.c](./demo.c) provides a basic demo version, which help us learn how to use the cli library.

Run `./build/cCLI` if you build success, as follow:
```shell
➜  /Users/junbozheng/project/cCLI git:(master) ./build/cCLI 
[INFO] [cli_init:126]: cli init, build time: Wed Apr  5 23:20:48 2023
cli>
cli>date
cli date func
Thu Apr  6 00:06:29 2023
cli>
cli>help
[DEBUG] [cli_help:112]: help -> help
[DEBUG] [cli_help:112]: test -> cli test
[DEBUG] [cli_help:112]: date -> cli date
[DEBUG] [cli_help:112]: hello -> hello
[DEBUG] [cli_help:112]: str2dec -> str to dec
[DEBUG] [cli_help:112]: str2hex -> str to hex
cli>
cli>test
cli test func
cli>
cli>hello
cli hello func
cli>
cli>cli
[WARN] [cli_cmd_check:44]: Not find cli cmd, please type 'help' for help.
cli>
```

## Contribute
Anyone is welcome to contribute. Simply fork this repository, make your changes in an own branch and create a pull-request for your change. Please do only one change per pull-request.

You found a bug? Please fill out an issue and include any data to reproduce the bug.

## Contributor
- [Junbo Zheng](https://github.com/Junbo-Zheng)
