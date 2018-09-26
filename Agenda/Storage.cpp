#include "Storage.h"
#include <fstream>
using std::list;
using std::function;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
Storage* Storage::instance_ = NULL;
Storage::Storage() {
    readFromFile("./");
}
Storage* Storage::getInstance(void) {
    if (instance_ == NULL)
        instance_ = new Storage();
    return instance_;
}
Storage::~Storage() {
    instance_ = NULL;
}
bool Storage::readFromFile(const char* fpath) {
    string s(fpath), line, info[5];
    ifstream fu(s+"User.csv");
    if (!fu)
        return false;
    getline(fu, line);
    while (getline(fu, line)) {
        unsigned i, pre = 1, cnt = 0, count = 0;
        for (i = 0; i < line.length(); i++) {
            if (line[i] == '"')
                cnt++;
            if (count == 3) {
                info[count] = line.substr(pre, line.length()-pre-1);
                break;
            }
            if (line[i] == ',' && cnt%2 == 0) {
                info[count] = line.substr(pre, i-pre-1);
                count++;
                pre = i+2;
            }
        }
        userList_.push_back(User(info[0], info[1], info[2], info[3]));
    }
    ifstream fm(s+"Meeting.csv");
    if (!fm)
        return false;
    getline(fm, line);
    while (getline(fm, line)) {
        unsigned i, pre = 1, cnt = 0, count = 0;
        for (i = 0; i < line.length(); i++) {
            if (line[i] == '"')
                cnt++;
            if (count == 4) {
                info[count] = line.substr(pre, line.length()-pre-1);
                break;
            }
            if (line[i] == ',' && cnt%2 == 0) {
                info[count] = line.substr(pre, i-pre-1);
                count++;
                pre = i+2;
            }
        }
        meetingList_.push_back(Meeting(info[0], info[1],
            Date::stringToDate(info[2]), Date::stringToDate(info[3]), info[4]));
    }
    return true;
}
bool Storage::writeToFile(const char* fpath) {
    string s(fpath);
    ofstream fu(s+"User.csv");
    if (!fu)
        return false;
    fu << "\"name\",\"password\",\"email\",\"phone\"" << endl;
    for (list<User>::iterator it = userList_.begin();
         it != userList_.end(); it++)
        fu << "\"" << it->getName() << "\",\"" << it->getPassword() << "\",\""
           << it->getEmail() << "\",\"" << it->getPhone() << "\"" << endl;
    ofstream fm(s+"Meeting.csv");
    if (!fm)
        return false;
    fm << "\"sponsor\",\"participator\",\"sdate\",\"edate\",\"title\""
       << endl;
    for (list<Meeting>::iterator it = meetingList_.begin();
         it != meetingList_.end(); it++)
        fm << "\"" << it->getSponsor() << "\",\"" << it->getParticipator()
           << "\",\"" << Date::dateToString(it->getStartDate()) << "\",\""
           << Date::dateToString(it->getEndDate()) << "\",\""
           << it->getTitle() << "\"" << endl;
    return true;
}
void Storage::createUser(const User& u) {
    userList_.push_back(u);
    sync();
}
list<User> Storage::queryUser(function<bool(const User&)> filter) {
    list<User> l;
    for (list<User>::iterator it = userList_.begin();
         it != userList_.end(); it++)
        if (filter(*it))
            l.push_back(*it);
    return l;
}
int Storage::updateUser(function<bool(const User&)> filter,
                        function<void(User&)> switcher) {
    int cnt = 0;
    for (list<User>::iterator it = userList_.begin();
         it != userList_.end(); it++)
        if (filter(*it)) {
            switcher(*it);
            cnt++;
        }
    sync();
    return cnt;
}
int Storage::deleteUser(function<bool(const User&)> filter) {
    int cnt = 0;
    for (list<User>::iterator it = userList_.begin();
         it != userList_.end(); it++)
        if (filter(*it)) {
            it = userList_.erase(it);
            cnt++;
            it--;
        }
    sync();
    return cnt;
}
void Storage::createMeeting(const Meeting& m) {
    meetingList_.push_back(m);
    sync();
}
list<Meeting> Storage::queryMeeting(function<bool(const Meeting&)> filter) {
    list<Meeting> l;
    for (list<Meeting>::iterator it = meetingList_.begin();
         it != meetingList_.end(); it++)
        if (filter(*it))
            l.push_back(*it);
    return l;
}
int Storage::updateMeeting(function<bool(const Meeting&)> filter,
                           function<void(Meeting&)> switcher) {
    int cnt = 0;
    for (list<Meeting>::iterator it = meetingList_.begin();
        it != meetingList_.end(); it++)
        if (filter(*it)) {
            switcher(*it);
            cnt++;
        }
    sync();
    return cnt;
}
int Storage::deleteMeeting(function<bool(const Meeting&)> filter) {
    int cnt = 0;
    for (list<Meeting>::iterator it = meetingList_.begin();
        it != meetingList_.end(); it++)
        if (filter(*it)) {
            it = meetingList_.erase(it);
            cnt++;
            it--;
        }
    sync();
    return cnt;
}
bool Storage::sync(void) {
    if (writeToFile("./"))
        return true;
    return false;
}
