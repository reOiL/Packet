cmake_minimum_required(VERSION 3.5)
project(Packet)

set(CMAKE_CXX_STANDARD 11)

add_library(Packet pgPacket.cpp pgPacket.h pgPacket.inl)