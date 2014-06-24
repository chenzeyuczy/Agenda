#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
  User();
  User(std::string userName, std::string userPassword,
       std::string userEmail, std::string userPhone);
  std::string getName();
  void setName(std::string name);
  std::string getPassword();
  void setPassword(std::string password);
  std::string getEmail();
  void setEmail(std::string email);
  std::string getPhone();
  void setPhone(std::string phone);
  bool isValid(void) const;

 private:
  std::string name_;
  std::string password_;
  std::string email_;
  std::string phone_;
};

#endif
