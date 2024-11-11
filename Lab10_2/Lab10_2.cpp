#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Speciality { KN, IT, ME, FI, TN };
string specialityStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

enum Kurs { I = 1, II, III, IV, V, VI };

struct Student {
    string prizv;
    Kurs kurs;
    Speciality speciality;
    int markPhysics;
    int markMathematics;
    union {
        int markProgramming;
        int markNumericalMethods;
        int markPedagogy;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void VidminnikiSearch(Student* p, const int N);
void NeVidminnikiSearch(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality, const int kurs);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];
    int ispeciality;
    Speciality speciality;
    string prizv;
    int found;
    int menuItem;
    Kurs kurs;

    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - вивід прізвищ студентів," << endl;
        cout << " які мають лише оцінки 4 та 5" << endl;
        cout << " [4] - вивід прізвищ студентів," << endl;
        cout << " чий середній бал нижче 4:" << endl;
        cout << " [5] - фізичне впорядкування даних" << endl;
        cout << " [6] - індексне впорядкування та вивід даних" << endl;
        cout << " [7] - бінарний пошук студента за спеціальністю та прізвищем" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            VidminnikiSearch(p, N);
            break;
        case 4:
            NeVidminnikiSearch(p, N);
            break;
        case 5:
            Sort(p, N);
            break;
        case 6:
        {
            int* I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            delete[] I;
        }
        break;
        case 7:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> ispeciality;
            speciality = (Speciality)ispeciality;
            cout << " курс (1 - I, 2 - II, 3 - III, 4 - IV, 5 - V, 6 - VI): ";
            int kursNum;
            cin >> kursNum;
            kurs = (Kurs)kursNum;
            cin.get();
            cout << " прізвище: "; getline(cin, prizv);
            cout << endl;
            found = BinSearch(p, N, prizv, speciality, kurs);
            if (found != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N) {
    int speciality;
    int kurs;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс: "; cin >> kurs;
        p[i].kurs = (Kurs)kurs;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> speciality;
        p[i].speciality = (Speciality)speciality;
        cout << " Оцінка з фізики: "; cin >> p[i].markPhysics;
        cout << " Оцінка з математики: "; cin >> p[i].markMathematics;

        switch (p[i].speciality) {
        case KN:
            cout << " Оцінка з програмування: "; cin >> p[i].markProgramming;
            break;
        case IT:
            cout << " Оцінка з чисельних методів: "; cin >> p[i].markNumericalMethods;
            break;
        case ME:
        case FI:
        case TN:
            cout << " Оцінка з педагогіки: "; cin >> p[i].markPedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N) {
    cout << "=========================================================================================" << endl;
    cout << "| № | Прізвище      | Курс | Спеціальність            | Фізика | Математика |Інша оцінка|" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " "
            << "| " << setw(13) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(25) << left << specialityStr[p[i].speciality]
            << "| " << setw(6) << p[i].markPhysics << " "
            << "| " << setw(10) << p[i].markMathematics << " ";

        switch (p[i].speciality) {
        case KN:
            cout << "| " << setw(9) << p[i].markProgramming << " |" << endl;
            break;
        case IT:
            cout << "| " << setw(9) << p[i].markNumericalMethods << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << "| " << setw(9) << p[i].markPedagogy << " |" << endl;
            break;
        }
    }
    cout << "=========================================================================================" << endl;
    cout << endl;
}

void VidminnikiSearch(Student* p, const int N) {
    cout << "Прізвища студентів, які мають лише оцінки 4 та 5:" << endl;
    for (int i = 0; i < N; i++) {
        if (p[i].markPhysics > 3 && p[i].markMathematics > 3) {
            if (p[i].speciality == KN && p[i].markProgramming > 3)
                cout << p[i].prizv << endl;
            else if (p[i].speciality == IT && p[i].markNumericalMethods > 3)
                cout << p[i].prizv << endl;
            else if ((p[i].speciality == ME || p[i].speciality == FI || p[i].speciality == TN) && p[i].markPedagogy > 3)
                cout << p[i].prizv << endl;
        }
    }
}

void NeVidminnikiSearch(Student* p, const int N) {
    cout << "Прізвища студентів, чий середній бал нижче 4:" << endl;
    for (int i = 0; i < N; i++) {
        double avr = p[i].markPhysics + p[i].markMathematics;
        if (p[i].speciality == KN)
            avr += p[i].markProgramming;
        else if (p[i].speciality == IT)
            avr += p[i].markNumericalMethods;
        else if (p[i].speciality == ME || p[i].speciality == FI || p[i].speciality == TN)
            avr += p[i].markPedagogy;

        avr /= 3.0;

        if (avr < 4)
            cout << p[i].prizv << endl;
    }
}

void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].speciality > p[i1 + 1].speciality)
                ||
                (p[i1].speciality == p[i1 + 1].speciality &&
                    p[i1].prizv > p[i1 + 1].prizv)
                ||
                (p[i1].speciality == p[i1 + 1].speciality &&
                    p[i1].prizv == p[i1 + 1].prizv &&
                    p[i1].kurs > p[i1 + 1].kurs)) {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[I[i1]].speciality > p[I[i1 + 1]].speciality)
                ||
                (p[I[i1]].speciality == p[I[i1 + 1]].speciality &&
                    p[I[i1]].prizv > p[I[i1 + 1]].prizv)
                ||
                (p[I[i1]].speciality == p[I[i1 + 1]].speciality &&
                    p[I[i1]].prizv == p[I[i1 + 1]].prizv &&
                    p[I[i1]].kurs > p[I[i1 + 1]].kurs)) {
                tmp = I[i1];
                I[i1] = I[i1 + 1];
                I[i1 + 1] = tmp;
            }
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N) {
    cout << "=========================================================================================" << endl;
    cout << "| № | Прізвище      | Курс | Спеціальність            | Фізика | Математика |Інша оцінка|" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " "
            << "| " << setw(13) << left << p[I[i]].prizv
            << "| " << setw(4) << right << p[I[i]].kurs << " "
            << "| " << setw(25) << left << specialityStr[p[I[i]].speciality]
            << "| " << setw(6) << p[I[i]].markPhysics << " "
            << "| " << setw(10) << p[I[i]].markMathematics << " ";

        switch (p[I[i]].speciality) {
        case KN:
            cout << "| " << setw(9) << p[I[i]].markProgramming << " |" << endl;
            break;
        case IT:
            cout << "| " << setw(9) << p[I[i]].markNumericalMethods << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << "| " << setw(9) << p[I[i]].markPedagogy << " |" << endl;
            break;
        }
    }
    cout << "=========================================================================================" << endl;
    cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Speciality speciality, const int kurs) {
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].speciality == speciality && p[m].kurs == kurs)
            return m;
        if ((p[m].speciality < speciality) ||
            (p[m].speciality == speciality && p[m].prizv < prizv && p[m].kurs == kurs))
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
}
