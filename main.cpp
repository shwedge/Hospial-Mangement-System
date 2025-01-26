#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include <jdbc/cppconn/driver.h>
#include <functional>
#include <iostream>
#include <vector>
#include <limits>
#include <jdbc/cppconn/connection.h>
#include <jdbc/mysql_driver.h>

using namespace std;
//using namespace sql;

int main() {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    Doctor doctor;
    Patient patient;
    Appointment appointment;

    doctor.loadDoctorsFromFile(doctors);
    patient.loadPatientsFromFile(patients);
    appointment.loadAppointmentFromFile(appointments);


//    linkAppointments(patients, doctors, appointments);
    try {
        // Create MySQL Driver and Connection
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        // Replace with your MySQL credentials
        string host = "localhost";  // Localhost, default MySQL port
        string user = "root";  // Change this to your MySQL username
        string password = "mypassword";  // Change this to your MySQL password

        // Get the MySQL driver instance
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(host, user, password);

        // Check connection status
        if (con->isValid()) {
            cout << "✅ MySQL Connection Successful!" << endl;
        } else {
            cout << "❌ MySQL Connection Failed!" << endl;
        }

        delete con; // Clean up

    } catch (sql::SQLException &e) {
        cout << "❌ MySQL Connection Error: " << e.what() << endl;
    }

    int choice;
    while (true){
        cout << "---Hospital Management System---\n";
        cout << "1.Add Patient\n";
        cout << "2.View Patients\n";
        cout << "3.Search Patient\n";
//        cout << "4.Delete Patient\n";
//        cout << "5.Edit Patient\n";
        cout << "4.Add Doctor\n";
        cout << "5.View Doctors\n";
        cout << "6.Schedule Appointment\n";
        cout << "7.View Appointment\n";
//        cout << "8.Search Doctor\n";
//        cout << "9.Edit Doctor Info\n";
//        cout << "10.Delete Doctor\n";
        cout << "8.Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<  "Invalid Input! Please enter a number." << endl;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                patient.addPatients(patients);
                break;
            case 2:
                patient.viewPatients(patients);
                break;
            case 3:
                patient.searchPatients(patients);
                break;
            case 4:
                doctor.addDoctor(doctors);
                break;
            case 5:
                doctor.viewDoctors(doctors);
                break;
            case 6:
                appointment.addAppointment(appointments, patients, doctors);
                break;
            case 7:
                appointment.viewAppointment(appointments);
                break;
            case 8:
                patient.savePatientsToFile(patients);
                doctor.saveDoctorsToFile(doctors);
                cout << "\nExiting Program!" << endl;
                return 0;
            default:
                cout << "Error: Invalid input. Please try again." << endl;
                continue;
        }
    }
    return 0;
}
