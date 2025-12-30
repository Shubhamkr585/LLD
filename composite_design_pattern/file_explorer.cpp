#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// 1. The Component Interface
// ==========================================
class FileSystemItem {
public:
    virtual string getName() = 0;
    virtual int getSize() = 0;
    virtual void showDetails() = 0;
    virtual ~FileSystemItem() {}
};

// ==========================================
// 2. The Leaf (File)
// ==========================================
class File : public FileSystemItem {
private:
    string name;
    int size;

public:
    File(string n, int s) : name(n), size(s) {}

    string getName() override {
        return name;
    }

    int getSize() override {
        return size;
    }

    void showDetails() override {
        cout << " File: " << name << " (" << size << " KB)" << endl;
    }
};

// ==========================================
// 3. The Composite (Folder)
// ==========================================
class Folder : public FileSystemItem {
private:
    string name;
    vector<FileSystemItem*> children; // Holds Files OR other Folders!

public:
    Folder(string n) : name(n) {}

    ~Folder() {
        cout << "Destroying Folder: " << name << endl;
        for (FileSystemItem* item : children) {
            delete item;
        }
    }

    string getName() override {
        return name;
    }

    // Method to add items (Files or Subfolders)
    void add(FileSystemItem* item) {
        children.push_back(item);
    }

    // Recursive Logic: Sum of children
    int getSize() override {
        int totalSize = 0;
        for (FileSystemItem* item : children) {
            totalSize += item->getSize();
        }
        return totalSize;
    }

    // Recursive Logic: Show self, then children
    void showDetails() override {
        cout << "Folder: " << name << endl;
        for (FileSystemItem* item : children) {
            item->showDetails();
        }
    }

    /**
     * @brief Simulates a 'cd' (change directory) command.
     * Searches for a subfolder with the given name.
     * @param folderName The name of the folder to change into.
     * @return A pointer to the Folder if found, otherwise nullptr.
     */
    Folder* cd(const string& folderName) {
        for (FileSystemItem* item : children) {
            Folder* folder = dynamic_cast<Folder*>(item);
            if (folder && folder->getName() == folderName) {
                cout << "\n> Changing into directory: " << folderName << endl;
                return folder;
            }
        }
        cout << "\n> Folder '" << folderName << "' not found in '" << this->name << "'." << endl;
        return nullptr;
    }
};

// ==========================================
// 4. The Client
// ==========================================
int main() {
    // The root folder will manage the memory of all its children.
    Folder* root = new Folder("My Documents");

    // 1. Create simple files (Leaves) and add them to root
    root->add(new File("Resume.pdf", 200));

    // 2. Create a subfolder and add files to it
    Folder* subFolder = new Folder("Personal");
    subFolder->add(new File("Photo.png", 500));
    subFolder->add(new File("ToDo.txt", 10));

    // 3. Add subfolder to root
    root->add(subFolder);

    // 4. Client treats Root exactly like a File!
    cout << "--- File System Details ---" << endl;
    root->showDetails();

    cout << "\nTotal Size of root: " << root->getSize() << " KB" << endl;


    // 5. Demonstrate "cd"
    Folder* current_dir = root;
    current_dir = current_dir->cd("Personal");

    if (current_dir) {
        cout << "--- Contents of 'Personal' ---" << endl;
        current_dir->showDetails();
        cout << "Total Size of 'Personal': " << current_dir->getSize() << " KB" << endl;
    }
    
    // Try to cd into a non-existent folder
    current_dir = root->cd("Work");


    // 6. Cleanup. Deleting the root folder will trigger the recursive deletion
    // of all its children (files and subfolders) because of the destructor.
    cout << "\n--- Deleting root folder ---" << endl;
    delete root;

    return 0;
}