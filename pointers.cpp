// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <math.h>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
char* promptString(std::string message);
void printStudentInfo(Student student);

int main(int argc, char **argv)
{
    Student student;
    double average;

    std::string message;

    //printf("%d", promptInt("Please enter an int \t", -100, 100));

    student.id = promptInt("Please enter the student's id number: ", 1, 999999999);
    student.f_name = promptString("Please enter the student's first name: ");
    student.l_name = promptString("Please enter the student's last name: ");
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);

    student.grades = new double [student.n_assignments];

    for (int i=0; i<student.n_assignments; i++){
        message = "Please enter grade for assignment " + std::to_string(i+1) + ": ";
        student.grades[i] = promptDouble(message, 0, 100);
    }


    printStudentInfo(student);
    // Sequence of user input -> store in fields of `student`

    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    std::string result;
    
    bool finished = false;
    bool negative = false;
    int final_int = 0;

    while (!finished){
        final_int = 0;
        negative = false;
        std::cout << message;
        std::cin >> result;
        for (int i=0; i<result.length(); i++){
            char c = result[i];

            if((c == 45) && (i==0)){
                negative = true;
                continue;
            }
            
            if((c != 46) && ((c < 48) || (c > 57 ))){
                std::cout << "Sorry, I cannot understand your answer \n";
                break;
            }

            final_int += ( pow(10, (result.length() - 1) - i) * (c - 48));

            if(i == result.length()-1){
                finished = true;
            }
        }

        if(negative){
            final_int *= -1;
        }

        if ((final_int < min) || (final_int > max)){
            std::cout << "Please enter a number between [" << min <<", " << max << "] \n";
            finished = false;
        }
    }

    //std::cout << "\n" << final_int << "\n";
    return final_int;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    return 0.0;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
}

char* promptString(std::string message){
    // Code to prompt user for an int
    std::string result;
    
    bool finished = false;

    char* final_string;    

    while (!finished){
        std::cout << message;
        std::cin >> result;

        final_string = new char [result.length()];
        for (int i=0; i<result.length(); i++){
            char c = result[i];
            
            if(((c < 65) || (c > 90)) && ((c < 97) || (c > 122))){
                std::cout << "Sorry, I cannot understand your answer \n";
                break;
            }

            if(i == result.length()-1){
                finished = true;
            }
            final_string[i] = c;
        }
    }

    //std::cout << "\n" << final_int << "\n";
    return final_string;
}

void printStudentInfo(Student student){
    std::cout << "ID: " << student.id << "\n";
    std::cout << "First Name: " << student.f_name << "\n";
    std::cout << "Last Name: " << student.l_name << "\n";
    std::cout << "Number of Assignments: " << student.n_assignments << "\n";
    std::cout << "Grades: ";
    for (int i=0; i<student.n_assignments; i++){
        std::cout << student.grades[i] << " ";
    }
    std::cout << "\n";
}