#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
// all of your function definitions should be in this file now

template <typename T>
class Matrix {
public:
    Matrix(std::size_t N) : size(N), data(N, std::vector<T>(N)) {}

    Matrix(std::vector<std::vector<T>> nums) : data(nums), size(nums.size()) {
        for (const auto& row : nums) {
            if (row.size() != size) {
                throw std::invalid_argument("Matrix must be square.");
            }
        }
    }

    Matrix operator+(const Matrix &rhs) const {
        if (size != rhs.size) {
            throw std::invalid_argument("Matrices must be of the same size for addition.");
        }
        Matrix result(size);
        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t j = 0; j < size; ++j) {
                result.data[i][j] = data[i][j] + rhs.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &rhs) const {
        if (size != rhs.size) {
            throw std::invalid_argument("Matrices must be of the same size for multiplication.");
        }
        Matrix result(size);
        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t j = 0; j < size; ++j) {
                T sum = 0;
                for (std::size_t k = 0; k < size; ++k) {
                    sum += data[i][k] * rhs.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    void set_value(std::size_t i, std::size_t j, T n) {
        if (i >= size || j >= size) {
            throw std::out_of_range("Indices out of bounds.");
        }
        data[i][j] = n;
    }

    T get_value(std::size_t i, std::size_t j) const {
        if (i >= size || j >= size) {
            throw std::out_of_range("Indices out of bounds.");
        }
        return data[i][j];
    }

    std::size_t get_size() const {
        return size;
    }

    T sum_diagonal_major() const {
        T sum = 0;
        for (std::size_t i = 0; i < size; ++i) {
            sum += data[i][i];
        }
        return sum;
    }

    T sum_diagonal_minor() const {
        T sum = 0;
        for (std::size_t i = 0; i < size; ++i) {
            sum += data[i][size - 1 - i];
        }
        return sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2) {
        if (r1 >= size || r2 >= size) {
            throw std::out_of_range("Row index out of bounds.");
        }
        std::swap(data[r1], data[r2]);
    }

    void swap_cols(std::size_t c1, std::size_t c2) {
        if (c1 >= size || c2 >= size) {
            throw std::out_of_range("Column index out of bounds.");
        }
        for (std::size_t i = 0; i < size; ++i) {
            std::swap(data[i][c1], data[i][c2]);
        }
    }

    void print_matrix() const {
        for (const auto& row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
}

private:
    std::vector<std::vector<T>> data;
    std::size_t size;
};

#endif // __MATRIX_HPP__
