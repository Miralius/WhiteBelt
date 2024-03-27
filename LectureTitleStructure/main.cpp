#include <string>

using namespace std;

struct Specialization {
    explicit Specialization(string str)
            : value(std::move(str))
    {}

    string value;
};

struct Course {
    explicit Course(string str)
            : value(std::move(str))
    {}
    string value;
};

struct Week {
    explicit Week(string str)
            : value(std::move(str))
    {}
    string value;
};

struct LectureTitle {
    LectureTitle(const Specialization& newSpecialization, const Course& newCourse, const Week& newWeek)
            : specialization(newSpecialization.value)
            , course(newCourse.value)
            , week(newWeek.value)
    {}
    string specialization;
    string course;
    string week;
};

int main() {
    LectureTitle title(
            Specialization("C++"),
            Course("White belt"),
            Week("4th")
    );

//    LectureTitle title("C++", "White belt", "4th");
//
//    LectureTitle title(string("C++"), string("White belt"), string("4th"));
//
//    LectureTitle title = {"C++", "White belt", "4th"};
//
//    LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};
//
//    LectureTitle title(
//            Course("White belt"),
//            Specialization("C++"),
//            Week("4th")
//    );
//
//    LectureTitle title(
//            Specialization("C++"),
//            Week("4th"),
//            Course("White belt")
//    );

    return 0;
}