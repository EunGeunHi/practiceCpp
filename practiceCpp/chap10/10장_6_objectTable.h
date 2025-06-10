// ===========================
// 템플릿 ObjectTable 클래스 > ObjectTable.h로 선언부와 같이 저장
// ===========================
template <typename T>
class ObjectTable {
private:
    T* data[MAX];
    int size;
public:
    ObjectTable();
    ~ObjectTable();
    void add(T* obj);
    void remove(int index);
    void update(int index, T* obj);
    int search(T* target);
    void sort();
    void showAll() const;
};


//정의도 같은 파일 안에 구현해야 컴파일러가 찾아 쓸수 있음
template <typename T>
ObjectTable<T>::ObjectTable() : size(0) {
    for (int i = 0; i < MAX; i++)
        data[i] = nullptr;
}

template <typename T>
ObjectTable<T>::~ObjectTable() {
    for (int i = 0; i < size; i++)
        delete data[i];
}

template <typename T>
void ObjectTable<T>::add(T* obj) {
    if (size < MAX) data[size++] = obj;
    else cout << "📛 테이블 용량 초과\n";
}

template <typename T>
void ObjectTable<T>::remove(int index) {
    if (index >= 0 && index < size) {
        delete data[index];
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        data[--size] = nullptr;
    }
}

template <typename T>
void ObjectTable<T>::update(int index, T* obj) {
    if (index >= 0 && index < size) {
        delete data[index];
        data[index] = obj;
    }
}

template <typename T>
int ObjectTable<T>::search(T* target) {
    for (int i = 0; i < size; i++)
        if (*data[i] == *target)
            return i;
    return -1;
}

template <typename T>
void ObjectTable<T>::sort() {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*data[i] > *data[j])
                swap(data[i], data[j]);
}

template <typename T>
void ObjectTable<T>::showAll() const {
    for (int i = 0; i < size; i++)
        data[i]->show();
}