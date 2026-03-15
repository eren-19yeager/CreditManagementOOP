#!/bin/bash
# Run this from your project folder to compile everything at once
g++ -std=c++17 -g \
    main.cpp \
    person.cpp \
    student.cpp \
    faculty.cpp \
    admin.cpp \
    course.cpp \
    system.cpp \
    enrollment.cpp \
    ResultManager.cpp \
    timeslot.cpp \
    ScheduleManager.cpp \
    grades.cpp \
    -o university
