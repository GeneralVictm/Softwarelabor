#include <iostream>

using namespace std;

class String {
    private:
        // 'String' is represented internally as a plain C-style string.
        size_t size;
        char* str;
    public:
        String() {
            size = 0;
            str = new char[1];
            str[0] = '\0';
        }
        String(char c) {
            size = 1;
            str = new char[2];
            str[0] = c;
            str[1] = '\0';
        }
        String(const char* src) {
            size = 0;
            size_t i = 0;
            while(src[i]) {
                size++;
                i++;
            }
            str = new char[size+1];
            for(i = 0; i < size; i++) {
                str[i] = src[i];
            }
            str[size] = '\0';
        }
        String(const String& src) {
            size = src.getSize();
            str = new char[size+1];
            for(size_t i = 0; i < size; i++) {
                str[i] = src[i];
            }
            str[size] = '\0';
        }
        ~String() { delete[] str; }

        size_t getSize() const {
            return size;
        }

        String& operator=(const String& src) {
            if (this == &src)
                return *this;
            char* help = new char[src.getSize()+1];
            for(size_t i = 0; i < src.getSize(); i++) {
                help[i] = src[i];
            }
            help[src.getSize()] = '\0';
            delete[] str;
            str = help;
            size = src.getSize();
            return *this;
        }

        String& operator+=(const String& src) {
            if (this == &src)
                return *this;
            char* help = new char[size + src.getSize() + 1];
            for(size_t i = 0; i < size; i++) {
                help[i] = str[i];
            }
            for(size_t i = 0; i < src.getSize(); i++) {
                help[i+size] = src[i];
            }
            help[size + src.getSize()] = '\0';
            delete[] str;
            str = help;
            size += src.getSize();
            return *this;
        }

        char& operator[](size_t index) const {
            return str[index];
        }

        // make friend, so we can access private members
        friend ostream& operator<< (ostream &out, String &s);

};

ostream& operator<< (ostream &out, String &s) {
    for(size_t i=0; i<s.size; i++) {
        out << s.str[i];
    }

    return out;
}

int main() {
    String s1;
    String s2("Hello");
    String s3(s2);
    s1 += s2; s2 = s3;
    cout << s1 << endl;
    cout << s2.getSize() << endl;
    cout << s3 << endl;
    cout << s2[2] << endl;
    String s4("Hall�chen");
    s1 += s4;
    cout << s1 << endl;
}
