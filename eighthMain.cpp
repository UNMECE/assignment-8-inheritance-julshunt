// Name: Julian Hunter
// Class: C++ Intermediate Programming & Problem-Solving
// Assignment 8: Inheritance
// FileName: "mainEight.cpp"

#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
using namespace std;

const double epsillonZero = (8.854*(10^(-12))); // Permittivity of free space in an electric Field
const double muZero = (4 * M_PI * (10^(-7))); // Permeability of free space in a magnetic field 

class Field {
protected:
    double *value;

public:
    // Default constructor
    Field() {
        value = new double[3]{0.0, 0.0, 0.0};
    }
    // Parameterized constructor
    Field(double v1, double v2, double v3) {
        value = new double[3]{v1, v2, v3};
    }
    // Destructor
    virtual ~Field() {
        delete[] value;
    }
    // Print magnitude
    virtual void printMagnitude() const {
        cout << "Field Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")" << endl;
    }
    // Overloading output operator
    friend ostream &operator<<(ostream &os, const Field &f) {
        os << "(" << f.value[0] << ", " << f.value[1] << ", " << f.value[2] << ")";
        return os;
    }
};

class electricField : public Field {
private:
    double calculatedElectricField;

public:
    // Constructors
    electricField() : Field(), calculatedElectricField(0.0) {}
    electricField(double v1, double v2, double v3) : Field(v1, v2, v3), calculatedElectricField(0.0) {}

    // Calculate electric field
    void calculateElectricField(double Q, double r) {
        calculatedElectricField = Q / (4 * M_PI * r * r * epsillonZero);
    }
    // Output calculated Electric Field
    void printCalculatedElectricField() const {
        cout << "The calculated electric field is " << calculatedElectricField << " (Newtons per Coulomb)" << endl;
    }
    // Overloading addition operator
    electricField operator+(const electricField &ef) const {
        return electricField(value[0] + ef.value[0], value[1] + ef.value[1], value[2] + ef.value[2]);
    }
    // Copy constructor
    electricField(const electricField &ef) : Field(ef.value[0], ef.value[1], ef.value[2]), calculatedElectricField(ef.calculatedElectricField) {}
};

class magneticField : public Field {
private:
    double calculatedMagneticField;

public:
    // Constructors
    magneticField() : Field(), calculatedMagneticField(0.0) {}
    magneticField(double v1, double v2, double v3) : Field(v1, v2, v3), calculatedMagneticField(0.0) {}

    // Calculate magnetic field
    void calculateMagneticField(double I, double r) {
        calculatedMagneticField = I / (2 * M_PI * r * muZero);
    }
    // Output calculated Magnetic Field
    void printCalculatedMagneticField() const {
        cout << "The calculated magnetic field is " << calculatedMagneticField << " Teslas" << endl;
    }
    // Overloading addition operator
    magneticField operator+(const magneticField &mf) const {
        return magneticField(value[0] + mf.value[0], value[1] + mf.value[1], value[2] + mf.value[2]);
    }
    // Copy constructor
    magneticField(const magneticField &mf) : Field(mf.value[0], mf.value[1], mf.value[2]), calculatedMagneticField(mf.calculatedMagneticField) {}
};

// Driver code
int main() {
    electricField eField(0.0, 1e5, 1e3);
    magneticField mField(1.0, 0.0, 0.5);

    // Print components
    cout << "Electric ";
    eField.printMagnitude();
    cout << "Magnetic ";
    mField.printMagnitude();

    // Calculate electric and magnetic fields
    eField.calculateElectricField(1e-6, 0.1); // Q = 1e-6 C, r = 0.1 m
    mField.calculateMagneticField(10, 0.1);   // I = 10 A, r = 0.1 m

    // Print calculated fields
    eField.printCalculatedElectricField();
    mField.printCalculatedMagneticField();

    // Demonstrate operator overloading for +
    electricField eField2(0.0, 2e5, 1e3);
    electricField eFieldSum = eField + eField2;
    cout << "Summed Electric Field: " << eFieldSum << endl;

    magneticField mField2(0.5, 0.0, 1.0);
    magneticField mFieldSum = mField + mField2;
    cout << "Summed Magnetic Field: " << mFieldSum << endl;

    return 0;
}
