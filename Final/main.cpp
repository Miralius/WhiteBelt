#include <iostream>
#include <string>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

class Date {
public:
    explicit Date(const string &dateString) {
        stringstream dateSS(dateString);
        dateSS >> _year;
        if (!checkAndSkipDelimiter(dateSS)) {
            throw invalid_argument("Wrong date format: " + dateString);
        }
        dateSS >> _month;
        if (!checkAndSkipDelimiter(dateSS)) {
            throw invalid_argument("Wrong date format: " + dateString);
        }
        dateSS >> _day;
        if (!dateSS or !dateSS.eof()) {
            throw invalid_argument("Wrong date format: " + dateString);
        }
        if (_month < 1 or _month > 12) {
            throw invalid_argument("Month value is invalid: " + to_string(_month));
        }
        if (_day < 1 or _day > 31) {
            throw invalid_argument("Day value is invalid: " + to_string(_day));
        }
    }

    Date() = default;

    [[nodiscard]] int GetYear() const {
        return _year;
    }

    [[nodiscard]] int GetMonth() const {
        return _month;
    }

    [[nodiscard]] int GetDay() const {
        return _day;
    }

private:
    static bool checkAndSkipDelimiter(istream &in) {
        char delimiter;
        in >> delimiter;
        if (delimiter != '-') {
            in.setstate(ios_base::failbit);
            return false;
        }
        return true;
    }

    int _year{};
    int _month{};
    int _day{};
};

ostream &operator<<(ostream &out, const Date &obj) {
    out << setw(4) << setfill('0') << obj.GetYear() << '-' << setw(2) << obj.GetMonth() << '-' << setw(2)
        << obj.GetDay();
    return out;
}

bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        _events[date].insert(event);
    }

    bool DeleteEvent(const Date &date, const string &event) {
        const auto eventsIt = _events.find(date);
        if (eventsIt != _events.cend()) {
            return eventsIt->second.erase(event);
        }
        return false;
    }

    int DeleteDate(const Date &date) {
        const auto eventsIt = _events.find(date);
        if (eventsIt != _events.cend()) {
            const auto size = eventsIt->second.size();
            _events.erase(eventsIt);
            return static_cast<int>(size);
        }
        return 0;
    }

    [[nodiscard]] set<string> Find(const Date &date) const {
        const auto eventsIt = _events.find(date);
        if (eventsIt != _events.cend()) {
            return eventsIt->second;
        }
        return {};
    }

    void Print() const {
        for (const auto &[date, events]: _events) {
            for (const auto &event: events) {
                cout << date << ' ' << event << '\n';
            }
        }
    }

private:
    map<Date, set<string>> _events;
};

class Command {
public:
    Command(const string &commandStr, Database &database)
            : _database(database), _date(Date()) {
        if (!commandStr.empty()) {
            stringstream commandSS(commandStr);
            commandSS >> _action;
            if (!_action.empty()) {
                if (_action == "Print") {
                    return;
                }
                try {
                    if (_action == "Add" or _action == "Del" or _action == "Find") {
                        string date;
                        commandSS >> date >> _event;
                        _date = Date(date);
                    } else {
                        throw invalid_argument("Unknown command: " + _action);
                    }
                }
                catch (const exception &ex) {
                    _action = "Exception";
                    _event = ex.what();
                }
            }
        }
    }

    void Run() {
        if (_action == "Add") {
            _database.AddEvent(_date, _event);
        } else if (_action == "Del") {
            if (_event.empty()) {
                cout << "Deleted " << _database.DeleteDate(_date) << " events\n";
            } else {
                if (_database.DeleteEvent(_date, _event)) {
                    cout << "Deleted successfully\n";
                } else {
                    cout << "Event not found\n";
                }
            }
        } else if (_action == "Find") {
            for (const auto &event: _database.Find(_date)) {
                cout << event << '\n';
            }
        } else if (_action == "Print") {
            _database.Print();
        } else if (_action == "Exception") {
            cout << _event << '\n';
        }
    }

private:
    Database &_database;
    string _action;
    Date _date;
    string _event;
};

int main() {
    Database db;

    string commandStr;
    while (getline(cin, commandStr)) {
        Command command(commandStr, db);
        command.Run();
    }

    return 0;
}