#include "matrix.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

template <typename T>
void handleMenu(Matrix<T>& mat1, Matrix<T>& mat2);

void printMenu() {
    std::cout << "Choose an Option" << std::endl;
    std::cout << "1) Read Values from File" << std::endl;
    std::cout << "2) Add Two Matrices and Display Result" << std::endl;
    std::cout << "3) Multiply Two Matrices and Display Result" << std::endl;
    std::cout << "4) Get the Sum of Matrix Diagonal Elements" << std::endl;
    std::cout << "5) Swap Matrix Rows and Display the Result" << std::endl;
    std::cout << "6) Swap Matrix Columns and Display the Result" << std::endl;
    std::cout << "7) Update Matrix Element and Display the Result" << std::endl;
    std::cout << "8) End Program" << std::endl;
}

template <typename T>
void readMatricesFromFile(const std::string& fileName, Matrix<T>& mat1, Matrix<T>& mat2) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Error opening file.");
    }
    size_t n;
    mat1 = Matrix<T>(n);
    mat2 = Matrix<T>(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            T val;
            file >> val;
            mat1.set_value(i, j, val);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            T val;
            file >> val;
            mat2.set_value(i, j, val);
        }
    }
    std::cout << "Matrix 1:\n";
    mat1.print_matrix();
    std::cout << "Matrix 2:\n";
    mat2.print_matrix();
}

int main() {
    std::string fileName;
    std::cout << "Enter initial file name: ";
    std::cin >> fileName;
    std::ifstream testFile(fileName);
    if (!testFile) throw std::runtime_error("File not found.");
    int type_flag;
    size_t n;
    testFile >> n >> type_flag;
    testFile.close();
    if (type_flag == 0) {
        Matrix<int> mat1(1), mat2(1);
        readMatricesFromFile(fileName, mat1, mat2);
        handleMenu(mat1, mat2);
    } else {
        Matrix<double> mat1(1), mat2(1);
        readMatricesFromFile(fileName, mat1, mat2);
        handleMenu(mat1, mat2);
    }
    return 0;
}

template <typename T>
void handleMenu(Matrix<T>& mat1, Matrix<T>& mat2) {
    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;

        if (choice == 1) {
            std::string newFile;
            std::cout << "Enter new file name: ";
            std::cin >> newFile;
            readMatricesFromFile(newFile, mat1, mat2);
        } else if (choice == 2) {
            Matrix<T> result = mat1 + mat2;
            std::cout << "Sum:\n";
            result.print_matrix();
        } else if (choice == 3) {
            Matrix<T> result = mat1 * mat2;
            std::cout << "Product:\n";
            result.print_matrix();
        } else if (choice == 4) {
            int matChoice;
            std::cout << "Select matrix (1 or 2): ";
            std::cin >> matChoice;
            if (matChoice == 1) {
                std::cout << "Main diagonal sum: " << mat1.sum_diagonal_major() << "\n";
                std::cout << "Secondary diagonal sum: " << mat1.sum_diagonal_minor() << "\n";
            } else if (matChoice == 2) {
                std::cout << "Main diagonal sum: " << mat2.sum_diagonal_major() << "\n";
                std::cout << "Secondary diagonal sum: " << mat2.sum_diagonal_minor() << "\n";
            } else {
                std::cout << "Invalid matrix choice" << std::endl;
            }
        } else if (choice == 5) {
            int matChoice;
            size_t r1, r2;
            std::cout << "Select matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter two row indices: ";
            std::cin >> r1 >> r2;
            if (r1 == r2) {
                std::cout << "Cannot swap row with itself" << std::endl;
            }else if (matChoice == 1) {
                mat1.swap_rows(r1, r2);
                mat1.print_matrix();
            } else if (matChoice == 2) {
                mat2.swap_rows(r1, r2);
                mat2.print_matrix();
            } else {
                std::cout << "Invalid matrix choice" << std::endl;
            }
        } else if (choice == 6) {
            int matChoice;
            size_t c1, c2;
            std::cout << "Select matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter two column indices: ";
            std::cin >> c1 >> c2;
            if (c1 == c2){
                std::cout << "Cannot swap column with itself" << std::endl;
            }else if (matChoice == 1) {
                mat1.swap_cols(c1, c2);
                mat1.print_matrix();
            } else if (matChoice == 2) {
                mat2.swap_cols(c1, c2);
                mat2.print_matrix();
            } else {
                std::cout << "Invalid matrix choice" << std::endl;
            }

        } else if (choice == 7) {
            int matChoice;
            size_t row, col;
            T value;
            std::cout << "Select matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter row, column, and new value: ";
            std::cin >> row >> col >> value;
            if (matChoice == 1) {
                mat1.set_value(row, col, value);
                mat1.print_matrix();
            } else if (matChoice == 2) {
                mat2.set_value(row, col, value);
                mat2.print_matrix();
            } else {
                std::cout << "Invalid matrix choice" << std::endl;
            }
        } else if (choice == 8) {
            break;
        } else {
            std::cout << "Invalid option" << std::endl;
        }
    }
}