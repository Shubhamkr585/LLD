// #include <bits/stdc++.h>
// using namespace std;

// class Copy {
// private:
//     string name;
//     int* marks;
//     int size;

// public:
//     Copy(string name, int arr[], int n) {
//         this->name = name;
//         this->size = n;
//         this->marks = arr;  // shallow copy (just pointer assignment)
//     }

//     // Shallow copy constructor
//     // Copy(Copy &c) {
//     //     this->name = c.name;
//     //     this->size = c.size;
//     //     this->marks = c.marks;  // still pointing to same array
//     // }

//     // Deep copy constructor
// Copy(Copy &c) {
//     this->name = c.name;
//     this->size = c.size;
//     this->marks = new int[size];
//     for (int i = 0; i < size; i++) {
//         this->marks[i] = c.marks[i];
//     }
// }


//     void print() {
//         cout << "Name of the student: " << name << endl;
//         cout << "Marks: ";
//         for (int i = 0; i < size; i++) {
//             cout << marks[i] << " ";
//         }
//         cout << endl;
//     }

//     void setMarks() {
//         for (int i = 0; i < size; i++) {
//             marks[i]++; //since there is a shallow copy the effect should be reflected on both
//         }
//     }

//     bool operator==(Copy &c) {
//         return this->marks == c.marks;  // check if both point to same memory
//     }
// };

// int main() {
//     string name = "shubham";
//     int arr[] = {86, 90, 92};
//     int n = sizeof(arr)/sizeof(arr[0]);

//     Copy c1(name, arr, n);

//     Copy c2(c1); // shallow copy

//     c2.setMarks();
//     c1.print();
//     c2.print();

//     if (c1 == c2) {  //->c1.operator==(c2)
//         cout << "Shallow copy" << endl;
//     } else {
//         cout << "Deep copy" << endl;
//     }
// }


//  copy constructor where one object has the memory allocationon the head an the other on the stack


class Copy {
private:
    string name;
    int* marks;
    int size;
    bool ownsMemory;

public:
    // Constructor (stack array, not owned)
    Copy(string name, int arr[], int n) {
        this->name = name;
        this->size = n;
        this->marks = arr;
        this->ownsMemory = false;  // not owner
    }

    // Deep copy constructor (heap allocation, owned)
    Copy(const Copy &c) {
        this->name = c.name;
        this->size = c.size;
        this->marks = new int[size];
        for (int i = 0; i < size; i++) this->marks[i] = c.marks[i];
        this->ownsMemory = true;   // owns this memory
    }

    // Destructor deletes only if owned
    ~Copy() {
        if (ownsMemory) delete[] marks;
    }
};


// copy constructor/destructor when there is only deep copy

// #include <bits/stdc++.h>
// using namespace std;

// class Copy {
// private:
//     string name;
//     int* marks;
//     int size;

// public:
//     // Always allocate memory dynamically
//     Copy(string name, int arr[], int n) {
//         this->name = name;
//         this->size = n;
//         this->marks = new int[size];
//         for (int i = 0; i < size; i++) {
//             this->marks[i] = arr[i];
//         }
//     }

//     // Deep copy constructor
//     Copy(const Copy &c) {
//         this->name = c.name;
//         this->size = c.size;
//         this->marks = new int[size];
//         for (int i = 0; i < size; i++) {
//             this->marks[i] = c.marks[i];
//         }
//     }

//     // Destructor (safe)
//     ~Copy() {
//         delete[] marks;
//     }

//     void print() {
//         cout << "Name: " << name << " Marks: ";
//         for (int i = 0; i < size; i++) cout << marks[i] << " ";
//         cout << endl;
//     }
// };

