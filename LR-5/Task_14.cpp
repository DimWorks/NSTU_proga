#include <iostream>
#include <vector>
#include <string>

// Классы для предметов, студентов и преподавателей
class Subject {
public:
    std::string name;
    // Другие поля и методы для предмета
};

class Student {
public:
    std::string name;
    // Другие поля и методы для студента
};

class Teacher {
public:
    std::string name;
    // Другие поля и методы для преподавателя
};

// Класс для оценок
class Grade {
public:
    Subject subject;
    Student student;
    float value;
    // Другие поля и методы для оценки
};

// Класс для комплекса по выставлению и учету оценок
class GradeComplex {
public:
    std::vector<Subject> subjects;
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    std::vector<Grade> grades;
    // Другие поля и методы для комплекса

//public:
    // Методы для добавления и управления предметами, студентами, преподавателями и оценками
    void addSubject(const std::string& name) {
        Subject subject;
        subject.name = name;
        subjects.push_back(subject);
    }

    void addStudent(const std::string& name) {
        Student student;
        student.name = name;
        students.push_back(student);
    }

    void addTeacher(const std::string& name) {
        Teacher teacher;
        teacher.name = name;
        teachers.push_back(teacher);
    }

    void addGrade(const Subject& subject, const Student& student, float value) {
        Grade grade;
        grade.subject = subject;
        grade.student = student;
        grade.value = value;
        grades.push_back(grade);
    }

    // Другие методы для работы с данными
};

// Интерфейс строителя для комплекса по выставлению и учету оценок
class GradeComplexBuilder {
public:
    virtual void addSubject(const std::string& name) = 0;
    virtual void addStudent(const std::string& name) = 0;
    virtual void addTeacher(const std::string& name) = 0;
    virtual void addGrade(const Subject& subject, const Student& student, float value) = 0;

    virtual GradeComplex getResult() = 0;
};

// Конкретный строитель для комплекса по выставлению и учету оценок
class ConcreteGradeComplexBuilder : public GradeComplexBuilder {
private:
    GradeComplex gradeComplex;

public:
    void addSubject(const std::string& name) override {
        Subject subject;
        subject.name = name;
        gradeComplex.subjects.push_back(subject);
    }

    void addStudent(const std::string& name) override {
        Student student;
        student.name = name;
        gradeComplex.students.push_back(student);
    }

    void addTeacher(const std::string& name) override {
        Teacher teacher;
        teacher.name = name;
        gradeComplex.teachers.push_back(teacher);
    }

    void addGrade(const Subject& subject, const Student& student, float value) override {
        Grade grade;
        grade.subject = subject;
        grade.student = student;
        grade.value = value;
        gradeComplex.grades.push_back(grade);
    }

    GradeComplex getResult() override {
        return gradeComplex;
    }
};

int main() {
    GradeComplexBuilder* builder = new ConcreteGradeComplexBuilder();

    builder->addSubject("Math");
    builder->addSubject("Physics");

    builder->addStudent("John");
    builder->addStudent("Alice");

    builder->addTeacher("Mr. Smith");

    builder->addGrade(Subject{ "Math" }, Student{ "John" }, 90.0f);
    builder->addGrade(Subject{ "Physics" }, Student{ "Alice" }, 85.5f);

    GradeComplex gradeComplex = builder->getResult();

    // Вывод студентов и их оценок
    for (const auto& student : gradeComplex.students) {
        std::cout << "Student: " << student.name << std::endl;
        for (const auto& grade : gradeComplex.grades) {
            if (grade.student.name == student.name) {
                std::cout << "Subject: " << grade.subject.name << ", Grade: " << grade.value << std::endl;
            }
        }
        std::cout << std::endl;
    }

    delete builder;

    return 0;
}