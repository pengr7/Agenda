#include "User.h"
using std::string;
User::User() {}
User::User(string n, string pw, string e, string ph) {
  name_ = n;
  password_ = pw;
  email_ = e;
  phone_ = ph;
}
string User::getName() const {
  return name_;
}
void User::setName(string s) {
  name_ = s;
}
string User::getPassword() const {
  return password_;
}
void User::setPassword(string s) {
  password_ = s;
}
string User::getEmail() const {
  return email_;
}
void User::setEmail(string s) {
  email_ = s;
}
string User::getPhone() const {
  return phone_;
}
void User::setPhone(string s) {
  phone_ = s;
}

