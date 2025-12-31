#include "Services/QueueManager.hpp"
#include <iostream>
#include <vector>

using namespace std;



void QueueManager::initDummyData() {

    vector<string> departments = {"NADRA", "Passport", "License"};
    vector<string> branches = {"Gulshan", "NorthNazimabad", "NorthKarachi"};
    vector<string> categories = {"Normal", "Senior", "Urgent"};

   
    for (const auto& dept : departments) {
        for (const auto& branch : branches) {
            string fullBranchName = dept + "_" + branch; // e.g. NADRA_Gulshan
            
            for(int i=0; i<3; i++) {
                
                Token t = createToken(0, fullBranchName, categories[i%3], "10:00 AM");
                enqueueToken(t);
            }
        }
    }
    cout << "--- DUMMY DATA INITIALIZED (3 people in every branch) ---" << endl;
}

//  Constructor
QueueManager::QueueManager() {
    m_nextTokenId = 100;
    initDummyData(); 
}


Token QueueManager::createToken(int userId, string branch, string cat, string time) {
    Token t;
    t.tokenID = m_nextTokenId++;
    t.userID = userId;
    t.branchName = branch;
    t.category = cat;
    t.bookedTime = time;
    t.status = "Pending";
    t.tokenNumber = branch.substr(0,3) + "-" + to_string(t.tokenID);
    return t;
}

void QueueManager::enqueueToken(const Token& t) {
    m_queues[t.branchName].enqueue(t);
    cout << "Enqueued " << t.tokenNumber << " to " << t.branchName << endl;
}

vector<Token> QueueManager::getQueueList(string branch) {
    vector<Token> result;
    auto* current = m_queues[branch].get_head();
    while(current) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

Token QueueManager::serveNext(string branch) {
    if(m_queues[branch].isEmpty()) throw runtime_error("Queue empty");
    Token t = m_queues[branch].dequeue();
    t.status = "Served";
    m_history[branch].push(t);
    return t;
}

Token QueueManager::undoServe(string branch) {
    if(m_history[branch].isEmpty()) throw runtime_error("No history to undo");
    Token t = m_history[branch].pop();
    t.status = "Pending"; 
    m_queues[branch].enqueue_front(t);
    return t;
}