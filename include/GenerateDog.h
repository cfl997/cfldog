#include <string>

#ifdef WIN32


#ifdef GeneralDOG_EXPORTS
//#define GeneralDOG_API __declspec(dllexport)
//#else
//#define GeneralDOG_API __declspec(dllimport)
#define GeneralDOG_API 
#endif
#else// WIN32
#define GeneralDOG_API
#endif // WIN32

#ifdef GeneralDOG_EXPORTS
GeneralDOG_API std::string generate_key();

GeneralDOG_API std::string getLicenseByKey(const std::string& key);

GeneralDOG_API bool isSame(const std::string& DogData);

#else
std::string generate_key();

std::string getLicenseByKey(const std::string& key);

bool isSame(const std::string& DogData);
#endif
