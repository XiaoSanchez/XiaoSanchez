#include <iostream>
#include <vector>
using namespace std;
void print(const vector<int>& u) {
    for (int i = 0; i < u.size(); i++) {
        cout << u[i];
    }
    cout << endl;
}
vector<int> pad(const vector<int>& u, int n) {
    vector<int> padded(n - u.size(), 0);
    padded.insert(padded.end(), u.begin(), u.end());
    return padded;
}
vector<int> multiply(const vector<int>& u, const vector<int>& v) {
    int n = max(u.size(), v.size());
    vector<int> result(2 * n, 0);
    vector<int> paddedU = pad(u, n);
    vector<int> paddedV = pad(v, n);
    for (int i = n - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = n - 1; j >= 0; --j) {
            int product = paddedU[i] * paddedV[j] + result[i + j + 1] + carry;
            carry = product / 10;
            result[i + j + 1] = product % 10;
        }
        result[i] += carry;
    }
    while (result.size() > 1 && result.front() == 0) {
        result.erase(result.begin());
    }
    return result;
}
vector<int> add(const vector<int>& u, const vector<int>& v) {
    int n = max(u.size(), v.size());
    vector<int> result(n + 1, 0);
    vector<int> paddedU = pad(u, n);
    vector<int> paddedV = pad(v, n);
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int product = paddedU[i] + paddedV[i] + carry;
        carry = product / 10;
        result[i + 1] = product % 10;
    }
    result[0] = carry;
    while (result.size() > 1 && result.front() == 0) {
        result.erase(result.begin());
    }
    return result;
}
vector<int> prod(const vector<int>& u, const vector<int>& v) {
    vector<int> x, y, w, z;
    int n, m;
    n = max(u.size(), v.size());
    if (u.empty() || v.empty()) {
        x.push_back(0);
        return x;
    } else if (n % 2 != 0) {
        return multiply(u, v);
    } else {
        m = n / 2;
        x.assign(u.begin(), u.end() - m);
        y.assign(u.end() - m, u.end());
        w.assign(v.begin(), v.end() - m);
        z.assign(v.end() - m, v.end());
        vector<int> a = prod(x, w);
        vector<int> b = add(prod(x, z), prod(w, y));
        for (int i = 0; i < n; i++) {
            a.push_back(0);
            if (i % 2 == 0) b.push_back(0);
        }
        return add(add(a, b), prod(y, z));
    }
}
vector<int> prod3(const vector<int>& u, const vector<int>& v) {
    vector<int> x, y, z, r, s, t;
    int n, m;
    n = min(u.size(), v.size());
    if (u.empty() || v.empty()) {
        x.push_back(0);
        return x;
    } else if (n % 3 != 0) {
        return multiply(u, v);
    } else {
        // Create submatrices for A and B
        m = n / 3;
        x.assign(u.begin(), u.begin() + m);
        y.assign(u.begin() + m, u.end() - m);
        z.assign(u.end() - m, u.end());
        r.assign(v.begin(), v.begin() + m);
        s.assign(v.begin() + m, v.end() - m);
        t.assign(v.end() - m, v.end());
        vector<int> result;
        vector<int> x_r = prod3(x, r);
        vector<int> x_s = prod3(x, s);
        vector<int> x_t = prod3(x, t);

        vector<int> y_r = prod3(y, r);
        vector<int> y_s = prod3(y, s);
        vector<int> y_t = prod3(y, t);

        vector<int> z_r = prod3(z, r);
        vector<int> z_s = prod3(z, s);
        vector<int> z_t = prod3(z, t);

        vector<int> P1 = add(x_s, y_r);
        vector<int> P2 = add(add(x_t, y_s), z_r);
        vector<int> P3 = add(y_t, z_s);
        for (int i = 0; i < 4 * n; i++) {
            if (i % 3 == 0) x_r.push_back(0);
            if (i % 4 == 0) P1.push_back(0);
            if (i % 6 == 0) P2.push_back(0);
            if (i % 12 == 0) P3.push_back(0);
        }
        result = add(add(add(add(x_r, z_t), P1), P2), P3);
        return result;
    }
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    if (n % 6 != 0) {
        cout << "n must be a multiple of 6." << endl;
        return 1;
    }
    vector<int> A(n);
    vector<int> B(n);
    for (int i = 0; i < n; ++i) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }
    cout << "A = ";
    print(A);
    cout << "B = ";
    print(B);
    cout << "The large integer multiplication from the division of two smaller integers is\nA*B = ";
    vector<int> two = prod(A, B);
    print(two);
    cout << "The large integer multiplication from the division of three smaller integers is\nA*B = ";
    vector<int> three = prod3(A, B);
    print(three);
    if (two == three) {
        cout << "Correct" << endl;
    } else {
        cout << "Incorrect" << endl;
    }
    return 0;
}