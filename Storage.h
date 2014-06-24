#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include "User.h"
#include "Meeting.h"
#include<list>
#include<string>

class Storage {
  private:
    static Storage* instance_;
    DISALLOW_COPY_AND_ASSIGN(Storage);
    Storage();
    // storage structure, or you have better structures e.g. balanced tree
    std::list<User> userList_;
    std::list<Meeting> meetingList_;
    // File IO
    bool ReadFromFile(char *fpath);
    bool WriteToFile(char *fpath);
    // log [choice]
    // TODO:...
  public:
    // singleton
    Storage& GetInstance(void);
    ~Storage();
    // CRUD for User & Meeting using C++11 Lambda Expressions
    bool CreateUser(const User&);
    std::list<User> QueryUser(function<bool(const User&)> filter);
    bool UpdateUser(function<bool(const User&)> filter, function<void(User&)> switcher);
    bool DeleteUser(function<bool(const User&)> filter);
    bool CreateMeeting(const Meeting&);
    std::list<Meeting> QueryMeeting(function<bool(const Meeting&)> filter);
    bool UpdateMeeting(function<bool(const Meeting&)> filter, function<void(Meeting&)> switcher);
    bool DeleteMeeting(function<bool(const Meeting&)> filter);
    // File IO
    bool Sync(void);
};

#endif
