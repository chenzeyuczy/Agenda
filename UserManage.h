#ifndef USERMANAGE_H
#define USERMANAGE_H

#include "User.h"
#include <list>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

class UserManage {
 public:
  ~UserManage();
  static UserManage *getInstance(void);
  void initUsersList(std::list<User> users);
  User* findUserByName(std::string userName);
  bool createUser(std::string userName, std::string userPassword,
                  std::string userEmail,
                  std::string userPhone);
  bool deleteUser(User user);
  bool updateUserPassword(User user, std::string newPassword);
  bool updateUserEmail(User user, std::string newEmail);
  bool updateUserPhone(User user, std::string newPhone);
  std::list<User> listAllUsers(void);

 private:
  UserManage();
  std::list<User> users_;
  static bool instanceFlag_;
  static UserManage *instance_;
  DISALLOW_COPY_AND_ASSIGN(UserManage);
};

#endif
