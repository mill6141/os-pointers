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
double round_to_one_decimal_place(double num);

int main(int argc, char **argv)
{
    Student student;
    double average;

    std::string message;

    //printf("%d", promptInt("Please enter an int \t", -100, 100));

    student.id = promptInt("Please enter the student's id number: ", 1, 999999999);
    //std::cin.ignore();

    student.f_name = promptString("Please enter the student's first name: ");
    student.l_name = promptString("Please enter the student's last name: ");
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);
    //std::cin.ignore();

    student.grades = new double [student.n_assignments];
    std::cout << "\n";

    for (int i=0; i<student.n_assignments; i++){
        message = "Please enter grade for assignment " + std::to_string(i) + ": ";
        student.grades[i] = promptDouble(message, 0.0, 1000.0);
        //std::cin.ignore();
    }


    //printStudentInfo(student);
    // Sequence of user input -> store in fields of `student`

    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`

    calculateStudentAverage(&student, &average);

    std::cout << "\nStudent: " << student.f_name << " " << student.l_name <<  " [" << student.id << "]\n";
    std::cout << "  Average grade: " << round_to_one_decimal_place(average) << "\n";

    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;


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
        std::getline(std::cin, result);

        for (int i=0; i<result.length(); i++){
            char c = result[i];

            if((c == 45) && (i==0)){
                negative = true;
                continue;
            }
            
            if(((c < 48) || (c > 57 ))){
                std::cout << "Sorry, I cannot understand your answer";
                std::cout << std::endl;

                break;
            }

            final_int += ( pow(10, (result.length() - 1) - i) * (c - 48)); // convert char to int and add to final_int

            if(i == result.length()-1){
                finished = true;
            }
        }

        if(negative){
            final_int *= -1;
        }

        if (((final_int < min) || (final_int > max)) && finished){
            //std::cout << "Please enter a number between [" << min <<", " << max << "] \n";
            std::cout << "Sorry, I cannot understand your answer";
            std::cout << std::endl;

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
    // Code to prompt user for an int
    std::string result;
    
    bool finished = false;
    bool negative = false;
    bool decimal = false;

    int decimal_index = -1;

    double final_double = 0;

    while (!finished){
        final_double = 0;
        negative = false;
        std::cout << message;
        std::getline(std::cin, result);

        if(result.length() == 0){
            std::cout << "Sorry, I cannot understand your answer";
            std::cout << std::endl;

            continue;
        } else if(result.length() > 10){
            //std::cout << "Please enter a number with at most 10 digits, including the decimal \n";
            std::cout << "Sorry, I cannot understand your answer";
            std::cout << std::endl;

            continue;
        }

        for (int i=0; i<result.length(); i++){
            char c = result[i];

            if((c == 45) && (i==0)){
                negative = true;
                continue;
            }
            
            if((c != 46) && ((c < 48) || (c > 57 ))){
                std::cout << "Sorry, I cannot understand your answer";
                std::cout << std::endl;

                break;
            } else if (c == 46){
                // Entereed a decimal point - only allow one
                if (decimal){
                    std::cout << "Sorry, I cannot understand your answer";
                    std::cout << std::endl;

                    break;
                } else {
                    decimal = true;
                    decimal_index = i;
                    //final_double /= pow(10, (result.length() - 1) - i); // divide by the appropriate power of 10 to shift the decimal point
                    continue;
                }
            }

            if(!decimal){
                final_double += ( pow(10, (result.length() - 1) - i) * (c - 48)); // convert char to double and add to final_double
            } else{
                final_double += ( pow(10, (result.length() - 1) - i + 1) * (c - 48)); // convert char to double and add to final_double
            }
            if(i == result.length()-1){
                finished = true;
            }
        }

        if(decimal_index != -1){
            final_double /= pow(10, (result.length()) - decimal_index); // divide by the appropriate power of 10 to shift the decimal point
        }

        if(negative){
            final_double *= -1;
        }

        if ((final_double < min) || (final_double > max)){
            //std::cout << "You entered: " << final_double << " \n";
            //std::cout << "Please enter a number between [" << min <<", " << max << "] \n";
            std::cout << "Sorry, I cannot understand your answer";
            std::cout << std::endl;

            finished = false;
        }
    }

    //std::cout << "\n" << final_double << "\n";
    return final_double;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade

    // object will be our student struct, so cast the void pointer to a Student pointer
    Student *student = (Student *) object;

    // Our average will be the sum of the grades divided by the number of assignments
    double sum = 0;

    for (int i=0; i<student->n_assignments; i++){
        sum += student->grades[i];
    }
    *avg = sum / student->n_assignments;
}

char* promptString(std::string message){
    // Code to prompt user for a string
    std::string result;
    
    bool finished = false;

    char* final_string;    

    while (!finished){
        std::cout << message;
        std::getline(std::cin, result);

        final_string = new char [result.length() + 1];
        for (int i=0; i<result.length(); i++){
            char c = result[i];
            
            if(((c < 65) || (c > 90)) && ((c < 97) || (c > 122)) && (c != 32)){
                std::cout << "Sorry, I cannot understand your answer";
                std::cout << std::endl;

                break;
            }

            if(i == result.length()-1){
                finished = true;
            }
            final_string[i] = c;
        }
        
    }

    final_string[result.length()] = '\0'; // Null terminate the string
    //std::cout << "\n" << final_int << "\n";
    return final_string;
}

double round_to_one_decimal_place(double num){
    return std::round(num * 10) / 10;
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