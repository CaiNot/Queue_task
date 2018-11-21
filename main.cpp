#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class STACK {
    int *const elems;    //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m) : elems(new int[m]), max(m) {        //初始化栈：最多存m个元素
        this->pos = 0;
    }

    STACK(const STACK &s) : elems(new int[s.size()]), max(s.size()) {            //用栈s拷贝初始化栈
        this->pos = (int) s;
        for (int i = 0; i < this->max; i++) {
            this->elems[i] = s[i];
        }
    }

    virtual int size() const {            //返回栈的最大元素个数max
        return this->max;
    }

    virtual operator int() const {            //返回栈的实际元素个数pos
        return this->pos;
    }

    virtual int operator[](int x) const {    //取下标x处的栈元素，第1个元素x=0
        return this->elems[x];
    }

    virtual STACK &operator<<(int e) {    //将e入栈,并返回栈
        this->elems[this->pos] = e;
        this->pos++;
        return *this;
    }

    virtual STACK &operator>>(int &e) {    //出栈到e,并返回栈
        this->pos--;
        e = this->elems[this->pos];
        return *this;
    }

    virtual STACK &operator=(const STACK &s) { //赋s给栈,并返回被赋值的栈
        int i = 0;
        int len = (int) s;
        delete[] this->elems;

        *(int **) &this->elems = new int[s.size()];
        *(int *) &this->max = s.size();
        this->pos = 0;

        for (i = 0; i < len; i++) {
            if (this->pos < s.size()) {
                this->elems[i] = s.elems[i];
                this->pos++;
            }
        }
        return *this;
    }

    virtual void print() const {        //打印栈
        for (int i = 0; i < this->pos; i++) {
            cout << this->elems[i] << "  ";
        }
    }

    virtual ~STACK() {                    //销毁栈
        if (elems)
            delete[] elems;
    }
};

class QUEUE : public STACK {
    STACK s2;
public:
    QUEUE(int m) : s2(m), STACK(m) {        //初始化队列：每个栈最多m个元素
    }

    QUEUE(const QUEUE &s) : s2(s.size()), STACK(s.size()) {        //用队列s拷贝初始化队列
        int e;
        int len_s = (int) s;
        for (int i = 0; i < len_s; i++) {
            (*(QUEUE *) &s) >> e;
            *this << e;
        }
    }

    virtual operator int() const {            //返回队列的实际元素个数
        return s2 + STACK::operator int();
    }

    virtual int full() const {               //返回队列是否已满，满返回1，否则返回0
        /**
         * s1已满且s2非空：满
        **/
        return STACK::operator int() == this->size() && (int) this->s2;
    }

    virtual int operator[](int x) const {   //取下标为x的元素，第1个元素下标为0
        if (x < (int) this->s2) {
            return this->s2[(int) this->s2 - x - 1];
        } else {
            return STACK::operator[](x - (int) this->s2);
        }
    }


    virtual QUEUE &operator<<(int e) {        //将e入队列,并返回队列
        if (STACK::operator int() >= STACK::size()) {
            int elemT;
            int len_s1 = STACK::operator int();
            for (int i = 0; i < len_s1; i++) {
                STACK::operator>>(elemT);
                s2 << elemT;
            }
        }
        STACK::operator<<(e);

        return *this;
    }

    virtual QUEUE &operator>>(int &e) {    //出队列到e,并返回队列
        if ((int) s2 == 0) {
            int elemT;
            int len_s1 = STACK::operator int();
            for (int i = 0; i < len_s1; i++) {
                STACK::operator>>(elemT);
                s2 << elemT;
            }
        }
        s2 >> e;
//        if (STACK::operator int() == 0) {
//            int elemT;
//            int len_s2 = (int) s2;
//            for (int i = 0; i < len_s2; i++) {
//                s2 >> elemT;
//                STACK::operator<<(elemT);
//            }
//        }
        return *this;
    }

    virtual QUEUE &operator=(const QUEUE &s) { //赋s给队列,并返回被赋值的队列
        int sSize = s.size();
//        int qSize = this->size();
        int sLen = (int) s;
        STACK::operator=(sSize);
        s2 = STACK(sSize);
        int elemT = 0;
        for (int i = 0; i < sLen; i++) {
            (*(QUEUE *) &s) >> elemT;
            *this << (elemT);
        }

        return *this;
    }

    virtual void print() const {          //打印队列
        int e = 0;
        if ((int) *this != 0) {
//            *((QUEUE *) this) >> e;
//            *((QUEUE *) this) << e;

            int len_s2 = (int) s2;
//            s2.print();
            for (int i = len_s2 - 1; i >= 0; i--) {
                cout << s2[i] << "  ";
            }
//            STACK::print();
            int len_s1 = STACK::operator int();
            for (int i = 0; i < len_s1; i++) {
                cout << STACK::operator[](i) << "  ";
            }
//            cout << e << "  ";
        }
    }

    virtual ~QUEUE() {                    //销毁队列
    }
};


bool isNum(char c) {
    if (c >= '0' && c <= '9')
        return true;
    else return false;
}

ofstream saveMessage("U201614751.txt");


class Problem {
    QUEUE menQ, womenQ;
public:
    Problem(int M, int F) : menQ(M), womenQ(F) {
        for (int i = 0; i < M; i++) {
            menQ << i + 1;
        }
        for (int i = 0; i < F; i++) {
            womenQ << i + 1;
        }
    }

    int whichSong(int m, int f) {
        int mQ, wQ;
        int song = 0;

        do {
            menQ >> mQ;
            menQ << mQ;

            womenQ >> wQ;
            womenQ << wQ;

            song++;
        } while (mQ != m || wQ != f);

        return song;
    }
};

int main(int argc, char *argv[]) {


    if (!saveMessage.is_open())
        return 1;

    if (argc > 1) {
        int i = 1;
        int e = 0;

        int model = 0;

        int j = 0;
        int popNum = 0;
        QUEUE *p = 0;
        QUEUE *c = 0;


        bool isEnd = false;
        for (; i < argc; i++) {
            if (isEnd) {
                delete p;
                return 0;
            }

            if (strcmp(argv[i], "-S") == 0) {
                int m = atoi(argv[i + 1]);
                i++;
                p = new QUEUE(m);
                cout << "S  " << m << "  ";
                saveMessage << "S  " << m << "  ";

            } else {

                if (strcmp(argv[i], "-I") == 0) {
                    model = 1;
                } else if (strcmp(argv[i], "-O") == 0) {
                    model = 2;
                } else if (strcmp(argv[i], "-C") == 0) {
                    model = 3;
                    i--;
                } else if (strcmp(argv[i], "-A") == 0) {
                    model = 4;
                } else if (strcmp(argv[i], "-N") == 0) {
                    model = 5;
                    i--;
                } else if (strcmp(argv[i], "-G") == 0) {
                    model = 6;
                } else {
                    i--;
                }
                i++;
                switch (model) {
                    case 1:
                        cout << "I  ";
                        saveMessage << "I  ";

                        for (; i < argc; i++) {
                            if (isNum(argv[i][0])) {
                                if (!p->full()) {
                                    e = atoi(argv[i]);
                                    *p << e;
                                } else {
                                    cout << "E";
                                    saveMessage << "E";

                                    isEnd = true;
                                    break;
                                }
                            } else {
                                i--;
                                break;
                            }
                        }
                        if (!isEnd)
                            p->print();
                        break;
                    case 2:
                        popNum = atoi(argv[i]);

                        cout << "O  ";
                        saveMessage << "O  ";

                        for (j = 0; j < popNum; j++) {
                            if ((int) *p < 1) {
                                cout << "E";
                                saveMessage << "E";

                                isEnd = true;
                                break;
                            }
                            *p >> e;
                        }
                        if (!isEnd) {
                            p->print();
                        }
                        break;
                    case 3:
                        c = new QUEUE(*p);
                        delete p;
                        p = c;

                        cout << "C  ";
                        saveMessage << "C  ";
                        p->print();
                        break;
                    case 4:
                        c = new QUEUE(atoi(argv[i]));
                        *c = *p;
                        delete p;
                        p = c;
                        cout << "A  ";
                        saveMessage << "A  ";
                        p->print();
                        break;
                    case 5:
                        cout << "N  " << (int) *p << "  ";
                        saveMessage << "N  " << (int) *p << "  ";
                        break;
                    case 6:
                        e = atoi(argv[i]);
                        cout << "G  ";
                        saveMessage << "G  ";
                        if (e < (int) *p && e >= 0) {
                            cout << (*p)[e] << "  ";
                            saveMessage << (*p)[e] << "  ";
                        } else {
                            cout << "E";
                            saveMessage << "E";
                            isEnd = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    } else {
        int M = 0, F = 0;

        cout << "Input male num: ";
        cin >> M;
        cout << "Input female num: ";
        cin >> F;

        if (M <= 0 || F <= 0) {
            cout << "Person can not be 0" << endl;
            return 1;
        }

        int m = 0, f = 0;

        cout << "Input male position: ";
        cin >> m;
        cout << "Input female position: ";
        cin >> f;

        Problem problem(M, F);
        int songs = 0;
        songs = problem.whichSong(m, f);

        cout << "Male " << m << " meet Female " << f << " at " << songs << " song" << endl;

    }
    saveMessage.close();
    return 0;
}