#pragma once
#include <string>
#include "crow.h"


struct Token {
    int tokenID;
    int userID;
    std::string branchName;
    std::string tokenNumber;
    std::string category;
    std::string status;
    std::string bookedTime;

    crow::json::wvalue toJson() const {
        crow::json::wvalue json;
        json["tokenID"] = tokenID;
        json["userID"] = userID;
        json["branchName"] = branchName;
        json["tokenNumber"] = tokenNumber;
        json["category"] = category;
        json["status"] = status;
        json["bookedTime"] = bookedTime;
        return json;
    }
};