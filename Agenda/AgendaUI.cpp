#include "AgendaUI.h"
using std::string;
using std::list;
using std::cin;
using std::cout;
using std::endl;
AgendaUI::AgendaUI() {}
void AgendaUI::OperationLoop(void) {
    startAgenda();
}
void AgendaUI::startAgenda(void) {
    cout << "------------------------Agenda--------------------------"
         << endl;
    cout << "Action :" << endl;
    cout << "l   - log in Agenda by user name and password" << endl;
    cout << "r   - register an Agenda accont" << endl;
    cout << "q   - quit Agenda" << endl;
    cout << "--------------------------------------------------------"
         << endl << endl;
    cout << "Agenda : ~$ ";
    executeOperation(getOperation());
}
string AgendaUI::getOperation() {
    string s;
    cin >> s;
    return s;
}
bool AgendaUI::executeOperation(string op) {
    if (op == "l") {
        userLogIn();
        return true;
    } else if (op == "r") {
        userRegister();
        return true;
    } else if (op == "q") {
        quitAgenda();
        return true;
    } else if (op == "o") {
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
    } else {
        executeOperation(getOperation());
        return true;
    }
}
void AgendaUI::userLogIn(void) {
    string name, password;
    cout << endl << "[log in] [user name] [password]" << endl;
    cout << "[log in] ";
    cin >> name >> password;
    if (agendaService_.userLogIn(name, password)) {
        cout << "[log in] succeed!" << endl << endl;
        userName_ = name;
        userPassword_ = password;
        cout << "------------------------Agenda--------------------------"
             << endl;
        cout << "Action :" << endl;
        cout << "o   - log out Agenda" << endl;
        cout << "dc  - delete Agenda account" << endl;
        cout << "lu  - liat all Agenda user" << endl;
        cout << "cm  - create a meeting" << endl;
        cout << "la  - list all meetings" << endl;
        cout << "las - list all sponsor meetings" << endl;
        cout << "lap - list all participator meetings" << endl;
        cout << "qm  - query meeting by title" << endl;
        cout << "qt  - query meeting by interval" << endl;
        cout << "dm  - delete meeting by title" << endl;
        cout << "da  - delete all meetings" << endl;
        cout << "--------------------------------------------------------"
                 << endl << endl;
        cout << "Agenda@" << userName_ << " : # ";
        executeOperation(getOperation());
    } else {
        cout << "[error] log in fail!" << endl;
        getOperation();
        system("clear");
        startAgenda();
    }
}
void AgendaUI::userRegister(void) {
    string name, password, email, phone;
    cout << endl << "[register] [user name] [password] [email] [phone]" << endl;
    cout << "[register] ";
    cin >> name >> password >> email >> phone;
    if (agendaService_.userRegister(name, password, email, phone)) {
        cout << "[register] succeed!" << endl;
        getOperation();
        system("clear");
        startAgenda();
    } else {
        cout << "[error] register fail!" << endl;
        getOperation();
        system("clear");
        startAgenda();
    }
}
void AgendaUI::quitAgenda(void) {
    exit(0);
}
void AgendaUI::userLogOut(void) {
    userName_ = userPassword_ = "";
    system("clear");
    startAgenda();
}
void AgendaUI::deleteUser(void) {
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        cout << endl << "[delete agenda annount] succeed!" << endl;
    } else {
         cout << endl << "[error] delete agenda annount fail!" << endl;
    }
    getOperation();
    system("clear");
    startAgenda();
}
void AgendaUI::listAllUsers(void) {
    cout << endl << "[list all users]" << endl << endl
         << "name\temail\tphone" << endl;
    list<User> l = agendaService_.listAllUsers();
    for (list<User>::iterator it = l.begin(); it != l.end(); it++)
        cout << it->getName() << "\t" << it->getEmail() << "\t"
             << it->getPhone() << endl;
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::createMeeting(void) {
    string title, participator, startTime, endTime;
    cout << endl << "[create meeting] [title] [participator] [start time"
         << "(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    cin >> title >> participator >> startTime >> endTime;
    if (agendaService_.createMeeting(userName_, title, participator,
                                     startTime, endTime)) {
        cout << "[create meeting] succeed!" << endl;
    } else {
        cout << "[error] create meeting fail!" << endl;
    }
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::listAllMeetings(void) {
    printMeetings(agendaService_.listAllMeetings(userName_));
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::listAllSponsorMeetings(void) {
    cout << endl << "[list all sponsor meetings]" << endl << endl;
    printMeetings(agendaService_.listAllSponsorMeetings(userName_));
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::listAllParticipateMeetings(void) {
    cout << endl << "[list all participate meetings]" << endl << endl;
    printMeetings(agendaService_.listAllParticipateMeetings(userName_));
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::queryMeetingByTitle(void) {
    string title;
    cout << endl << "[query meeting] [title]" << endl;
    cout << "[query meeting] ";
    cin >> title;
    printMeetings(agendaService_.meetingQuery(userName_, title));
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    string startTime, endTime;
    cout << endl << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] "
         << "[end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meeting] ";
    cin >> startTime >> endTime;
    printMeetings(agendaService_.meetingQuery(userName_, startTime, endTime));
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::deleteMeetingByTitle(void) {
    string title;
    cout << endl << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    cin >> title;
    if (agendaService_.deleteMeeting(userName_, title)) {
        cout << "[delete meeting by title] succeed!" << endl;
    } else {
        cout << "[error] delete meeting fail!" << endl;
    }
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::deleteAllMeetings(void) {
    if (agendaService_.deleteAllMeetings(userName_)) {
        cout << "[delete all meetings] succeed!" << endl;
    } else {
        cout << "[error] delete all meetings fail!" << endl;
    }
    cout << endl << "Agenda@" << userName_ << " : # ";
    executeOperation(getOperation());
}
void AgendaUI::printMeetings(list<Meeting> meetings) {
    cout << "title\tsponsor\tparticipator\tstart time\tend time" << endl;
    for (list<Meeting>::iterator it = meetings.begin();
         it != meetings.end(); it++)
        cout << it->getTitle() << "\t" << it->getSponsor() << "\t"
             << it->getParticipator()  << "\t"
             << Date::dateToString(it->getStartDate()) << "\t"
             << Date::dateToString(it->getEndDate()) << endl;
}
