/* FileManage.h --- File Manage of Agenda
 */

#ifndef INCLUDED_FILEMANAGE_H
#define INCLUDED_FILEMANAGE_H 1

#include "User.h"
#include "Meeting.h"
#include <string>
#include <list>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

class FileManage {
 public:
  ~FileManage();
  static FileManage *getInstance(void);
  std::list<User> readUsersFromFile(void);
  void writeUsersToFile(std::list<User> users);
  std::list<Meeting> readMeetingsFromFile(void);
  void writeMeetingsToFile(std::list<Meeting> meetings);

 private:
  FileManage();
  std::string userFileName_;
  std::string meetingFileName_;
  static FileManage *instance_;
  static bool instanceFlag_;
  DISALLOW_COPY_AND_ASSIGN(FileManage);
};

#endif /* INCLUDED_FILEMANAGE_H */
