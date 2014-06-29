// Copyright [2013] chenzy

#include "AgendaUI.h"
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

AgendaUI::AgendaUI() {
  userName_.clear();
  userPassword_.clear();
  agendaService_.startAgenda();
  startAgenda();
}

void AgendaUI::startAgenda() {
  if (userName_.empty()) {
    cout << "-------------------- Agenda -----------------------\n"
         << "Action :\n"
         << "l   - log in Agendaby user name and password\n"
         << "r   - register an Agenda account\n"
         << "q   - quit Agenda\n"
         << "---------------------------------------------------\n\n";
  } else {
    cout << "-------------------- Agenda -----------------------\n"
         << "Action :\n"
         << "o   - log out Agenda\n"
         << "dc  - delete Agenda account\n"
         << "lu  - list all Agenda user\n"
         << "cm  - create a meeting\n"
         << "la  - list all meetings\n"
         << "las - list all sponsor meetings\n"
         << "lap - list all participate meetings\n"
         << "qm  - query meeting by title\n"
         << "qt  - query meeting by time interval\n"
         << "dm  - delete meeting by title\n"
         << "da  - delete all meetings\n"
         << "su  - set user password\n"
         << "se  - set email\n"
         << "sp  - set phone\n"
         << "smp - set meeting participator\n"
         << "sms - set meeting start date\n"
         << "sme - set meeting end date\n"
         << "---------------------------------------------------\n\n";
  }
}  // 开始菜单

void AgendaUI::getOperation() {
  std::string op;
  if (userName_.empty()) {
    while (1) {
      bool isValid = true;
      cout << "Agenda : ~$ ";
      op = getCmd();
	  if (op == "l") {
		  userLogIn();
	  } else if (op == "r") {
		  userRegister();
	  } else if (op == "q"){
		  quitAgenda();
	  } else {
        isValid = false;
      }
      if (isValid) break;
    }
  } else {
    while (1) {
      cout << "Agenda@" << userName_ << " : # ";
      op = getCmd();
      if (executeOperation(op)) break;
    }
  }
}  // 获取操作指令

std::string AgendaUI::getCmd() {
    std::string temp;
    cin >> temp;
    return temp;
}  // Get the input.

bool AgendaUI::executeOperation(std::string op) {
  if (op == "o") {
    userLogOut();
    return true;
  } else if (op == "dc") {
    deleteUser();
    return true;
  } else if (op == "lu") {
    listAllUsers();
    return true;
  } else if (op == "cm") {
    createMeeting();
    return true;
  } else if (op == "la") {
    listAllMeetings();
    return true;
  } else if (op == "las") {
    listAllSponsorMeetings();
    return true;
  } else if (op == "lap") {
    listAllParticipateMeetings();
    return true;
  } else if (op == "qm") {
    queryMeetingByTitle();
    return true;
  } else if (op == "qt") {
    queryMeetingByTimeInterval();
    return true;
  } else if (op == "dm") {
    deleteMeetingByTitle();
    return true;
  } else if (op == "da") {
    deleteAllMeetings();
    return true;
  } else if (op == "su") {
    setPassword();
    return true;
  } else if (op == "se") {
    setEmail();
    return true;
  } else if (op == "sp") {
    setPhone();
    return true;
  } else if (op == "smp") {
    setParticipator();
    return true;
  } else if (op == "sms") {
    setStartDate();
    return true;
  } else if (op == "sme") {
    setEndDate();
    return true;
  }
  return false;
}

void AgendaUI::userLogIn() {
  cout << "\n[log in] [user name] [password]\n"
       << "[log in] ";
  std::string name, password;
  cin >> name >> password;
  if (agendaService_.userLogIn(name, password)) {
	userName_ = name;
	userPassword_ = password;
    cout << "[log in] succeed!\n\n";
  } else {
    cout << "[error] log in fail!\n\n";
  }
  startAgenda();
  getOperation();
}

void AgendaUI::userRegister() {
  cout << "\n[register] [user name] [password] [email] [phone]\n"
       << "[register] ";
  std::string name, password, email, phone;
  cin >> name >> password >> email >> phone;
  if (agendaService_.userRegister(name, password, email, phone)) {
    cout << "[register] succeed!\n\n";
  } else {
    cout << "[error] register fail!\n\n";
  }
  startAgenda();
  getOperation();
}

void AgendaUI::quitAgenda() {
  agendaService_.quitAgenda();
  cout << "[quit agenda] succeed!\n";
}

void AgendaUI::userLogOut() {
  userName_.clear();
  userPassword_.clear();
  agendaService_.quitAgenda();
  startAgenda();
  getOperation();
}

void AgendaUI::deleteUser() {
	std::string password;
	cout << "\nPlease input the password again: ";
	cin >> password;
  cout <<"\n[delete agenda account] ";
  if (agendaService_.deleteUser(userName_, password)) {
	userName_.clear();
	userPassword_.clear();
    cout << "succeed!\n\n";
  } else {
    cout << "delete agenda account fail!\n\n";
  }
  startAgenda();
  getOperation();
}  // 删除账户

void AgendaUI::listAllUsers() {
  cout << "\n[list all users]\n\n"
       << "name    email          phone\n";
  std::list<User> tem = agendaService_.listAllUsers();
  std::list<User>::iterator p;
  for (p = tem.begin(); p != tem.end(); p++) {
    cout << std::setiosflags(std::ios::left) << std::setw(8) << p->getName()
         << std::setw(15) << p->getEmail() << p->getPhone() << endl;
  }
  cout << endl;
  startAgenda();
  getOperation();
}

void AgendaUI::createMeeting() {
  cout << "[create meeting] [title] [participator] "
       << "[start time(yyyy-mm-dd/hh::mm)] "
       << "[end time](yyyy-mm-dd/hh:mm)\n"
       << "[create meeting] ";
  std::string title, participator, stime, etime;
  cin >> title >> participator >> stime >> etime;
  if (agendaService_.createMeeting(userName_, title,
    participator, stime, etime)) {
    cout << "[create meeting] succeed!\n\n";
  } else {
    cout << "[error] create meeting fail!\n\n";
  }
  startAgenda();
  getOperation();
}  // 添加会议

void AgendaUI::listAllMeetings() {
  cout << "\n[list all meetings]\n";
  std::list<Meeting> tem = agendaService_.listAllMeetings
    (userName_);
  printMeetings(tem);
  startAgenda();
  getOperation();
}

void AgendaUI::listAllSponsorMeetings() {
  cout << "\n[list all sponsor meetings]\n";
  std::list<Meeting> tem = agendaService_.listAllSponsorMeetings
    (userName_);
  printMeetings(tem);
  startAgenda();
  getOperation();
}

void AgendaUI::listAllParticipateMeetings() {
  cout << "\n[list all participate meetings]\n";
  std::list<Meeting> tem =
    agendaService_.listAllParticipateMeetings(userName_);
  printMeetings(tem);
  startAgenda();
  getOperation();
}

void AgendaUI::queryMeetingByTitle() {
  cout << "\n[query meeting] [title]:\n"
       << "[query meeting] ";
  std::string meeting;
  cin >> meeting;
  std::list<Meeting> tem = agendaService_.meetingQuery(userName_, meeting);
  if (!tem.empty()) {
    cout << "\nsponsor        participator   "
         << "start time           end time\n";
	for (auto i: tem)
    cout << std::setiosflags(std::ios::left)
         << std::setw(15) << i.getSponsor()
         << std::setw(15) << i.getParticipator()
         << std::setw(20) << Date::dateToString(i.getStartDate())
         << Date::dateToString(i.getEndDate()) << endl << endl;
  } else {
    cout << "\n[error] query meeting fail!\n\n";
  }  // 会议名不存在
  startAgenda();
  getOperation();
}

void AgendaUI::queryMeetingByTimeInterval() {
  cout << "\n[query meetings] [start time(yyyy- mm-dd/hh:mm)] "
       << "[end time(yyyy-mm-dd/hh:mm)]\n"
       << "[query meetings] ";
  std::string stime, etime;
  cin >> stime >> etime;
  Date start = Date::stringToDate(stime), end = Date::stringToDate(etime);
  if (start > end || Date::isValid(start) || Date::isValid(end)) {
  // start晚于end或者不合法
    cout << "\n[error] query meeting fail!\n\n";
  } else {
    std::list<Meeting> tem = agendaService_.meetingQuery
      (userName_, stime, etime);
      // What if not existed?
    printMeetings(tem);
  }
  startAgenda();
  getOperation();
}

void AgendaUI::deleteMeetingByTitle() {
  cout << "\n[delete meeting] [title]\n" << "[delete meeting] ";
  std::string title;
  cin >> title;
  if (agendaService_.deleteMeeting(userName_, title)) {
    cout << "\n[delete meeting by title] succeed!\n\n";
  } else {
    cout << "\n[error] delete meeting fail!\n\n";
  }
  startAgenda();
  getOperation();
}

void AgendaUI::deleteAllMeetings() {
  if (agendaService_.deleteAllMeetings(userName_)) {
    cout << "\n[delete all meetings] succeed!\n\n";
  } else {
    cout << "\n[error] delete meetings fail!\n\n";
  }
  startAgenda();
  getOperation();
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::list<Meeting>::iterator p;
  cout << "\ntitle          sponsor        participator   "
       << "start time           end time\n";
  for (p = meetings.begin(); p != meetings.end(); p++) {
    cout << std::setiosflags(std::ios::left) << std::setw(15) << p->getTitle()
         << std::setw(15) << p->getSponsor()
         << std::setw(15) << p->getParticipator()
         << std::setw(20) << Date::dateToString(p->getStartDate())
         << Date::dateToString(p->getEndDate()) << endl;
  }
  cout << endl;
}  // 打印会议列表

void AgendaUI::setPassword() {
  cout << "\n[set password] [new password]\n"
       << "[set password] ";
  std::string password;
  cin >> password;
  /*
  if (agendaService_.setPassword(userName_, password))
    cout << "[set password] succeed!\n\n";
  else
    cout << "[error] set password fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改密码

void AgendaUI::setEmail() {
  cout << "\n[set email] [new email]\n"
       << "[set email] ";
  std::string email;
  cin >> email;
  /*
  if (agendaService_.setEmail(userName_, email))
    cout << "[set email] succeed!\n\n";
  else
    cout << "[error] set email fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改邮箱

void AgendaUI::setPhone() {
  cout << "\n[set phone] [new phone]\n"
       << "[set phone] ";
  std::string phone;
  cin >> phone;
  /*
  if (agendaService_.setPhone(userName_, phone))
    cout << "[set phone] succeed!\n\n";
  else
    cout << "[error] set phone fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改电话

void AgendaUI::setParticipator() {
  cout << "\n[set participator] [title] [new participator]\n"
       << "[set participator] ";
  std::string title, participator;
  cin >> title >> participator;
  /*
  if (agendaService_.meetingQuery(title) == NULL)
    cout << "[error] meeting doesn't exist!\n";
  if (agendaService_.setParticipator(title, participator))
    cout << "[set participator] succeed!\n\n";
  else
    cout << "[error] set participator fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改参与者

void AgendaUI::setStartDate() {
  cout << "\n[set start date] [title] [new start date]\n"
       << "[set start date] ";
  std::string title, stime;
  cin >> title >> stime;
  /*
  if (agendaService_.meetingQuery(title) == NULL)
    cout << "[error] meeting doesn't exist!\n";
  if (agendaService_.setStartDate(title, stime))
    cout << "[set start date] succeed!\n\n";
  else
    cout << "[error] set start date fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改起始时间

void AgendaUI::setEndDate() {
  cout << "\n[set end date] [title] [new end date]\n"
       << "[set end date] ";
  std::string title, etime;
  cin >> title >> etime;
  /*
  if (agendaService_.meetingQuery(title) == NULL)
    cout << "[error] meeting doesn't exist!\n";
  if (agendaService_.setStartDate(title, etime))
    cout << "[set end date] succeed!\n\n";
  else
    cout << "[error] set end date fail!\n\n";
  */
  startAgenda();
  getOperation();
}  // 修改终止时间
