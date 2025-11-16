FROM ubuntu:24.04
RUN apt-get update && apt-get install -y \
    python3-pip \
    cmake \
    g++ \
    libboost-all-dev \
    libssl-dev \
    libsdl2-dev \
    && pip3 install conan