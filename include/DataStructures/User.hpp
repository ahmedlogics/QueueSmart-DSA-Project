#pragma once
#include <string>
#include "crow.h"

struct User {
    int userID;
    std::string fullName;
    std::string email;
    std::string cnic;
    std::string password; // Stored in RAM

    crow::json::wvalue toJson() const {
        crow::json::wvalue json;
        json["userID"] = userID;
        json["fullName"] = fullName;
        json["email"] = email;
        json["cnic"] = cnic;
        return json;
    }
};