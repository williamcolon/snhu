#include <unordered_map>
#include <string>

class Contact {
public:
    std::string getContactID();
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPhoneNumber(const std::string& phoneNumber);
    void setAddress(const std::string& address);
    bool operator==(const Contact& other) const;
};

class ContactService {
private:
    std::unordered_map<std::string, Contact> contacts;

public:
    ContactService() {}

    bool addContact(const Contact& contact) {
        bool contactAlready = false;
        for (const auto& contactPair : contacts) {
            if (contactPair.second == contact) {
                contactAlready = true;
                break;
            }
        }
        if (!contactAlready) {
            //contacts[contact.getContactID()] = contact;
            return true;
        }
        else {
            return false;
        }
    }

    bool deleteContact(const std::string& contactId) {
        return contacts.erase(contactId) > 0;
    }

    bool updateContactField(const std::string& contactId, const std::string& fieldName, const std::string& value) {
        auto it = contacts.find(contactId);
        if (it != contacts.end()) {
            Contact& contact = it->second;
            if (fieldName == "firstName" && !value.empty() && value.length() <= 10) {
                contact.setFirstName(value);
            }
            else if (fieldName == "lastName" && !value.empty() && value.length() <= 10) {
                contact.setLastName(value);
            }
            else if (fieldName == "phoneNumber" && value.length() == 10) {
                contact.setPhoneNumber(value);
            }
            else if (fieldName == "address" && !value.empty() && value.length() <= 30) {
                contact.setAddress(value);
            }
            return true;
        }
        return false;
    }

    Contact getContact(const std::string& contactId) {
        return contacts.at(contactId);
    }
};

