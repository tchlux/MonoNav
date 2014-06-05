"""
File: Student.py
Author:

Define a student class that stores name, scores on assignments,
quizzes and tests.
"""

class Student:
    ASSIGN = 1
    QUIZ = 2
    TEST = 3

    #constructor
    #Should declare and instantiate storage for the students name,
    #and should also declare the storage areas for assignments, quizzes,
    #and tests.
    def __init__(self, student_name, ASSIGN=1, QUIZ=2, TEST=3):
        self.student = student_name
        self.assign = ASSIGN
        self.quiz = QUIZ
        self.test = TEST
        self.assign_weight = .35
        self.quiz_weight = .13
        self.test_weight = .52
        self.assign_list = []
        self.quiz_list = []
        self.test_list = []

    #addGrade
    #Pre:  Grade storage area has been declared
    #Post: Adds parameter grade into the appropriate gradebook
    def addGrade(self, grade, grade_type):
        if grade_type == self.assign:
            self.assign_list.append(grade)
        elif grade_type == self.quiz:
            self.quiz_list.append(grade)
        elif grade_type == self.test:
            self.test_list.append(grade)
        else:
            a=b

    #getName
    #Pre:  name instance variable is defined
    #Post: returns the value in the name instance variable
    def getName(self):
        return self.student

    def returnMean(self, list_name):
        average = 0
        for grade in list_name:
            average += grade
        average /= len(list_name)
        return average
        
    #Pre:  Grade storage area has been declared and instantiated
    #Post: returns the average of all grades, using the weights defined
    def getAverage(self):
        self.assign_average = self.returnMean(self.assign_list)
        self.quiz_average =  self.returnMean(self.quiz_list)
        self.test_average =  self.returnMean(self.test_list)
        self.assign_average *= self.assign_weight
        self.quiz_average *= self.quiz_weight
        self.test_average *= self.test_weight
        self.average = (self.assign_average + self.quiz_average + self.test_average)
#        print(self.average)
        return self.average

    #printTestGrades
    #Pre:  Test grade storage as been declared and instantiated.
    #Post: Prints a list of all test grades.
    def printTestGrades(self):
        print("Test Grades:")
        for grade in self.test_list:
            print(grade)

    #printQuizGrades
    #Pre:  Quiz grade storage as been declared and instantiated.
    #Post: Prints a list of all quiz grades.
    def printQuizGrades(self):
        print("Quiz Grades:")
        for grade in self.quiz_list:
            print(grade)

    #printAssignGrades
    #Pre:  Assignment grade storage as been declared and instantiated.
    #Post: Prints a list of all Assignment grades.
    def printAssignGrades(self):
        print("Assignment Grades:")
        for grade in self.assign_list:
            print(grade)

