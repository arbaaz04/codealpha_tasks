#include <iostream>
#include <string>
#include <vector>

using namespace std;

string calculategrade(double coursegpa) {
    if (coursegpa >= 4.0){
    	return "A";
	}
	if (coursegpa >= 3.67){
    	return "A-";
	}
	if (coursegpa >= 3.33){
    	return "B+";
	}
	if (coursegpa >= 3.0){
    	return "B";
	}
	if (coursegpa >= 2.67){
    	return "B-";
	}
	if (coursegpa >= 2.33){
    	return "C+";
	}
	if (coursegpa >= 2.0){
    	return "C";
	}
	if (coursegpa >= 1.67){
    	return "C-";
	}
	else{
		return "F";
	}
}

class course {
    string coursename;
    string grade;
    double coursegpa;
    int crhrs;
    
    public:
        course(string name, double gpa, int hrs) {
            coursename = name;
            coursegpa = gpa;
            crhrs = hrs;
            setgrade();
        }
        
        double getgpa() const {
            return coursegpa;
        }

        int getcrhrs() const {
            return crhrs;
        }
        
        void setgrade() {
            grade = calculategrade(coursegpa);
        }

        void display() const {
            cout << "Course Name: " << coursename << ", Course GPA: " << coursegpa << ", Grade: " << grade << ", Credit Hours: " << crhrs << endl;
        }
};

class student {
    vector<course> courses;

    public:
        void addcourse(const course &c) {
            courses.push_back(c);
        }

        void displayall() const {
            for (const auto &c : courses) {
                c.display();
            }
        }

        double calculatetotalcrhrs() const {
            double totalcrhrs = 0;
            for (const auto &c : courses) {
                totalcrhrs += c.getcrhrs();
            }
            return totalcrhrs;
        }

        double calculatetotalgp() const {
            double tgp = 0;
            for (const auto &c : courses) {
                tgp += c.getgpa() * c.getcrhrs();
            }
            return tgp;
        }

        double calculategpa() const {
            double totalcrhrs = calculatetotalcrhrs();
            if (totalcrhrs == 0) return 0;
            double tgp = calculatetotalgp();
            return tgp / totalcrhrs;
        }
        
        string setfinalgrade() const {
            double gpa = calculategpa();
            return calculategrade(gpa);
        }
};

int main() {
    cout << "GPA Calculator\n\n";
    
    student s1; 
    int numofcourses;
    cout << "Enter the number of courses to calculate GPA: ";
    cin >> numofcourses;
    
    for (int x = 0; x < numofcourses; ++x) {
        string cname;
        double coursegpa;
        int crhrs;

		cout << endl;
        cout << "Enter course name: ";
        cin >> cname;
        cout << "Enter course GPA (out of 4.0): ";
        cin >> coursegpa;
        cout << "Enter credit hours: ";
        cin >> crhrs;

        course c(cname, coursegpa, crhrs);
        s1.addcourse(c);
    }
    
    cout << "\n\nCourses taken:\n";
    s1.displayall();

    double totalcrhrs = s1.calculatetotalcrhrs();
    double tgp = s1.calculatetotalgp();
    double gpa = s1.calculategpa();
    string finalgrade = s1.setfinalgrade();
    
    cout << "\nTotal Credit Hours: " << totalcrhrs << endl;
    cout << "Total Grade Points: " << tgp << endl;
    cout << "Semester GPA: " << gpa << endl;
    cout << "Semester Grade: " << finalgrade << endl;

}
