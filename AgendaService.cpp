#include "AgendaServi   ce.h"

bool stringValid(std::string str) {
    for (auto i : str) {
        if (!((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i>= 'A' && i <= 'Z')))
            return false;
    }
    return true;
}

bool phoneValid(std::string phone) {
    for (auto i : phone) {
        if (i < '0' || i > '9')
            return false;
    }
    return true;
}  // Check whether the phone format is correct.

bool emailValid(std::string email) {
    int l = email.length();
    int pat, pdot;
    if (email.length() < 5)
        return false;
    for (int i = 0; i < l; i++) {
        if (email[i] == '@') pat = i;
        if (email[i] == '.') pdot = i;
        if (email[i] != '@' && email[i] != '.' &&
            !(email[i] <= '9' && email[i] >= '0') &&
            !(email[i] <= 'z' && email[i] >= 'a') &&
            !(email[i] <= 'Z' && email[i] >= 'A'))
            return false;
    }
    if (pat == 0 || pat == l - 1) return false;
    if (pdot == 0 || pdot == l - 1) return false;
    return true;
}  // Check whether the email format is valid.

bool meetingValid(std::string userName, std::string participator,
    std::string title, std::string startDate, std::string endDate) {
    if (userName == participator)
        return false;
    if (Date::stringToDate(startDate) >= Date::stringToDate(endDate)) {
        return false;
    }
    return true;
}  // Check whether the meeting is valid.

AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    quitAgenda();
    delete storage_;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    std::list<User> userList = storage_->queryUser([&](const User& user) {
        return user.getName() == userName && user.getPassword() == password;
    });
    if (userList.empty()) {
        return false;
    }
    return true;
}

bool AgendaService::userRegister(std::string userName, std::string password,
    std::string email, std::string phone) {
    if (!(stringValid(userName) && stringValid(password)))
        return false;
    if (!storage_->queryUser([&](const User& user) {
        return user.getName() == userName;
        }).empty()) {
        return false;
    }
    if (phoneValid(phone) && emailValid(email)) {  // User information valid.
        User user(userName, password, email, phone);
        storage_->createUser(user);
        return true;
    }
    return false;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    int count = storage_->deleteUser([&](const User& user) {
        return (user.getName() == userName && user.getPassword() == password);
    });
    storage_->deleteMeeting([&](const Meeting& meeting) {
        return meeting.getSponsor() == userName || meeting.getParticipator() == userName;});
    return (count != 0);
}  // a user can only delete itself

bool AgendaService::setPassword(std::string userName, std::string password) {
    if (!stringValid(password))
        return false;
    return storage_->updateUser(
        [&](const User& user) {return user.getName() == userName;},
        [&](User& user) {user.setPassword(password);}
    );
}

bool AgendaService::setEmail(std::string userName, std::string email) {
    if (!emailValid(email))
        return false;
    return storage_->updateUser(
        [&](const User& user) {return user.getName() == userName;},
        [&](User& user) {user.setEmail(email);}
    );
}

bool AgendaService::setPhone(std::string userName, std::string phone) {
    if (!phoneValid(phone))
        return false;
    return storage_->updateUser(
        [&](const User& user) {return user.getName() == userName;},
        [&](User& user) {user.setPhone(phone);}
    );
}

std::list<User> AgendaService::listAllUsers(void) {
    return storage_->queryUser([](const User& user) {return true;});
}

bool AgendaService::createMeeting(std::string userName, std::string title,
    std::string participator,
    std::string startDate, std::string endDate) {
    Date sdate = Date::stringToDate(startDate), edate = Date::stringToDate(endDate);
    if (!meetingValid(userName, participator, title, startDate, endDate))
        return false;
    if (storage_->queryUser([&](const User& user) {return user.getName() == participator;}).empty())
        return false;
    if (storage_->queryMeeting([&](const Meeting& meeting) {return title == meeting.getTitle();}).empty())
        return false;
    if (storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName)
            && (meeting.getStartDate() > sdate && meeting.getStartDate() < edate)
            && (meeting.getEndDate() > sdate && meeting.getEndDate() < edate);
        }).empty()
        && storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == participator || meeting.getParticipator() == participator)
            && (meeting.getStartDate() > sdate && meeting.getStartDate() < edate)
            && (meeting.getEndDate() > sdate && meeting.getEndDate() < edate);
        }).empty()) {
        storage_->createMeeting(Meeting(userName, participator,
            Date::stringToDate(startDate), Date::stringToDate(endDate), title));
        return true;
    }
    return false;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    return storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName)
            && meeting.getTitle() == title;
    });
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
    std::string startDate, std::string endDate) {
    Date sdate = Date::stringToDate(startDate);
    Date edate = Date::stringToDate(endDate);
    std::list<Meeting> meetingList;
    if (!(Date::isValid(sdate) && Date::isValid(edate)))
        return meetingList;
    if (sdate > edate)
        return meetingList;
    return storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName)
            && (((meeting.getStartDate() >= sdate) && (meeting.getStartDate() <= edate))
                || ((meeting.getEndDate() >= sdate) && (meeting.getEndDate() <= edate)));
    });
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName || meeting.getParticipator() == userName);
    });
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName);
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meeting) {
    return (meeting.getParticipator() == userName);
    });
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    int count = storage_->deleteMeeting([&](const Meeting& meeting) {
        return (meeting.getSponsor() == userName
            && meeting.getTitle() == title);
    });
    return (count != 0);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    int count = storage_->deleteMeeting([&](const Meeting& meeting) {
        return meeting.getSponsor() == userName;
    });
    return (count != 0);
}

void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    storage_->sync();
}
