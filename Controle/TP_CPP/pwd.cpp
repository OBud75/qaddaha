#include "pwd.hpp"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

Password::Password(const std::string &password, bool is_encrypted) {
    if (is_encrypted) {
        _encrypted_value = password;
    } else {
        _raw_value = password;
        encrypt(password);
    }
}

void Password::encrypt(const std::string &password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.size(), hash);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    _encrypted_value = ss.str();
}

std::string Password::str() const {
    return _raw_value;
}

bool Password::operator==(const std::string &str) const {
    Password temp_password(str);
    return _encrypted_value == temp_password._encrypted_value;
}

bool Password::operator==(const Password &other) const {
    return _encrypted_value == other._encrypted_value;
}

std::ostream &operator<<(std::ostream &os, const Password &p) {
    os << p._encrypted_value;
    return os;
}