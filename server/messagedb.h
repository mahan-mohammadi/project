#include "message.h"

class MessageDB {
private:
    static string getFileName(int, int);
public:
    static void saveMessage(Message);
    // returns the number of the messages
    static json getMessagesOf(int, int );
};
