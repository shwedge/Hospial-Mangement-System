//
// Created by Sajjad Hossain on 1/17/2025.
//

#ifndef HOSPITALMANAGEMENTSYSTEM2025_DOCTOR_H
#define HOSPITALMANAGEMENTSYSTEM2025_DOCTOR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Appointment;

class Doctor {
public:
    Doctor() = default;
    Doctor(string id, string name, string spec, string contact, int exp);

    void displayDoctors() const;
    void saveDoctorsToFile(const vector<Doctor>& doctors);
    void loadDoctorsFromFile(vector<Doctor>& doctors);
    void addDoctor(vector<Doctor>& doctors);
    void viewDoctors(const vector<Doctor>& doctors);
    void searchDoctors(const vector<Doctor>& doctors);
    void deleteDoctor(vector<Doctor>& doctors, vector<Appointment>& appointment);
    void editDoctor(vector<Doctor>& doctors, vector<Appointment>& appointments);
    void setAvailability();
    void viewAvailable() const;
    void removeAvailableSlot(const string& slot);
    void addAppointment(Appointment* appt);
    void displayAppointments() const;

    const vector<string> &getAvailability() const;
    void setAvailability(const vector<string> &availability);
    const string &getDoctorId() const;
    void setDoctorId(string &doctorId);
    const string &getName() const;
    void setName(const string &name);
    const string &getSpecialization() const;
    void setSpecialization(const string &specialization);
    int getExperience() const;
    void setExperience(int experience);
    const string &getContact() const;
    void setContact(const string &contact);
    const vector<Appointment> &getAppointments() const;
    void setAppointments(const vector<Appointment> &appointments);

    friend ostream& operator<<(ostream& os, const Doctor& doctor);
    friend istream& operator>>(istream& is, Doctor& doctor);
private:
    string doctorID;
    string name;
    string specialization;
    string contact;
    int experience;
    vector<string> availableSlots;
    vector<Appointment*> appointments;
};


#endif //HOSPITALMANAGEMENTSYSTEM2025_DOCTOR_H
