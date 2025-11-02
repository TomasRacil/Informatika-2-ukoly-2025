#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> data;

public:
    // Constructor
    Matrix(int r, int c) : rows(0), cols(0) {
        if (r > 0 && c > 0) {
            rows = r;
            cols = c;
            data.resize(rows, std::vector<int>(cols, 0));
        }
    }

    // Copy constructor
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data; // deep copy
    }

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Accessors
    int getValue(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols)
            throw std::out_of_range("Index out of range");
        return data[r][c];
    }

    void setValue(int r, int c, int value) {
        if (r < 0 || r >= rows || c < 0 || c >= cols)
            throw std::out_of_range("Index out of range");
        data[r][c] = value;
    }

    // Addition
    Matrix add(const Matrix& other) const {
        if (rows <= 0 || cols <= 0 || rows != other.rows || cols != other.cols)
            return Matrix(0, 0);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Subtraction
    Matrix subtract(const Matrix& other) const {
        if (rows <= 0 || cols <= 0 || rows != other.rows || cols != other.cols)
            return Matrix(0, 0);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    // Transpose
    Matrix transpose() const {
        if (rows <= 0 || cols <= 0) return Matrix(0, 0);
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[j][i] = data[i][j];
        return result;
    }

    // Multiplication
    Matrix multiply(const Matrix& other) const {
        if (rows <= 0 || cols <= 0 || other.rows <= 0 || other.cols <= 0 || cols != other.rows)
            return Matrix(0, 0);
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j) {
                int sum = 0;
                for (int k = 0; k < cols; ++k)
                    sum += data[i][k] * other.data[k][j];
                result.data[i][j] = sum;
            }
        return result;
    }
};

#ifndef __TEST__
int main() {
    Matrix A(2, 2);
    A.setValue(0, 0, 1); A.setValue(0, 1, 2);
    A.setValue(1, 0, 3); A.setValue(1, 1, 4);

    Matrix B(2, 2);
    B.setValue(0, 0, 5); B.setValue(0, 1, 6);
    B.setValue(1, 0, 7); B.setValue(1, 1, 8);

    Matrix C = A.add(B);
    for(int i = 0; i < C.getRows(); i++) {
        for(int j = 0; j < C.getCols(); j++)
            std::cout << C.getValue(i, j) << " ";
        std::cout << "\n";
    }

    return 0;
}
#endif
