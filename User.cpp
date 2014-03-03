// Copyright [2013] chenzy
#include "User.h"

User::User() {}
User::User(std::string n, std::string pw, std::string e, std::string ph)
: name_(n), password_(pw), email_(e), phone_(ph) {}
std::string User::getName() {return name_;}
void User::setName(std::string n) {name_ = n;}
std::string User::getPassword() {return password_;}
void User::setPassword(std::string p) {password_ = p;}
std::string User::getEmail() {return email_;}
void User::setEmail(std::string e) {email_ = e;}
std::string User::getPhone() {return phone_;}
void User::setPhone(std::string p) {phone_ = p;}

bool User::phoneValid(std::string phone) {
  for (unsigned int i = 0; i < phone.length(); i++) {
    if (phone[i] < '0' || phone[i] > '9')
      return false;
  }
  return true;
}
bool User::emailValid(std::string email) {
  bool at, dot, text, flag;
  at = dot = text = flag = false;
  for (unsigned int i = 0; i < email.length(); i++) {
    if (email[i] == '@') {
      if (dot || at) {
        return false;
      } else {
        at = true;
        text = false;
      }
    } else if (email[i] == '.') {
      if (!text || !at || dot) {
        return false;
      } else {
        dot = true;
        text = false;
        flag = true;
      }
    } else {
      text = true;
      dot = false;
    }
  }
  return at && !dot && text && flag;
}
