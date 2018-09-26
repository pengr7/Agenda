#include "AgendaService.h"
using std::list;
using std::string;
AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}
AgendaService::~AgendaService() {
    delete storage_;
    storage_ = NULL;
}
bool AgendaService::userLogIn(string userName, string password) {
    if (storage_->queryUser([userName, password](const User& u) {
                return u.getName() == userName && u.getPassword() == password;
            }).size() != 1)
        return false;
    return true;
}
bool AgendaService::userRegister(string userName, string password,
                                 string email, string phone) {
    if (storage_->queryUser([userName](const User& u) {
                return u.getName() == userName;}).size() != 0)
        return false;
    storage_->createUser(User(userName, password, email, phone));
    return true;
}
bool AgendaService::deleteUser(string userName, string password) {
    if (storage_->deleteUser([userName, password](const User& u) {
                return u.getName() == userName && u.getPassword() == password;
            })) {
        deleteAllMeetings(userName);
        return true;
    }
    return false;
}
list<User> AgendaService::listAllUsers(void) {
    return storage_->queryUser([](const User&) {return true;});
}
bool AgendaService::createMeeting(string userName, string title,
                                  string participator, string startDate,
                                  string endDate) {
    if (storage_->queryUser([userName, participator](const User& u) {
                return u.getName() == userName || u.getName() == participator;
            }).size() != 2)
        return false;
    if (!(Date::isValid(Date::stringToDate(startDate))
          && Date::isValid(Date::stringToDate(endDate))))
        return false;
    if (Date::stringToDate(startDate) >= Date::stringToDate(endDate))
        return false;
    if (storage_->queryMeeting([title](const Meeting& m) {
                return m.getTitle() == title;}).size() != 0)
        return false;
    list<Meeting> l1 = listAllMeetings(userName);
    list<Meeting> l2 = listAllMeetings(participator);
    list<Meeting>::iterator it;
    for (it = l1.begin(); it != l1.end(); it++)
        if (!(it->getEndDate() <= Date::stringToDate(startDate)
              || it->getStartDate() >= Date::stringToDate(endDate)))
            return false;
    for (it = l2.begin(); it != l2.end(); it++)
        if (!(it->getEndDate() <= Date::stringToDate(startDate)
              || it->getStartDate() >= Date::stringToDate(endDate)))
            return false;
    storage_->createMeeting(Meeting(userName, participator,
                                    Date::stringToDate(startDate),
                                    Date::stringToDate(endDate), title));
    return true;
}
list<Meeting> AgendaService::meetingQuery(string userName, string title) {
    return storage_->queryMeeting([userName, title](const Meeting& m) {
            return (m.getSponsor() == userName
                    || m.getParticipator() == userName)
                && m.getTitle() == title;});
}
list<Meeting> AgendaService::meetingQuery(string userName,
                                          string startDate, string endDate) {
    if (!(Date::isValid(Date::stringToDate(startDate))
          && Date::isValid(Date::stringToDate(endDate))))
        return list<Meeting>();
    return storage_->queryMeeting([userName, startDate, endDate]
                                  (const Meeting& m) {
            return (m.getSponsor() == userName
                    || m.getParticipator() == userName)
                && !(m.getEndDate() < Date::stringToDate(startDate)
                     || m.getStartDate() > Date::stringToDate(endDate));});
}
list<Meeting> AgendaService::listAllMeetings(string userName) {
    return storage_->queryMeeting([userName](const Meeting& m) {
            return m.getSponsor() == userName
                || m.getParticipator() == userName;});
}
list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
    return storage_->queryMeeting([userName](const Meeting& m) {
            return m.getSponsor() == userName;});
}
list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
    return storage_->queryMeeting([userName](const Meeting& m) {
            return m.getParticipator() == userName;});
}
bool AgendaService::deleteMeeting(string userName, string title) {
    return storage_->deleteMeeting([userName, title](const Meeting& m) {
            return m.getSponsor() == userName && m.getTitle() == title;});
}
bool AgendaService::deleteAllMeetings(string userName) {
    return storage_->deleteMeeting([userName](const Meeting& m) {
            return m.getSponsor() == userName;});
}
void AgendaService::startAgenda(void) {}
void AgendaService::quitAgenda(void) {}
