#include "Services/AuthService.hpp"
#include <iostream>

using namespace std;

bool AuthService::registerUser(string name, string email, string cnic, string pass) {
     
    for(const auto& u : m_users) {
        if(u.email == email || u.cnic == cnic) return false;
    }

    
    User newUser = { m_nextUserId++, name, email, cnic, pass };
    m_users.push_back(newUser);
    
    cout << "User Registered: " << name << " (Total: " << m_users.size() << ")" << endl;
    return true;
}

optional<User> AuthService::loginUser(string emailOrCnic, string password) {
    // Linear Search
    for(const auto& u : m_users) {
        if((u.email == emailOrCnic || u.cnic == emailOrCnic) && u.password == password) {
            return u;
        }
    }
    return nullopt;
}

string AuthService::createSession(int userId) {
    string token = "SESSION_" + to_string(rand());
    m_sessions[token] = userId;
    return token;
}

optional<int> AuthService::validateSession(string token) {
    if (m_sessions.count(token)) return m_sessions[token];
    return nullopt;
}

optional<User> AuthService::getUserById(int id) {
    for(const auto& u : m_users) {
        if(u.userID == id) return u;
    }
    return nullopt;
}