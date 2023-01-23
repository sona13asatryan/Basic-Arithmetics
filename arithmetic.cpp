#include <iostream>

const int mark = 1;
const int size_of = sizeof(int) * 8;
int add(int a, int b) {
    bool bit1 = 0, bit2 = 0, carry = 0;
    int res1 = 0, res2 = 0, res4 = 0;
    int sum = 0, result = 0;
    int i = 0;
    for (; i < size_of; ++i) {
        bit1 = mark & a;
        bit2 = mark & b;
        a = a >> 1;
        b = b >> 1;
        // I used my Turing Complete's Full Adder circuit.
        res1 = bit1 & bit2;
        res2 = bit1 ^ bit2;
        sum = res2 ^ carry;
        sum = sum << i;
        result = sum | result;
        res4 = res2 & carry;
        carry = res1 | res4;
    }
    return result;
}

int sub (int a, int b) {
    b = ~b + 1;
    return add(a,b);
}

int mul(int a, int b) {
    bool bit = 0;
    int result = 0;
    for (int i = 0; i < size_of; ++i) {
        bit = mark & a;
        if (bit) {
            result = add(b, result);
        }
        a = a >> 1;
        b = b << 1;
    }
    return result;
}

int divide (int a, int b) {
    int result = 0;
    if (!b) {
        std::cerr << "Can't divide by zero" << std::endl;
        abort();
    }
    if (!a) {
        return 0;
    }
    if (mul(a,b) > 0) {
        if (a > 0) {
            while (mul(result, b) <= a) {
                result = add(result, 1);
            }
        } else {
            while (mul(result, b) >= a) {
                result = add(result, 1);
            }
        }
        
        result = sub(result, 1);
    } else {
        if (a > 0) {
            while (mul(result, b) <= a) {
                result = sub(result, 1);
            }
        } else {
            while (mul(result, b) >= a) {
                result = sub(result, 1);
            }
        }
        result = add(result, 1);
    }
    return result;
}


int main() {
    int x, y;
    std::cin >> x >> y;
    int res = add(x,y);
    std::cout << "add(x, y) = " << res << std::endl;
    std:: cout << "x + y = " << x + y <<std::endl;
    res = mul(x, y);
    std::cout << "mul(x, y) = " << res << std::endl;
    std:: cout << "x * y = " << x * y <<std::endl;
    res = divide (x,y);
    std::cout << "divide(x, y) = " << res << std::endl;
    std:: cout << "x / y = " << x / y <<std::endl;
    return 0;
}
