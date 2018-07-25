# Packet
## Documentation
**Method list**
***Method***| ***About*** 
--|--
*pgPacket* pgPacket()  | Empty constructor 
*pgPacket* pgPacket(const pgPacket &chPacket) | Copy constructor
*pgPacket* pgPacket(const std::vector<char> vecMemory)| Constructor by memo, you must get memory from packet first 
*pgPacket* ~pgPacket()| Destructor
*bool* push(T const &elm) | push variable to packet
*bool* push(const std::vector<T> Data)| push vector to packet
