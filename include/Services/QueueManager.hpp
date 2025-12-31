#pragma once
#include <map>
#include <vector>
#include <string>
#include "../DataStructures/Queue.hpp"
#include "../DataStructures/Stack.hpp"
#include "../DataStructures/Token.hpp"

class QueueManager {
public:
    static QueueManager& getInstance() {
        static QueueManager instance;
        return instance;
    }

    Token createToken(int userId, std::string branch, std::string cat, std::string time);
    void enqueueToken(const Token& token);
    std::vector<Token> getQueueList(std::string branch);
    Token serveNext(std::string branch);
    Token undoServe(std::string branch);

private:
   
    QueueManager(); 
    
    void initDummyData(); // New helper declaration

    std::map<std::string, Queue<Token>> m_queues;
    std::map<std::string, Stack<Token>> m_history;
    int m_nextTokenId;
};