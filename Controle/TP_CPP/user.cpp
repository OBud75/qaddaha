#include "user.hpp"
#include "pwd.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>

static std::unordered_map<int, std::shared_ptr<User>> user_db;

User::User(int id, Password password) 
    : id(id), password(std::make_shared<Password>(std::move(password))), is_logged_in(false) {}

int User::login(const char *raw_password) {
    Password temp_password(raw_password);
    if (*password == temp_password) {
        is_logged_in = true;
        return 1;
    }
    return 0;
}

void User::save() {
    user_db[id] = std::make_shared<User>(id, *password);
    std::cout << "User ID " << id << " saved." << std::endl;
}

std::shared_ptr<User> User::get(int id) {
    if (user_db.find(id) != user_db.end()) {
        return user_db[id];
    } else {
        throw std::runtime_error("User not found !");
    }
}