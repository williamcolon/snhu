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

// Structure representing an Appointment with relevant properties
struct Appointment {
    std::string clientName;    // Name of the individual for the appointment
    std::string appointmentDate; // Date formatted as YYYY-MM-DD
    std::string appointmentTime; // Time formatted as HH:MM
    std::string details;        // Brief overview of the appointment
};

// The AppointmentManager class oversees a list of appointments
class AppointmentManager {
private:
    std::vector<Appointment> scheduledAppointments; // Vector to hold appointments
    const std::string storageFile = "appointments.csv"; // File for saving and loading appointments

    // Validates date input format
    bool isDateValid(const std::string& date) {
        return std::regex_match(date, std::regex(R"(\d{4}-\d{2}-\d{2})")); // Checks date format
    }

    // Validates time input format
    bool isTimeValid(const std::string& time) {
        return std::regex_match(time, std::regex(R"(\d{2}:\d{2})")); // Checks time format
    }

    // Saves appointments to the designated CSV file
    void writeToCSV() {
        std::ofstream file(storageFile, std::ios::app); // Opens file in append mode
        for (const auto& appointment : scheduledAppointments) {
            file << appointment.clientName << "," << appointment.appointmentDate << ","
                << appointment.appointmentTime << "," << appointment.details << "\n";
        }
    }

    // Loads appointments from the CSV file
    void readFromCSV() {
        std::ifstream file(storageFile); // Opens file for reading
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            Appointment appointment;
            std::string field;

            std::getline(lineStream, appointment.clientName, ','); // Reads name field until a comma
            std::getline(lineStream, appointment.appointmentDate, ','); // Reads date field until a comma
            std::getline(lineStream, appointment.appointmentTime, ','); // Reads time field until a comma
            std::getline(lineStream, appointment.details, ','); // Reads description field until a comma

            scheduledAppointments.push_back(appointment); // Adds loaded appointment to the list
        }
    }

public:
    AppointmentManager() {
        readFromCSV(); // Loads existing appointments upon initialization
    }

    // Creates a new appointment based on user input
    void createAppointment() {
        Appointment appointment; // Create an Appointment object for user input

        std::cout << "Enter client name: ";
        std::getline(std::cin, appointment.clientName); // Reads client's name

        // Validate appointment date
        std::string dateInput;
        while (true) {
            std::cout << "Enter appointment date (YYYY-MM-DD): ";
            std::getline(std::cin, dateInput); // Reads the date input from the user
            if (isDateValid(dateInput)) {
                appointment.appointmentDate = dateInput; // Assigns valid date
                break;
            }
            std::cout << "Incorrect date format. Please try again.\n"; // Prompt for re-entry if date is invalid
        }

        // Validate appointment time
        std::string timeInput;
        while (true) {
            std::cout << "Enter appointment time (HH:MM): ";
            std::getline(std::cin, timeInput);
            if (isTimeValid(timeInput)) {
                appointment.appointmentTime = timeInput; // Assigns valid time
                break;
            }
            std::cout << "Incorrect time format. Please try again.\n"; // Prompt for re-entry if time is invalid
        }

        std::cout << "Enter appointment details: ";
        std::getline(std::cin, appointment.details); // Reads appointment details

        scheduledAppointments.push_back(appointment); // Adds new appointment to the list
        writeToCSV(); // Saves the updated list of appointments to CSV
        std::cout << "Appointment added successfully!\n"; // Confirmation message
    }

    // Displays all scheduled appointments
    void showAppointments() const {
        if (scheduledAppointments.empty()) {
            std::cout << "No appointments found.\n";
            return;
        }
        std::cout << "Upcoming Appointments:\n";
        for (const auto& appointment : scheduledAppointments) {
            std::cout << "Client Name: " << appointment.clientName
                << ", Date: " << appointment.appointmentDate
                << ", Time: " << appointment.appointmentTime
                << ", Details: " << appointment.details << "\n";
        }
    }

    // Removes all appointments from the manager
    void removeAllAppointments() {
        scheduledAppointments.clear(); // Clears the appointment list
        std::ofstream file(storageFile, std::ios::trunc); // Clears the CSV file content
        std::cout << "All appointments have been removed.\n";
    }

    // Removes a specific appointment by client name
    void removeAppointment() {
        std::string clientName;
        std::cout << "Enter the client name of the appointment to remove: ";
        std::getline(std::cin, clientName); // Reads the name of the appointment to delete

        // Remove appointment from the list
        auto it = std::remove_if(scheduledAppointments.begin(), scheduledAppointments.end(),
            [&clientName](const Appointment& app) { return app.clientName == clientName; });

        if (it != scheduledAppointments.end()) {
            scheduledAppointments.erase(it, scheduledAppointments.end()); // Deletes matching appointments
            std::ofstream file(storageFile, std::ios::trunc); // Clears the CSV file
            writeToCSV(); // Resave remaining appointments to CSV
            std::cout << "Appointment removed successfully.\n"; // Confirmation message
        }
        else {
            std::cout << "No appointment found for client: " << clientName << "\n"; // Message if no matching appointment is found
        }
    }
};

// The main function serves as the user interface for the appointment manager
//In this program, we define two classes: Appointment, which stores details of an individual appointment (title and date),
// and AppointmentService, which manages a collection of appointments.
// The AppointmentService class provides two key methods:
// addAppointment to append a new appointment to the list and displayAppointments to output all scheduled appointments to the console. 
//In the main function, we instantiate the AppointmentService, add some sample appointments, 
// and display them, showcasing how the service can be effectively used for appointment management.

int main() {
    std::cout << "Welcome to the Appointment Scheduler\n William Colon\n\n"; // Welcome message
    AppointmentManager manager; // Creates an instance of the AppointmentManager
    int userChoice;
    do {
        // Display menu options for user
        std::cout << "1. Create Appointment\n2. Show Appointments\n3. Remove All Appointments\n4. Remove Appointment\n5. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> userChoice; // Reads user choice
        std::cin.ignore(); // Ignore the newline character left in the buffer

        switch (userChoice) {
        case 1:
            manager.createAppointment(); // Calls function to add an appointment
            break;
        case 2:
            manager.showAppointments(); // Calls function to display all appointments
            break;
        case 3:
            manager.removeAllAppointments(); // Calls function to clear all appointments
            break;
        case 4:
            manager.removeAppointment(); // Calls function to delete a specific appointment
            break;
        case 5:
            std::cout << "Thank you for using the appointment scheduler.\n"; // Exit message
            break;
        default:
            std::cout << "Invalid option. Please try again.\n"; // Message for invalid choice
        }
    } while (userChoice != 5); // Continue until user chooses to exit

    return 0; // Return statement indicating successful execution
}

///

// Address Optimization
//  - The CSV file operations for loading and saving appointments could use optimizations to reduce redundant file writes, especially in the `deleteAppointment` method.
//  - Instead of writing to the CSV far too frequently and in a truncating manner, consider batch processing and writing changes after a batch operation, or when the application is closed.
//  - Use a more efficient data structure if searching for appointments becomes a frequent operation, such as a map for fast lookups by name.
//  - Avoid file I/O in performance-critical paths by storing data temporarily in memory and writing to file less frequently.

// Time Complexity
//    - **addAppointment()**: This function performs several validation checks on the input. The time to execute is relatively constant due to the loops being dependent on user input. In the worst-case scenario, the function will keep prompting until valid input is received. Therefore, the average time complexity is O(n) where n is the number of attempts made to enter valid data.
//    - **displayAppointments()**: This function iterates through the vector of appointments. The time complexity is O(m), where m is the number of appointments in the vector, as it must print out each appointment detail.
//    - **clearAppointments()**: This function clears the vector and has a time complexity of O(1) since it just clears the vector without iterating through it.
//    - **saveToCSV()**: The function saves appointments to the CSV file, having a time complexity of O(m), where m is the number of appointments being saved.
//    - **loadFromCSV()**: This function loads appointments from the CSV file with a complexity of O(m) as it reads all the entries from the file.
//    - **Main Function**: The menu system is a simple do-while loop that runs until the user opts to exit. The complexity of this function is O(1) for each menu operation but could vary based on the options selected by the user.
//    This refined code structure is clear and efficient, with a focus on best practices for user input validation and displaying results accordingly.

// Efficiency of Algorithmic Logic
//  - The logic for input validation is efficient with regex, although it could be slightly optimized if date or time checks become increasingly complex by utilizing date parsing libraries.
//  - The use of a vector for storage provides a dynamic array feature, which is suitable for the current use case but may need to switch to a more complex data structure as requirements grow.
//  - While the current design is straightforward, further structural changes may enhance performance and usability if extended with more features like searching or sorting appointments. 

/// 