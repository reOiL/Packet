//
// Created by reoil on 23.05.18.
//

#include "pgPacket.h"
#include <algorithm>

#define PACKET_ENCRYPT_KEY ( ( ('a' ^ 4 >> 2) * ('b' & 'F' ) ) * 2 ) // encrypted key for packet

//! Basic constructor
pgPacket::pgPacket() {
    this->w_rd = 0;     //set last position to 0
}

//! Copy constructor
pgPacket::pgPacket(const pgPacket &chPacket) {
    this->Packet = chPacket.Packet; // copy packet
    this->w_rd = chPacket.w_rd;     // copy position
}

//! Constructor by memory vector (Memory vector mean vector created by function getMemory of this class)
pgPacket::pgPacket(const std::vector<char> vecMemory) {
    this->w_rd = 0;             // set position to 0
    this->Packet = vecMemory;   // copy data from vector
}

//! Destructor
pgPacket::~pgPacket() {

}

//! Used for check can pop element
bool pgPacket::verify(size_t elmSize) {
    bool const bRet = ((this->Packet.size() - this->w_rd) >= elmSize)
                      ? // check size packet vs data type size if packet size < data type size return false
                      (int) this->Packet.at(this->w_rd) == elmSize
                      : // checked data type in packet at position vs data type size
                      false;
    this->w_rd++; // set next position for start read element
    return bRet;
}

//! Used for push memory to vector
bool pgPacket::push(const void *elm, size_t const elmSize) {
    this->Packet.push_back((char) elmSize); // push data size for verify
    char Arr[elmSize] = {};                 // init char array for memory
    memcpy(Arr, elm, elmSize);              // copy memory to array
    for (int i = 0; i < elmSize; ++i) {
        this->Packet.push_back(Arr[i]);     // push data to vector
    }
    return true;
}

//! push data
bool pgPacket::push(const char *Data) {
    this->push(std::strlen(Data));  // push string size
    for (unsigned int i = 0; i < std::strlen(Data); i++) {
        this->Packet.push_back(Data[i]);    // push string to memory
    }
    return true;
}

//! push data
bool pgPacket::push(const std::string Data) {
    this->push(Data.c_str()); // push std::String bu const char *
    return true;
}

//! push data
bool pgPacket::push(const pgPacket pkPacket) {
    for(unsigned int i = pkPacket.w_rd; i < pkPacket.size(); i++)
    {
        this->Packet.push_back(pkPacket.Packet.at(i)); // insert packet to packet
    }
    return true;
}

//! Pop memory from packet
bool pgPacket::pop(void *Data, size_t const elmSize) {
    if (!this->verify(elmSize)) { return false; }; // check element data type vs element data type in vector
    char Arr[elmSize] = {}; //array for get memory from vector
    for (unsigned int i = 0 + w_rd; i < elmSize + w_rd; i++) {
        Arr[i - w_rd] = this->Packet.at(i); // get memory from vector to array
    }
    this->w_rd += elmSize; // set next position
    memcpy(Data, Arr, elmSize); // copy memory from array to variable
    return true;
}

//! Pop std::string from packet
bool pgPacket::pop(std::string &Data) {
    size_t iDataSize = 0;   // for get string len from packet
    if (!this->pop(iDataSize) ||                                // get string len from packet
            (this->Packet.size() - this->w_rd) < iDataSize )    // check string len for can get data from packet
    { return false; }

    Data.resize(static_cast<unsigned int>(iDataSize), '\0');    // resize string
    for (unsigned int i = 0 + this->w_rd; i < iDataSize + this->w_rd; i++) {
        Data.at(i - w_rd) = this->Packet.at(i);                 // insert data to string
    }
    this->w_rd += iDataSize; // move position
    return true;
}

//! returned packet size
size_t pgPacket::size() const {
    return this->Packet.size(); // get packet size
}

//! Erase all packet
void pgPacket::clear() {
    this->Packet.clear();   // clearing packet
    this->w_rd = 0;         // set last position to 0
}

//! if packet empty return true
bool pgPacket::isEmpty() const {
    return this->Packet.size() == 0; // check if size = 0
}

//! Get memory from packet
void pgPacket::getMemory(std::vector<char> &vecOut) {
    vecOut = this->Packet;  // copy memory to vector
}

//! Set position to 0
void pgPacket::ThrowPosition() {
    this->w_rd = 0; // set packet position to 0
}

//! Encrypted packet
void pgPacket::crypt() {
    for (unsigned int i = 0; i < this->Packet.size(); i++) {
        this->Packet[i] = static_cast<char>(this->Packet.at(i) ^ PACKET_ENCRYPT_KEY); // encrypt packet
    }
    std::reverse(this->Packet.begin(), this->Packet.end());                           // revers packet
}

//! Decrypted packet
void pgPacket::decrypt() {
    for (unsigned int i = 0; i < this->Packet.size(); i++) {
        this->Packet[i] = static_cast<char>(this->Packet.at(i) ^ PACKET_ENCRYPT_KEY); // decrypt packet
    }
    std::reverse(this->Packet.begin(), this->Packet.end());                           // revers packet
}

//! Operator or compare packet return true if packet same
bool pgPacket::operator==(const pgPacket &mPack) {
    return this->Packet == mPack.Packet; // compare
}
