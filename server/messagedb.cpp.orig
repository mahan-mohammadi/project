#include "messagedb.h"
#include <fstream>

string MessageDB::getFileName(int userId1 , int userId2){
    int smallerId;
    int largerId;

    if (userId1 < userId2) {
        smallerId = userId1;
        largerId = userId2;
    } else {
        smallerId = userId2;
        largerId = userId1;
    }

    return to_string(smallerId) + "-" + to_string(largerId) + ".json";

}

void MessageDB::saveMessage(Message message){
    string filename = getFileName(message.getSenderId(), message.getReciverId());
    json chatJson;
    ifstream inputFile(filename);
    if (inputFile.good()) {
        
        inputFile >> chatJson;
    }

    //to check if it empty
    if (!chatJson.is_array()) {
        chatJson = json::array();
    }

    inputFile.close();

    chatJson.push_back(message.toJson());

    ofstream outputFile(filename);
    
    outputFile << chatJson.dump(2);
    outputFile.close();
}

// returns the number of the message
json MessageDB::getMessagesOf(int userID , int contactID){
    string filename = getFileName(userID , contactID);
    ifstream inputFile(filename);

    if (!inputFile.good()) {
        // no file so we exit.
        return json::array();
    }

    json chatJson;
    inputFile >> chatJson;
    inputFile.close();

    return chatJson;
}