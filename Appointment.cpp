//
// Created by Sajjad Hossain on 1/19/2025.
//

#include "Appointment.h"
#include "Patient.h"
#include "Doctor.h"
#include <sstream>

Appointment::Appointment(string appId,Patient* patient, Doctor* doctor, string pId, string docId, string date, string tm, string st):
appointmentId(appId), patientId(pId), doctorId(docId), date(date), time(tm), status(st), patient(patient), doctor(doctor)
{
    patient->addAppointments(this);
    doctor->addAppointment(this);
}

const string &Appointment::getAppointmentId() const {
    return appointmentId;
}

const string &Appointment::getPatientId() const {
    return patientId;
}

const string &Appointment::getDoctorId() const {
    return doctorId;
}

const string &Appointment::getDate() const {
    return date;
}

const string &Appointment::getTime() const {
    return time;
}

const string &Appointment::getStatus() const {
    return status;
}

void Appointment::setDate(const string &date) {
    Appointment::date = date;
}

void Appointment::setTime(const string &time) {
    Appointment::time = time;
}

void Appointment::setStatus(const string &status) {
    Appointment::status = status;
}

void Appointment::displayAppointmentInfo() const {
    cout << "\nAppointment ID: " << appointmentId << "\nPatient ID: " << patientId << "\nDoctor ID: "
        << doctorId << "\nDate: " <<date <<"\nTime: " << time << "\nStatus: " << status << endl;
}

ostream &operator<<(ostream &os, const Appointment &app) {
    os << app.appointmentId << "," << app.patientId <<"," << app.doctorId <<","
        <<app.date <<"," << app.time <<"," << app.status;
    return os;
}

istream &operator>>(istream &is, Appointment &app) {
    string line;
    if(!getline(is, line)) return is;
    stringstream ss(line);
    getline(ss, app.appointmentId, ',');
    getline(ss, app.patientId, ',');
    getline(ss, app.doctorId, ',');
    getline(ss, app.date, ',');
    getline(ss, app.time, ',');
    getline(ss, app.status);
    ss.ignore();
    return is;
}

void Appointment::saveAppointmentsToFile(const vector<Appointment> &app) {
    ofstream outFile("appointments.txt", ios::app);
    if(outFile.is_open()){
        for (const auto& appointment: app){
            outFile << appointment << endl;
        }
        outFile.close();
    } else{
        cout << "Error: Unable to save data to file." << endl;
    }
}

void Appointment::loadAppointmentFromFile(vector<Appointment> &app) {
    ifstream inFile("appointments.txt");
    if (!inFile.is_open()){
        cout << "Error: Unable to open the file." << endl;
        return;
    }
    string line;
    while(getline(inFile, line)){
        stringstream ss(line);
        Appointment appointment;
        ss >> appointment;
        app.push_back(appointment);
    }
    inFile.close();
}
Patient* findPatient(const std::vector<Patient>& patients, const std::string& id) {
    for (const auto& patient : patients) {
        if (patient.getId() == id) {
            return new Patient(patient);  // ✅ Return a copy of the patient
        }
    }
    return nullptr;
}

// ✅ Find Doctor by ID
Doctor* findDoctor(const std::vector<Doctor>& doctors, const std::string& id) {
    for (const auto& doctor : doctors) {
        if (doctor.getDoctorId() == id) {
            return new Doctor(doctor);  // ✅ Return a copy of the doctor
        }
    }
    return nullptr;
}

void Appointment::addAppointment(vector<Appointment>& app, vector<Patient>& patients, vector<Doctor>& doctors) {
    string appID, pID, dID, dt, tm;

    cout <<"Enter Appointment ID: ";
    getline(cin, appID);
    cout << "Enter Patient ID: ";
    getline(cin, pID);
    cout << "Enter Doctor ID: ";
    getline(cin, dID);
    cout << "Enter date: ";
    getline(cin, dt);
    cout << "Enter time: ";
    getline(cin, tm);

    Patient* newPatient = findPatient(patients, pID);
    Doctor* newDoctor = findDoctor(doctors, dID);

//    for (auto& p : patients){
//        if (p.getId() == patientId){
//            selectedPatient = &p;
//            break;
//        }
//    }
//    for (auto& d : doctors){
//        if (d.getDoctorId() == doctorId){
//            selectedDoctor = &d;
//            break;
//        }
//    }
    if (!newPatient || !newDoctor){
        cout << "Patient & Doctor not found!"<< endl;
        return;
    }

    Appointment newAppointment(appID, newPatient, newDoctor, pID, dID, dt, tm, "Scheduled");
    app.push_back(newAppointment);
    saveAppointmentsToFile(app);

    cout << "\nAppointment schedule successful!" << endl;
}

void Appointment::viewAppointment(const vector<Appointment> &app) {
    if (!app.empty()){
        for (const auto& appointment: app){
            appointment.displayAppointmentInfo();
            cout << "--------------------" << endl;
        }
    }else {
        cout << "No appointment scheduled." << endl;
    }
}

void Appointment::searchAppointment(const vector<Appointment> &appointment) {
    string searchID;
    cout << "Enter Appointment ID: ";
    getline(cin, searchID);
    cin.ignore();

    bool found = false;
    for (const auto& app: appointment){
        if (app.getAppointmentId() == searchID){
            app.displayAppointmentInfo();
            found = true;
            break;
        }
    } if(!found){
        cout << "Invalid Appointment ID." << endl;
    }
}

void Appointment::editAppointment(vector<Appointment> &appointment) {
    string appID;
    cout << "Enter Appointment ID: ";
    getline(cin, appID);
    cin.ignore();

    for (auto& app: appointment){
        if (app.getAppointmentId() == appID){
            cout << "Editing details for this ID " << appID << endl;

            string newDate;
            cout << "Enter new Date: ";
            getline(cin, newDate);
            if(!newDate.empty()) app.setDate(newDate);

            string newTime;
            cout << "Enter new Time: ";
            getline(cin, newTime);
            if (!newTime.empty()) app.setTime(newTime);

            cout << "Appointment update successfully." << endl;
            return;
        } else{
            cout << "Invalid given Appointment ID." << endl;
        }
    }
}

void Appointment::cancelAppointment(vector<Appointment> &appointment) {
    string searchID;
    if(appointment.empty()){
        cout << "No appointment in the file." << endl;
        return;
    }

    for (auto& app: appointment){
        if(app.getAppointmentId() == searchID){
            app.setStatus("Canceled");
            cout << "Appointment canceled successfully." << endl;
            return;
        }
    }
}

Patient *Appointment::getPatient() const {
    return patient;
}

Doctor *Appointment::getDoctor() const {
    return doctor;
}
