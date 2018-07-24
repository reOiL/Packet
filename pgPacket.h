//
// Created by reoil on 23.05.18.
//
#include <vector>
#include <iostream>
#include <cstring>
#include <list>
#include <set>
#include <map>
#include <typeinfo>

#ifndef PACKET_PGPACKET_H
#define PACKET_PGPACKET_H


#pragma pack (1)

class pgPacket {
private:
    std::vector<char> Packet; // Basic packet

    unsigned int w_rd; // position of last data pop
public:

    //! Basic constructor
    pgPacket();

    //! Copy constructor
    pgPacket(const pgPacket &chPacket);

    //! Constructor by memory vector (Memory vector mean vector created by function getMemory of this class)
    pgPacket(const std::vector<char> vecMemory);

    //! Destructor
    ~pgPacket();

private:

    //! Used for check can pop element
    bool verify(size_t elmSize);

    //! Used for push memory to vector
    bool push(const void *elm, size_t const elmSize);

public:

    //! push data
    template<typename T>
    bool push(T const &elm);

    //! push data
    template<typename T>
    bool push(const std::vector<T> Data);

    //! push data
    template<typename T>
    bool push(const std::set<T> Data);

    //! push data
    template<typename T>
    bool push(const std::list<T> Data);

    //! push data
    template<typename T1, typename T2>
    bool push(const std::pair<T1, T2> Data);

    //! push data
    template<typename T1, typename T2>
    bool push(const std::map<T1, T2> Data);

    //! push data
    bool push(const char * Data);

    //! push data
    bool push(const std::string Data);

    //! push data
    bool push(const pgPacket pkPacket);
private:

    //! pop memory from packet
    bool pop(void *elm, size_t const elmSize);

public:

    //! pop data
    template<typename T>
    bool pop(T &elm);

    //! pop data
    template<typename T>
    bool pop(std::set<T> &Data, const int iElm);

    //! pop data
    template<typename T>
    bool pop(std::list<T> &Data, const int iElm);

    //! pop data
    template<typename T1, typename T2>
    bool pop(std::pair<T1, T2> &Data);

    //! pop data
    template<typename T1, typename T2>
    bool pop(std::map<T1, T2> &Data, const int iElm);

    //! pop data
    bool pop(std::string &Data);

public:

    //! returned packet size
    size_t size() const;

    //! Erase all packet
    void clear();

    //! if packet empty return true
    bool isEmpty() const;

    //! Get memory from packet
    void getMemory(std::vector<char> &vecOut);

    //! Set position to 0
    void ThrowPosition();
public:

    //! Encrypted packet
    void crypt();

    //! Decrypted packet
    void decrypt();

public:

    //! Operator or compare packet return true if packet same
    bool operator==(const pgPacket &mPack);
};

#pragma pack ()

#include "pgPacket.inl" // include template realization

#endif //PACKET_PGPACKET_H