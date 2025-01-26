//
// Created by Sajja on 1/16/2025.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include "Patient.h"
#include "Appointment.h"

using namespace std;

Patient::Patient(string id, string name, int age, string gender, string contact) :
                id(id), name(name), age(age), gender(gender), contact(contact) {}

const string &Patient::getGender() const {
    return gender;
}

const string &Patient::getName() const {
    return name;
}

const string &Patient::getId() const {
    return id;
}

const string &Patient::getContact() const {
    return contact;
}

int Patient::getAge() const {
    return age;
}

void Patient::setId(const string &id) {
    Patient::id = id;
}

void Patient::setGender(const string &gender) {
    Patient::gender = gender;
}

void Patient::setName(const string &name) {
    Patient::name = name;
}

void Patient::setContact(const string &contact) {
    Patient::contact = contact;
}

void Patient::setAge(int age) {
    Patient::age = age;
}
//
//const vector<Appointment> &Patient::getAppointments() const {
//    return appointments;
//}
//
//void Patient::setAppointments(const vector<Appointment> &appointments) {
//    Patient::appointments = appointments;
//}

void Patient::displayPatientInfo() const {
    cout << "\n--- Patient Information---" << endl;
    cout << "ID: " << id << "\nName: " << name << "\nAge: "
        << age <<"\nGender: " << gender <<"\nContact: " << contact << endl;
}

ostream& operator<<(ostream& os, const Patient &p) {
    os << p.id << "," << p.name <<"," << p.age <<"," << p.gender <<"," << p.contact;
    return os;
}

istream& operator>>(istream& is, Patient &p) {
    string line;
    if (!getline(is,line)) return is;
    stringstream ss(line);
    getline(ss, p.id, ',');
    getline(ss, p.name, ',');
    ss >> p.age;
    ss.ignore();
    getline(ss, p.gender, ',');
    getline(ss, p.contact);
    return is;
}

void Patient::savePatientsToFile(const vector<Patient>& patients) {
    ofstream outFile("patients.txt");
    if (outFile.is_open()){
        for(const auto& patient: patients){
            outFile << patient << endl;
        }
        outFile.close();
    }else{
        cout << "Error: unable to save data to the file." << endl;
    }
}

void Patient::loadPatientsFromFile(vector<Patient>& patients) {
    ifstream inFile("patients.txt");
    if (!inFile.is_open()){
        cout << "Error: Unable to open the file." << endl;
        return;
    }

    string line;
    while(getline(inFile, line)){
        stringstream ss(line);
        Patient patient;
        ss >> patient;
        patients.push_back(patient);
    }
    inFile.close();
}

void Patient::addPatients(vector<Patient>& patients) {
    string id, name, gender, contact;
    int age;

    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, name);
    cout << "Enter age: ";
    cin>> age;
    cin.ignore();
    cout << "Enter Patient Gender: ";
    getline(cin, gender);
    cout << "Enter Patient Contact: ";
    getline(cin, contact);

    Patient newPatient(id, name, age, gender, contact);
    patients.push_back(newPatient);
    savePatientsToFile(patients);

    cout <<"\nPatient add successfully." << endl;
}

void Patient::viewPatients(const vector<Patient> &patients) {
    if (patients.empty()){
        cout << "No patients to display." << endl;
        return;
    } else{
        for (const Patient& patient : patients){
            patient.displayPatientInfo();
            cout <<  "-----------------" << endl;
        }
    }
}

void Patient::searchPatients(const vector<Patient> &patients) {
    string ID;
    cout << "Enter Patient ID: ";
    getline(cin, id);

    bool found = false;
    for (const auto& patient: patients){
        if (patient.getId() == id){
            patient.displayPatientInfo();
            found = true;
            break;
        }
    }
    if(!found){
        cout << "No patient available under this ID." << endl;
    }
}

void Patient::deletePatientInfo(vector<Patient> &patients) {
    string ID;
    cout << "Enter Patient ID: ";
    getline(cin, ID);
    cin.ignore();
    cin.clear();

    for (auto& patient: patients){
        if (patient.id == ID){
            auto it = remove_if(patients.begin(), patients.end(),[ID] (const Patient& patient){
                return patient.getId() == ID;
            });
            patients.erase(it, patients.end());
            savePatientsToFile(patients);
            cout << "Patient deleted Successfully." << endl;
        }
    }
    cout << "Invalid Patient ID!" << endl;
}

void Patient::editPatientInfo(vector<Patient> &patients) {
    string patientID;
    cout << "Enter Patient ID: ";
    getline (cin, patientID);
    cin.ignore();

    for (Patient& patient : patients){
        if (patient.getId() == patientID){
            cout << "Editing patient details for this ID: " <<patientID << endl;

            string newID;
            cout << "Enter new ID: ";
            getline(cin, newID);
            if(!newID.empty()) patient.setId(newID);

            string newName;
            cout << "Enter new Name: ";
            getline(cin, newName);
            if (!newName.empty()) patient.setName(newName);

            string newAge;
            cout << "Enter new Age: ";
            getline(cin, newAge);
            if (!newAge.empty()) patient.setAge(stoi(newAge));

            string newGender;
            cout << "Enter new Gender: ";
            getline(cin, newGender);
            if(!newGender.empty()) patient.setGender(newGender);

            string newContact;
            cout << "Enter new Contact: ";
            getline(cin, newContact);
            cin.ignore();
            cin.clear();
            if (!newContact.empty()) patient.setContact(newContact);

            savePatientsToFile(patients);
            cout << "Patient Info Updated successfully." << endl;
            return;
        }
    }
    cout << "No Patient available under this ID." << endl;
}

void Patient::addAppointments(Appointment* apps) {
        appointments.push_back(apps);
}

void Patient::displayPatientAppointments() const {
    cout << "Appointment for Patient: " << name << "(ID: " << id << ")\n";
    for (const auto& appt: appointments){
        appt->displayAppointmentInfo();
//        cout << "-  Appointment ID: " << appt->getPatientId()<< "on" << appt->getDate() << endl;
    }
}


