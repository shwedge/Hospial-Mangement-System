//
// Created by Sajjad Hossain on 1/16/2025.
//

#ifndef HOSPITALMANAGEMENTSYSTEM2025_PATIENT_H
#define HOSPITALMANAGEMENTSYSTEM2025_PATIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Appointment;

class Patient {
public:
    Patient() = default;
    Patient(string id, string name, int age, string gender, string contact);

    void displayPatientInfo() const;
    void savePatientsToFile(const vector<Patient>& patients);
    void loadPatientsFromFile(vector<Patient>& patients);
    void addPatients(vector<Patient>& patients);
    void viewPatients(const vector<Patient>& patients);
    void searchPatients(const vector<Patient>& patients);
    void deletePatientInfo(vector<Patient>& patients);
    void editPatientInfo(vector<Patient>& patients);
    void addAppointments(Appointment* apps);
    void displayPatientAppointments() const;

    const string &getGender() const;
    const string &getName() const;
    const string &getId() const;
    const string &getContact() const;
    int getAge() const;
    void setId(const string &id);
    void setGender(const string &gender);
    void setName(const string &name);
    void setContact(const string &contact);
    void setAge(int age);

    friend ostream& operator<<(ostream& os, const Patient& p);
    friend istream& operator>>(istream& is, Patient& p);
private:
    string id, name, gender, contact;
    int age{};
    vector<Appointment*> appointments;
};




#endif //HOSPITALMANAGEMENTSYSTEM2025_PATIENT_H
