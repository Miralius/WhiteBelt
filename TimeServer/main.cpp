#include <iostream>
#include <exception>
#include <string>

using namespace std;

string AskTimeServer() {
    unsigned char mode = 2;
    if (mode == 0) {
        return "16:01:59";
    } else if (mode == 1) {
        throw system_error();
    } else {
        throw domain_error("omg");
    }
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            last_fetched_time = AskTimeServer();
        }
        catch (system_error &ex) {
            return last_fetched_time;
        }
        return last_fetched_time;
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception &e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
