# Use an official Ubuntu runtime as a parent image
FROM ubuntu:latest

# Install g++, a C++ compiler
RUN apt-get update && apt-get install -y g++

# Install CMake
RUN apt-get install -y cmake

# Install libc++ library
RUN apt-get install -y libc++-dev