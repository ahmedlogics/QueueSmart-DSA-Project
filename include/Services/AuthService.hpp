#pragma once
#include <vector>
#include <map>
#include <string>
#include <optional>
#include "../DataStructures/User.hpp"

class AuthService {
public:
    static AuthService& getInstance() {
        static AuthService instance;
        return instance;
    }

    // Dynamic Array  to store Users
    
    bool registerUser(std::string name, std::string email, std::string cnic, std::string password);
    
    std::optional<User> loginUser(std::string emailOrCnic, std::string password);
    
    std::string createSession(int userId);
    std::optional<int> validateSession(std::string token);
    std::optional<User> getUserById(int id);

private:
    AuthService() {}
    
    
    std::vector<User> m_users; 
    std::map<std::string, int> m_sessions; // Token -> UserID
    int m_nextUserId = 1;
};