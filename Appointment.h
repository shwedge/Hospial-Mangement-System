//
// Created by Sajja on 1/19/2025.
//

#ifndef HOSPITALMANAGEMENTSYSTEM2025_APPOINTMENT_H
#define HOSPITALMANAGEMENTSYSTEM2025_APPOINTMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Patient;
class Doctor;

class Appointment {
public:
    Appointment() = default;
    Appointment(string appId,Patient* patient, Doctor* doctor, string pId, string docId, string date, string tm, string st = "Schedule");

    void displayAppointmentInfo() const;
    void saveAppointmentsToFile(const vector<Appointment>& app);
    void loadAppointmentFromFile(vector<Appointment>& app);
    void addAppointment(vector<Appointment>& app, vector<Patient>& patients, vector<Doctor>& doctors);
    void viewAppointment(const vector<Appointment>& app);
    void searchAppointment(const vector<Appointment>& appointment);
    void editAppointment(vector<Appointment>& appointment);
    void cancelAppointment(vector<Appointment>& appointment);

//    Patient* findPatient(const std::vector<Patient>& patients, const std::string& id);
//    Doctor* findDoctor(const std::vector<Doctor>& doctors, const std::string& id);

    void setDate(const string &date);
    void setTime(const string &time);
    void setStatus(const string &status);
    const string &getAppointmentId() const;
    const string &getPatientId() const;
    const string &getDoctorId() const;
    const string &getDate() const;
    const string &getTime() const;
    const string &getStatus() const;
    Patient *getPatient() const;
    Doctor *getDoctor() const;

    friend ostream& operator<<(ostream& os, const Appointment& app);
    friend istream& operator>>(istream& is, Appointment& app);
private:
    string appointmentId;
    string patientId;
    string doctorId;
    string date;
    string time;
    string status;
    Patient* patient{};
    Doctor* doctor{};
};


#endif //HOSPITALMANAGEMENTSYSTEM2025_APPOINTMENT_H
