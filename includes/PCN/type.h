#ifndef PCN_TYPE
#define PCN_TYPE
#include <unordered_map>
#include <string>
namespace PCN {
	enum INPUT_TYPE { HTTPS, HTTP,TCP, UDP, IMCP, STOP, EXIT, ALL , ETHHDR};

	std::unordered_map<std::string, INPUT_TYPE>  STATE_MENT({
		{"https", INPUT_TYPE::HTTPS},
		{"http", INPUT_TYPE::HTTP},
		{"tcp", INPUT_TYPE::TCP},
		{"imcp", INPUT_TYPE::IMCP},
		{"stop", INPUT_TYPE::STOP},
		{"exit", INPUT_TYPE::EXIT},
		{"start", INPUT_TYPE::ALL},
		{"ethhdr",INPUT_TYPE::ETHHDR}
		});
}


#endif