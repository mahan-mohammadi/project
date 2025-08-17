#include <string>
#include <ctime>

using namespace std;

class UserUtils {
public:
    static bool isPassValid(string);
    static bool isUsernameValid(string);
    static string formatTimestamp(time_t);
};