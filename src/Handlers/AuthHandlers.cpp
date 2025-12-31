// src/Handlers/AuthHandlers.cpp

#include "Handlers/AuthHandlers.hpp"
#include "Services/AuthService.hpp"

using namespace std;

crow::response AuthHandlers::handleRegister(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) return crow::response(400);

  
    bool success = AuthService::getInstance().registerUser(
        body["fullName"].s(),
        body["email"].s(),
        body["cnic"].s(),
        body["password"].s()
    );

    if (success) return crow::response(200, "{\"message\":\"Registered\"}");
    return crow::response(400, "{\"message\":\"User already exists\"}");
}

crow::response AuthHandlers::handleLogin(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) return crow::response(400);

 
    auto user = AuthService::getInstance().loginUser(
        body["emailOrCnic"].s(),
        body["password"].s()
    );

    if (user) {
        crow::json::wvalue res;
        res["sessionToken"] = AuthService::getInstance().createSession(user->userID);
        res["user"] = user->toJson();
        return crow::response(200, res);
    }
    return crow::response(401, "{\"message\":\"Invalid Credentials\"}");
}


optional<int> AuthHandlers::getAuthenticatedUserId(const crow::request& req) {
    string token = req.get_header_value("Authorization");
    if (token.find("Bearer ") == 0) token = token.substr(7);
    return AuthService::getInstance().validateSession(token);
}