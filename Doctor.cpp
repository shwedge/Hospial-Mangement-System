//
// Created by Sajja on 1/17/2025.
//

#include "Doctor.h"
#include "Appointment.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Doctor::Doctor(string id, string name, string spec, string contact, int exp) :
doctorID(id), name(name), specialization(spec), contact(contact), experience(exp)
{
}

const string &Doctor::getDoctorId() const {
    return doctorID;
}

void Doctor::setDoctorId(string &doctorId) {
    doctorID = doctorId;
}

const string &Doctor::getName() const {
    return name;
}

void Doctor::setName(const string &name) {
    Doctor::name = name;
}

const string &Doctor::getSpecialization() const {
    return specialization;
}

void Doctor::setSpecialization(const string &specialization) {
    Doctor::specialization = specialization;
}

int Doctor::getExperience() const {
    return experience;
}

void Doctor::setExperience(int experience) {
    Doctor::experience = experience;
}

const string &Doctor::getContact() const {
    return contact;
}

void Doctor::setContact(const string &contact) {
    Doctor::contact = contact;
}

void Doctor::displayDoctors() const {
    cout <<"---Doctors Information---" << endl;
    cout <<"ID: "<< doctorID << "\nName: " << name << "\nSpecialization: " << specialization
            << "\nContact: " << contact << "\nExperience: "<< experience << endl;
}

ostream &operator<<(ostream &os, const Doctor &doctor) {
    os << doctor.doctorID <<"," << doctor.name << "," <<doctor.specialization << ","
        << doctor.contact << "," << doctor.experience;
    return os;
}

istream &operator>>(istream &is, Doctor &doctor) {
    string line;
    if(!getline(is, line)) return is;
    stringstream ss(line);
    getline(ss, doctor.doctorID, ',');
    getline(ss,doctor.name,',');
    getline(ss, doctor.specialization, ',');
    getline(ss, doctor.contact, ',');
    ss >> doctor.experience;
    ss.ignore();
    return is;
}

void Doctor::saveDoctorsToFile(const vector<Doctor> &doctors) {
    ofstream outFile("doctors.txt");
    if (outFile.is_open()){
        for (const auto& doctor: doctors){
            outFile << doctor << endl;
        }
        outFile.close();
    }else{
        cout << "Error: Unable to save data to file!" << endl;
    }
}

void Doctor::loadDoctorsFromFile(vector<Doctor> &doctors) {
    ifstream inFile("doctors.txt");
    if (!inFile.is_open()){
        cout << "Error: Unable to open the file." <<endl;
        return;
    }

    string line;
    while(getline(inFile, line)){
        stringstream ss(line);
        Doctor doctor;
        ss >> doctor;
        doctors.push_back(doctor);
    }
    inFile.close();
}

void Doctor::addDoctor(vector<Doctor>& doctors) {
    string id, name, spec, contact;
    int exp;

    cout << "Enter Doctor ID: ";
    getline(cin, id);
    cout << "Enter Doctor name: ";
    getline(cin, name);
    cout << "Enter Speciality: ";
    getline(cin, spec);
    cout << "Enter Contact: ";
    getline(cin, contact);
    cout << "Enter years of experience: ";
    cin >> exp;
    cin.ignore();

    Doctor newDoctor(id, name, spec, contact, exp);
    doctors.push_back(newDoctor);
    saveDoctorsToFile(doctors);

    cout << "\nDoctor added successfully." <<endl;
}

void Doctor::viewDoctors(const vector<Doctor> &doctors) {
    if (doctors.empty()){
        cout << "No doctor in the file." << endl;
        return;
    } else{
        for (const auto& doctor: doctors){
            doctor.displayDoctors();
            cout << "---------------" << endl;
        }
    }
}

void Doctor::editDoctor(vector<Doctor> &doctors, vector<Appointment>& appointments) {
    string id;
    cout << "Enter Doctor ID: ";
    getline(cin, id);
    cin.ignore();

    for (auto& doctor: doctors){
        if (doctor.getDoctorId() == id){
            cout << "Editing details for this doctor ID: " << id << endl;

            string newID;
            cout << "Enter new ID: ";
            getline(cin, newID);
            if(!newID.empty()) doctor.setDoctorId(newID);

            string newName;
            cout << "Enter new Name: ";
            getline (cin, newName);
            if(!newName.empty()) doctor.setName(newName);

            string newSpec;
            cout << "Enter new speciality: ";
            getline(cin, newSpec);
            if (!newSpec.empty()) doctor.setSpecialization(newSpec);

            string newContact;
            cout << "Enter new Contact: ";
            getline(cin, newContact);
            if (!newContact.empty()) doctor.setContact(newContact);

            string newExp;
            cout << "Enter new Experience: ";
            getline(cin, newExp);
            if(!newExp.empty()) doctor.setExperience(stoi(newExp));

            saveDoctorsToFile(doctors);
            cout << "Doctor Info Updated." << endl;
        }
        else{
            cout << "No Doctor available under this ID." << endl;
        }
    }
}

void Doctor::searchDoctors(const vector<Doctor> &doctors) {
    string id;
    cout << "Enter Doctor ID: ";
    getline(cin, id);

    bool found = false;
    for (const auto& doctor : doctors){
        if (doctor.getDoctorId() == id){
            doctor.displayDoctors();
            found = true;
            break;
        }
    }if (!found){
        cout << "Invalid Doctor ID." << endl;
    }
}

void Doctor::deleteDoctor(vector<Doctor> &doctors, vector<Appointment>& appointment) {
    string id;
    cout << "Enter doctor ID: ";
    getline(cin,id);

    for (auto& doctor : doctors){
        if (doctor.getDoctorId()== id){
            auto it = remove_if(doctors.begin(), doctors.end(),
                                [id](const Doctor& doctors){
                                    return doctors.getDoctorId() == id;
            });
            if (it != doctors.end()) {
                doctors.erase(it, doctors.end());

                saveDoctorsToFile(doctors);
                auto appIt = remove_if(appointment.begin(), appointment.end(), [id](const Appointment& appointments){
                    return appointments.getAppointmentId() == id;
                });
                appointment.erase(appIt,appointment.end());

                cout << "Doctor Info Eliminated!" << endl;
            }
        } else{
            cout << "Invalid Doctor ID!" <<endl;
        }
    }
}

void Doctor::setAvailability() {
    int n;
    cout << "Enter numbers of available slot: ";
    cin >>n;
    cin.ignore();

    availableSlots.clear();
    for (int i = 0; i < n; i++){
        string slot;
        cout << "Enter slots" << i + 1 <<"(eg: 10:00AM - 11:00AM): ";
        getline(cin, slot);
        availableSlots.push_back(slot);
    }
    cout << "Available slot Successfully updated." <<endl;
}

void Doctor::viewAvailable() const {
    if (availableSlots.empty()){
        cout << "No available slot for " << name <<"." << endl;
        return;
    }

    cout << "Available slot for " << name << endl;
    for (const auto& slot : availableSlots){
        cout << "- " << slot <<"\n";
    }
}

void Doctor::removeAvailableSlot(const string &slot) {
    auto it  = find(availableSlots.begin(), availableSlots.end(), slot);
    if (it != availableSlots.end()){
        availableSlots.erase(it);
        cout << "Slot \"" << slot << "\"removed.\n";
    }else{
        cout << "No slot found!\n" << endl;
    }
}

void Doctor::addAppointment(Appointment* appt) {
        appointments.push_back(appt);
}

void Doctor::displayAppointments() const {
    cout << "Appointment for Doctor: "<< name <<"(ID: " << doctorID << ")\n";
    for (const auto& appt : appointments){
        appt->displayAppointmentInfo();
//        cout << "Appointment ID: " << appt->getPatientId() <<"on" << appt->getDate() << endl;
    }
}

