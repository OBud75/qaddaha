#include "pwd.hpp"
#include "user.hpp"
#include <iostream>
#include <cassert>

int main() {
    Password password("gabichou");
    User user(1, password);
    assert(password == "gabichou");
    
    std::cout << "OK" << std::endl;

    user.save();

    std::shared_ptr<User> retrieved_user = User::get(1);
    if (retrieved_user->login("gabichou")) {
        std::cout << "Login success" << std::endl;
    } else {
        std::cout << "Login failed" << std::endl;
    }

    return 0;
}