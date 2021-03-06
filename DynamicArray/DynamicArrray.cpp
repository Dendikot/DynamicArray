#include <iostream>
#include <iterator>

template<class Vector>
class ListIterator
{
public:
    using ValueType = typename Vector::ValueType;
public:
    ListIterator(ValueType* ptr) :m_ptr(ptr) {}

    ListIterator& operator++() { m_ptr++; return *this; }

    ListIterator operator++(int) { ListIterator tmp = *this; ++(*this); return tmp; }

    ListIterator& operator--() { m_ptr--; return *this; }
    ListIterator operator--(int) { ListIterator tmp = *this; --(*this); return tmp; }

    ListIterator operator+(int value) { m_ptr += value; return *this; }

    int distance(ListIterator& other) { return ((int)m_ptr - (int)other.m_ptr)/sizeof(ValueType);}

    ValueType& operator*() { return *m_ptr; }
    Vector& operator->() { return m_ptr; }

    bool operator==(const ListIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ListIterator& other) const { return !(*this == other); }
private:
    ValueType* m_ptr;
};

template <class T, size_t S = 2>
class ListInt
{
public:
    using ValueType = T;
    using Iterator = ListIterator<ListInt<T, S>>;
private:
    int size;
    int filledCells = 0;
    T* arrPoint = nullptr;

    void realloc(size_t newSize) {
        T* newPointer = new T[newSize];
        if (newSize < filledCells)
        {
            filledCells = newSize;
        }

        for (size_t i = 0; i < filledCells; i++)
        {
            newPointer[i] = arrPoint[i];
        }

        delete[] arrPoint;
        arrPoint = newPointer;
        size = newSize;
    }

public:
    ListInt() {
        realloc(S);
    }

    int Length() {
        return filledCells;
    }

    int Size() {
        return size;
    }

    T& operator[](size_t index) {

        if (index < size)
        {
            return arrPoint[index];
        }
        else
        {
            return NULL;
        }
    }

    void pushBack(int value) {
        if (filledCells >= size)
        {
            realloc(size * 2);
        } 
        arrPoint[filledCells] = value;
        filledCells++;
    }

    void popBack() {
        if (filledCells < 0) return;
        filledCells--;
    }

    void flush(size_t initSize = 3) {
        size = initSize;
        filledCells = -1;
        // if size != 0
        delete[] arrPoint;
        arrPoint = new int[initSize];
    }

    Iterator begin()
    {
        return Iterator(arrPoint);
    }

    Iterator end()
    {
        return Iterator(arrPoint + filledCells);
    }
    
    //
    void insert(Iterator place, ValueType item, size_t amount = 1) {
        int distance = end().distance(place);
        if (distance > filledCells) return;

        ValueType* tempArr = new ValueType[distance];

        int indexTemp = 0;
        int indexFill = filledCells - distance;
        for (int i = indexFill; i < filledCells; i++)
        {
            tempArr[indexTemp] = arrPoint[i];
            indexTemp++;
        }

        filledCells += amount;
        while (filledCells >= size)
            realloc(size * 2);
        
        for (int i = indexFill; i < indexFill+amount; i++)
            arrPoint[i] = item;

        indexTemp = 0;
        for (int i = indexFill + amount; i < indexFill + amount + distance; i++)
        {
            arrPoint[i] = tempArr[indexTemp];
            indexTemp++;
        }

        delete[] tempArr;
    }

    ~ListInt() {
        delete[] arrPoint;
    }
};

int main()
{
    ListInt<double> list;
    list.pushBack(21);
    list.pushBack(43);
    list.pushBack(4322);

    list.insert(list.begin()+1, 3, 4);


    for (double i : list)
    {
        std::cout << i << "\n";
    }
}