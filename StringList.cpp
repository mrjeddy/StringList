#include <iostream>
#include <string>

using namespace std;

class StringList
{
public:
    int arrSize = 0;
    string* inputArray;
    string* tempArr;

    StringList(int arrl, string* arr) {
        inputArray = new string[arrl];
        tempArr = new string[arrl];
        arrSize = arrl;
        for (int i = 0; i < arrl; i++)
        {
            inputArray[i] = arr[i];
        }
    }
    StringList(int arrl, const char* arr[]) {
        inputArray = new string[arrl];
        arrSize = arrl;
        for (int i{}; i < arrl; i++)
        {
            inputArray[i] = arr[i];
        }
    }
    StringList(const StringList& sl) noexcept {
        inputArray = sl.inputArray;
        arrSize =sl.arrSize;
        tempArr = new string[sl.arrSize];
    }
    StringList(StringList&& sl) noexcept{
        swap(inputArray, sl.inputArray);
        swap(arrSize, sl.arrSize);
        tempArr = new string[sl.arrSize];
    }
    StringList operator=(const StringList& sl) {
        inputArray = sl.inputArray;
        arrSize = sl.arrSize;
        return *this;
    }
    StringList operator+=(const char* ch) {
        int arrLenght = arrSize + 1;
        tempArr = new string[arrLenght];
        for (int i = 0; i < arrSize; i++) {
            tempArr[i] = inputArray[i];
        }
        tempArr[arrSize] = ch;
        inputArray = tempArr;
        arrSize++;
        return *this;
    }
    StringList operator+=(string st) {
        int arrLenght = arrSize + 1;
        tempArr = new string[arrLenght];
        for (int i = 0; i < arrSize; i++) {
            tempArr[i] = inputArray[i];
        }
        tempArr[arrSize] = st;
        inputArray = tempArr;
        arrSize++;
        return *this;
    }
    void getInputed() {
        cout << endl << "===========" << endl;
        for (int i = 0; i < arrSize; i++)
        {
            cout << inputArray[i] << endl;
        }
        cout << "===========" << endl << endl;
    }
    string lowerCase(string s) {
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        return s;
    }
    void reorder(string* a, int first, int last) {
        int i = first, j = last;
        string tmp, x = lowerCase(a[(first + last) / 2]);
        do {
            while (lowerCase(a[i]) > x)
                i++;
            while (lowerCase(a[j]) < x)
                j--;
            if (i <= j)
            {
                if (i < j)
                {
                    swap(a[i], a[j]);
                }
                i++;
                j--;
            }
        } while (i <= j);
        if (i < last)
            reorder(a, i, last);
        if (first < j)
            reorder(a, first, j);    
    }
    void sortList() {
        reorder(inputArray, 0, arrSize-1);
    }
};


StringList operator+(const StringList& sl1, const StringList& sl2) {
    int arrlen = sl1.arrSize + sl2.arrSize;
    string* arr = new string[arrlen];
    copy(sl1.inputArray, sl1.inputArray + sl1.arrSize, arr);
    copy(sl2.inputArray, sl2.inputArray + sl2.arrSize, arr + sl1.arrSize);
    StringList sl = StringList(arrlen, arr);
    return sl;
}

string stringList[] = { "Marinate", "the", "nether", "rod", "In", "the", "squish", "mitten" };
const char* charList[] = { "somebody", "once", "told", "me", "the", "world", "is", "gonna", "roll", "me" };

int main()
{
    int arrLenght = sizeof(stringList) / sizeof(stringList[0]);
    int chLenght = sizeof(charList) / sizeof(charList[0]);

    StringList sl = StringList(arrLenght, stringList);
    StringList mysl(sl);
    StringList chsl = StringList(chLenght, charList);
    mysl = chsl;
    mysl += "foxtrot";
    mysl += "uniform";
    string word = "charlie";
    mysl += word;
    mysl += "kilo";
    StringList moved(move(mysl));
    mysl = sl + moved;
    mysl.sortList();
    mysl.getInputed();



    string line;
    getline(cin, line);
    return 0;
}
