#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class SnapStore {
public:
    void displayMenu() {
        std::cout << "SpoinkStore Menu:" << std::endl;
        std::cout << "1. Install a Snap" << std::endl;
        std::cout << "2. Exit" << std::endl;
    }

    void installSnap(const std::string& snapName) {
        std::cout << "Installing snap: " << snapName << std::endl;

        // Use the snap command to install the snap
        std::string installCommand = "sudo snap install " + snapName;

        int result = std::system(installCommand.c_str());

        if (result == 0) {
            std::cout << "Installation completed successfully!" << std::endl;
        } else {
            std::cerr << "Installation failed. Check the snap name and try again." << std::endl;
        }
    }

    void run() {
        while (true) {
            displayMenu();
            int choice;
            std::cout << "Enter your choice (1-2): ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string snapName;
                    std::cout << "Enter the name of the snap to install: ";
                    std::cin >> snapName;
                    installSnap(snapName);
                    break;
                }
                case 2: {
                    std::cout << "Exiting SpoinkStore. Goodbye!" << std::endl;
                    return;
                }
                default:
                    std::cerr << "Invalid choice. Please enter a number between 1 and 2." << std::endl;
            }
        }
    }
};

int main() {
    SnapStore mySnapStore;
    mySnapStore.run();

    return 0;
}
