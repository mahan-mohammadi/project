#include <string>
#include <ctime>

using namespace std;

class UserUtils {
public:
    static bool isPassValid(string);
    static bool isUsernameValid(string);
    //using time_t for consistency between systems int can be different
    static string formatTimestamp(time_t);
};