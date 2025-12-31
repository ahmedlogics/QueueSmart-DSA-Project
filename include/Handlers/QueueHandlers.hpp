#pragma once
#include "crow.h"
#include <string> 

class QueueHandlers {
public:
    // Define the functions as static so main.cpp can call them directly
    static crow::response handleBookToken(const crow::request& req);
    
    
    static crow::response handleGetQueueStatus(const crow::request& req, std::string branch);
    
    static crow::response handleServeNextToken(const crow::request& req, std::string branch);
    
    static crow::response handleUndoToken(const crow::request& req, std::string branch);
}; 