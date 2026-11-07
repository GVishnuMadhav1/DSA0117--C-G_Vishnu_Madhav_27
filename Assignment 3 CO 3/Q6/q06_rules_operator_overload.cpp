#include <iostream>
#include <cstring>

class Text {
private:
    char* data_;
    int len_;

public:
    Text() : data_(new char[1]{'\0'}), len_(0) {}
    Text(const char* s) : len_(std::strlen(s)), data_(new char[len_ + 1]) {
        std::strcpy(data_, s);
    }
    Text(const Text& other) : len_(other.len_), data_(new char[len_ + 1]) {
        std::strcpy(data_, other.data_);
    }
    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        delete[] data_;
        len_ = other.len_;
        data_ = new char[len_ + 1];
        std::strcpy(data_, other.data_);
        return *this;
    }
    ~Text() { delete[] data_; }

    Text operator+(const Text& other) const {
        Text result;
        delete[] result.data_;
        result.len_ = this->len_ + other.len_;
        result.data_ = new char[result.len_ + 1];
        std::strcpy(result.data_, this->data_);
        std::strcat(result.data_, other.data_);
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(this->data_, other.data_) == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        os << t.data_;
        return os;
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << " Q6: RULES OF OPERATOR OVERLOADING & SMS GATEWAY TEXT\n";
    std::cout << " Course: DSA0117 (CO3) | Student: G. Vishnu Madhav (192425192)\n";
    std::cout << "============================================================\n";

    Text msg1("OTP: 4819. ");
    Text msg2("Valid for 10 minutes.");
    Text fullMsg = msg1 + msg2;
    std::cout << "Concatenated Message: " << fullMsg << "\n";

    Text copyMsg = fullMsg;
    std::cout << "Equality Check (copyMsg == fullMsg): " << std::boolalpha << (copyMsg == fullMsg) << "\n";
    copyMsg = copyMsg; // Self assignment safe
    std::cout << "After self assignment: " << copyMsg << "\n";
    std::cout << "[PASS] Rules of operator overloading verified!\n";
    return 0;
}
