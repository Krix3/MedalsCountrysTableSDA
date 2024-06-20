#include <iostream>
#include <string>
#include <utility>
#include <windows.h>

using namespace std;

class MedalsTable {
private:
    struct MedalEntry {
        string country;
        int gold;
        int silver;
        int bronze;

        MedalEntry() : country(""), gold(0), silver(0), bronze(0) {}
        MedalEntry(string c, int g, int s, int b) : country(move(c)), gold(g), silver(s), bronze(b) {}
    };

    MedalEntry* medals;
    int size;
    int capacity;

public:
    MedalsTable(int capacity = 10) : size(0), capacity(capacity)
    {
        medals = new MedalEntry[capacity];
    }

    ~MedalsTable()
    {
        delete[] medals;
    }

    MedalsTable(const MedalsTable& other) : size(other.size), capacity(other.capacity)
    {
        medals = new MedalEntry[capacity];
        for (int i = 0; i < size; ++i)
        {
            medals[i] = other.medals[i];
        }
    }

    MedalsTable& operator=(const MedalsTable& other)
    {
        if (this != &other)
        {
            delete[] medals;

            size = other.size;
            capacity = other.capacity;
            medals = new MedalEntry[capacity];
            for (int i = 0; i < size; ++i)
            {
                medals[i] = other.medals[i];
            }
        }
        return *this;
    }

    MedalsTable(MedalsTable&& other) noexcept : medals(nullptr), size(0), capacity(0)
    {
        swap(*this, other);
    }

    MedalsTable& operator=(MedalsTable&& other) noexcept {
        if (this != &other)
        {
            delete[] medals;
            swap(*this, other);
        }
        return *this;
    }

    void addEntry(const string& country, int gold, int silver, int bronze)
    {
        if (size == capacity)
        {
            resize();
        }
        medals[size++] = MedalEntry(country, gold, silver, bronze);
    }

    void printTable() const
    {
        for (int i = 0; i < size; ++i)
        {
            cout << medals[i].country << ": Золото " << medals[i].gold
                << ", Серебро " << medals[i].silver
                << ", Бронза " << medals[i].bronze << endl;
        }
    }

private:
    void resize()
    {
        capacity *= 2;
        MedalEntry* newMedals = new MedalEntry[capacity];
        for (int i = 0; i < size; ++i) {
            newMedals[i] = std::move(medals[i]);
        }
        delete[] medals;
        medals = newMedals;
    }

    friend void swap(MedalsTable& first, MedalsTable& second) noexcept {
        using std::swap;
        swap(first.medals, second.medals);
        swap(first.size, second.size);
        swap(first.capacity, second.capacity);
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    MedalsTable table(5);

    table.addEntry("США", 10, 5, 2);
    table.addEntry("Канада", 7, 8, 9);
    table.addEntry("Россия", 12, 4, 5);

    cout << "Таблица медалей:" << endl;
    table.printTable();

    MedalsTable copiedTable = table;
    cout << "\nСкопированная таблица медалей:" << endl;
    copiedTable.printTable();

    MedalsTable movedTable = move(table);
    cout << "\nПеремещенная таблица медалей:" << endl;
    movedTable.printTable();

    return 0;
}