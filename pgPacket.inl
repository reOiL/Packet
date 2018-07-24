//#pragma pack (push, 1)

//! push data
template<typename T>
bool pgPacket::push(T const &elm) {
    size_t const elmSize = sizeof(T);
    return this->push((void const *) &elm, elmSize);
}

//! push data
template<typename T>
bool pgPacket::push(const std::vector<T> Data) {
    for (auto it : Data) {
        if (!this->push(it, sizeof(T)))
            return false;
    }
    return true;
}

//! push data
template<typename T>
bool pgPacket::push(const std::set<T> Data) {
    for (auto it : Data) {
        if (!this->push(it))
            return false;
    }
    return true;
}

//! push data
template<typename T>
bool pgPacket::push(const std::list<T> Data) {
    for (auto it : Data) {
        if (!this->push(it))
            return false;
    }
    return true;
}

//! push data
template<typename T1, typename T2>
bool pgPacket::push(const std::pair<T1, T2> Data) {
    if (this->push(Data.first))
        if (this->push(Data.second))
            return true;

    return false;
}

//! push data
template<typename T1, typename T2>
bool pgPacket::push(const std::map<T1, T2> Data) {
    for (auto it: Data) {
        if (!this->push(it))
            return false;
    }
    return true;
}

//! pop data
template<typename T>
bool pgPacket::pop(T &elm) {
    size_t const elmSize = sizeof(T);
    return this->pop(&elm, elmSize);
}

//! pop data
template<typename T>
bool pgPacket::pop(std::set<T> &Data, const int iElm) {
    for (int i = 0; i < iElm; i++) {
        T temp;
        if (!this->pop(temp))
            return false;
        Data.insert(temp);
    }
    return true;
}

//! pop data
template<typename T>
bool pgPacket::pop(std::list<T> &Data, const int iElm) {
    for (int i = 0; i < iElm; i++) {
        T temp;
        if (!this->pop(temp))
            return false;
        Data.push_back(temp);
    }
    return true;
}

//! pop data
template<typename T1, typename T2>
bool pgPacket::pop(std::pair<T1, T2> &Data) {
    T1 temp1;
    T2 temp2;
    return !(!this->pop(Data.first) || !this->pop(Data.second));

}

//! pop data
template<typename T1, typename T2>
bool pgPacket::pop(std::map<T1, T2> &Data, const int iElm) {
    for (int i = 0; i < iElm; i++) {
        std::pair<T1, T2> temp_pair;
        if (!this->pop(temp_pair))
            return false;
        Data.insert(temp_pair);
    }
    return true;
}

//#pragma pack(pop)