#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
void print(const vector<vector<int> >& A) {
    int n = to_string(*max_element(A[0].begin(), A[0].end())).length();
    cout << setiosflags(ios::right) << setiosflags(ios::fixed);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << setw(n) << A[i][j] << " ";
        }
        cout << endl;
    }
}
// Generate random integers in the range [0, ⌊sqrt(MAXIMUM INTEGER / n))⌋)
int random(int n) {
    return int (sqrt(rand() / n));
}
// Multiply two matrices using the standard algorithm
vector<vector<int> > multiplyMatrices(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int n = A.size();
    vector<vector<int> > result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
vector<vector<int> > add(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int n = A.size();
    vector<vector<int> > result(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}
vector<vector<int> > subtract(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int n = A.size();
    vector<vector<int> > result(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}
// Strassen Matrix Multiplication
vector<vector<int> > strassenMultiply(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int n = A.size();
    // Base case: If the matrix size is 1x1, perform regular multiplication
    if (n == 1) {
        vector<vector<int> > result(1, vector<int>(1, A[0][0] * B[0][0]));
        return result;
    }
    // Create submatrices for A and B
    int m = n / 2;
    vector<vector<int> > A11(m, vector<int>(m));
    vector<vector<int> > A12(m, vector<int>(m));
    vector<vector<int> > A21(m, vector<int>(m));
    vector<vector<int> > A22(m, vector<int>(m));
    vector<vector<int> > B11(m, vector<int>(m));
    vector<vector<int> > B12(m, vector<int>(m));
    vector<vector<int> > B21(m, vector<int>(m));
    vector<vector<int> > B22(m, vector<int>(m));
    // split matrix A, B into four quadrants
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            B11[i][j] = B[i][j];
            A12[i][j] = A[i][j + m];
            B12[i][j] = B[i][j + m];
            A21[i][j] = A[i + m][j];
            B21[i][j] = B[i + m][j];
            A22[i][j] = A[i + m][j + m];
            B22[i][j] = B[i + m][j + m];
        }
    }
    // Compute seven products using Strassen's method
    vector<vector<int> > P1 = strassenMultiply(A11, subtract(B12, B22));
    vector<vector<int> > P2 = strassenMultiply(add(A11, A12), B22);
    vector<vector<int> > P3 = strassenMultiply(add(A21, A22), B11);
    vector<vector<int> > P4 = strassenMultiply(A22, subtract(B21, B11));
    vector<vector<int> > P5 = strassenMultiply(add(A11, A22), add(B11, B22));
    vector<vector<int> > P6 = strassenMultiply(subtract(A12, A22), add(B21, B22));
    vector<vector<int> > P7 = strassenMultiply(subtract(A11, A21), add(B11, B12));
    // Compute the four quadrants of the result matrix
    vector<vector<int> > C11 = subtract(add(add(P5, P4), P6), P2);
    vector<vector<int> > C12 = add(P1, P2);
    vector<vector<int> > C21 = add(P3, P4);
    vector<vector<int> > C22 = subtract(subtract(add(P5, P1), P3), P7);
    // Combine the four quadrants to form the result matrix
    vector<vector<int> > result(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = C11[i][j];
            result[i][j + m] = C12[i][j];
            result[i + m][j] = C21[i][j];
            result[i + m][j + m] = C22[i][j];
        }
    }
    return result;
}
// Check if two matrices are equal
bool compare(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <matrix_size>" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    if ((n & (n - 1)) != 0 || n < 1 || n > 1024) {
        cout << "n must be a power of 2 between 1 and 1024." << endl;
        return 1;
    }
    // Generate random matrices A and B
    vector<vector<int> > A(n, vector<int>(n));
    vector<vector<int> > B(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = random(n);
            B[i][j] = random(n);
        }
    }
    cout << "A =" << endl;
    print(A);
    cout << "B =" << endl;
    print(B);
    cout << "The standard matrix multiplication A*B =" << endl;
    vector<vector<int> > standard = multiplyMatrices(A, B);
    print(standard);
    cout << "The Strassen's multiplication A*B =" << endl;
    vector<vector<int> > strassen = strassenMultiply(A, B);
    print(strassen);
    if (compare(standard, strassen)) {
        cout << "Correct" << endl;
    } else {
        cout << "Incorrect" << endl;
    }
    return 0;
}