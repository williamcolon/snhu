/// cpp
// IT-499 Code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// William Colon
// william.colon@snhu.edu
// CS-499
// Version 4.8  2024/10/10
// This Appointment scheduling software 
// is to automate and organize appointments by allowing 
// customers to book appointments with service providers 
// via an app, or website in the form of an online scheduler or kiosk.

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <sstream>

// Struct to represent an Appointment with relevant details
struct Appointment {
    std::string name;        // Name of the person for the appointment
    std::string date;        // Date formatted as YYYY-MM-DD
    std::string time;        // Time formatted as HH:MM
    std::string description; // Brief description of the appointment
};

// The AppointmentService class manages a collection of appointments
class AppointmentService {
private:
    std::vector<Appointment> appointments; // Vector to store added appointments
    const std::string filename = "appointment.csv"; // Filename for CSV storage

    // Function to validate date input
    bool validateDate(const std::string& date) {
        return std::regex_match(date, std::regex(R"(\d{4}-\d{2}-\d{2})")); // Checks if date matches YYYY-MM-DD format
    }

    // Function to validate time input
    bool validateTime(const std::string& time) {
        return std::regex_match(time, std::regex(R"(\d{2}:\d{2})")); // Checks if time matches HH:MM format
    }

    // Function to save appointments to CSV file
    void saveToCSV() {
        std::ofstream file(filename, std::ios::app); // Opens file in append mode
        for (const auto& appointment : appointments) {
            // Writes each appointment's details as a comma-separated line in the CSV file
            file << appointment.name << "," << appointment.date << "," << appointment.time << "," << appointment.description << "\n";
        }
    }

    // Function to load appointments from CSV file
    void loadFromCSV() {
        std::ifstream file(filename); // Opens file for reading
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream s(line);
            Appointment appointment;
            std::string field;

            std::getline(s, appointment.name, ','); // Reads name field until a comma
            std::getline(s, appointment.date, ','); // Reads date field until a comma
            std::getline(s, appointment.time, ','); // Reads time field until a comma
            std::getline(s, appointment.description, ','); // Reads description field until a comma

            appointments.push_back(appointment); // Adds the loaded appointment to the vector
        }
    }

public:
    AppointmentService() {
        loadFromCSV(); // Load existing appointments from the CSV file on initialization
    }

    // Function to add a new appointment
    void addAppointment() {
        Appointment appointment; // Create an Appointment object to store user input

        std::cout << "Enter name: ";
        std::getline(std::cin, appointment.name); // Reads the name input from the user

        // Input validation for the appointment date
        std::string date;
        while (true) {
            std::cout << "Enter date (YYYY-MM-DD): ";
            std::getline(std::cin, date); // Reads the date input from the user
            if (validateDate(date)) {
                appointment.date = date; // Assign valid date to the appointment
                break; // Exit loop if date is valid
            }
            std::cout << "Invalid date format. Please try again.\n"; // Prompt for re-entry if date is invalid
        }

        // Input validation for the appointment time
        std::string time;
        while (true) {
            std::cout << "Enter time (HH:MM): ";
            std::getline(std::cin, time); // Reads the time input from the user
            if (validateTime(time)) {
                appointment.time = time; // Assign valid time to the appointment
                break; // Exit loop if time is valid
            }
            std::cout << "Invalid time format. Please try again.\n"; // Prompt for re-entry if time is invalid
        }

        std::cout << "Enter description: ";
        std::getline(std::cin, appointment.description); // Reads the description input from the user

        appointments.push_back(appointment); // Adds the new appointment to the vector
        saveToCSV(); // Save updated appointments to CSV
        std::cout << "Appointment added successfully!\n"; // Confirmation message
    }

    // Function to display all scheduled appointments
    void displayAppointments() const {
        if (appointments.empty()) {
            std::cout << "No appointments scheduled.\n"; // Message if there are no appointments
            return;
        }
        std::cout << "Scheduled Appointments:\n";
        for (const auto& appointment : appointments) {
            // Displays each appointment's details
            std::cout << "Name: " << appointment.name
                << ", Date: " << appointment.date
                << ", Time: " << appointment.time
                << ", Description: " << appointment.description << "\n";
        }
    }

    // Function to clear all appointments
    void clearAppointments() {
        appointments.clear(); // Clears the vector of appointments
        std::ofstream file(filename, std::ios::trunc); // Truncates the CSV file, effectively clearing its content
        std::cout << "All appointments cleared.\n"; // Confirmation message
    }

    // Function to delete a specific appointment by name
    void deleteAppointment() {
        std::string name;
        std::cout << "Enter the name of the appointment you wish to delete: ";
        std::getline(std::cin, name); // Reads the name of the appointment to delete

        // Removes the appointment from the vector based on the name
        auto it = std::remove_if(appointments.begin(), appointments.end(),
            [&name](const Appointment& app) { return app.name == name; });

        if (it != appointments.end()) {
            appointments.erase(it, appointments.end()); // Erases the matching appointments from the vector
            std::ofstream file(filename, std::ios::trunc); // Clears the CSV file
            saveToCSV(); // Resaves remaining appointments to the CSV file
            std::cout << "Appointment deleted successfully.\n"; // Confirmation message
        }
        else {
            std::cout << "No appointment found for the name: " << name << "\n"; // Message if no matching appointment is found
        }
    }
};

int main() {
    std::cout << "William Colon Scheduler\n"; // Display title
    AppointmentService service; // Create an instance of AppointmentService
    int choice;
    do {
        // Display menu options for the user
        std::cout << "1. Add Appointment\n2. Display Appointments\n3. Clear Appointments\n4. Delete Appointment\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Reads user choice
        std::cin.ignore(); // Ignore the newline character left in the buffer

        switch (choice) {
        case 1:
            service.addAppointment(); // Calls function to add an appointment
            break;
        case 2:
            service.displayAppointments(); // Calls function to display all appointments
            break;
        case 3:
            service.clearAppointments(); // Calls function to clear all appointments
            break;
        case 4:
            service.deleteAppointment(); // Calls function to delete a specific appointment
            break;
        case 5:
            std::cout << "Exiting the appointment service.\n"; // Exit message
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n"; // Message for invalid choice
        }
    } while (choice != 5); // Continue until user chooses to exit

    return 0; // Return statement indicating successful execution
}

///   - **addAppointment()**: This function performs several validation checks on the input. The time to execute is relatively constant due to the loops being dependent on user input. In the worst-case scenario, the function will keep prompting until valid input is received. Therefore, the average time complexity is O(n) where n is the number of attempts made to enter valid data.
//    - **displayAppointments()**: This function iterates through the vector of appointments. The time complexity is O(m), where m is the number of appointments in the vector, as it must print out each appointment detail.
//    - **clearAppointments()**: This function clears the vector and has a time complexity of O(1) since it just clears the vector without iterating through it.
//    - **saveToCSV()**: The function saves appointments to the CSV file, having a time complexity of O(m), where m is the number of appointments being saved.
//    - **loadFromCSV()**: This function loads appointments from the CSV file with a complexity of O(m) as it reads all the entries from the file.
//    - **Main Function**: The menu system is a simple do-while loop that runs until the user opts to exit. The complexity of this function is O(1) for each menu operation but could vary based on the options selected by the user.
//    This refined code structure is clear and efficient, with a focus on best practices for user input validation and displaying results accordingly.
/// 