# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Define base configuration.
FROM ubuntu:20.04
MAINTAINER ral@gatech.edu
WORKDIR /usr/local/

# Declare environment variables.
ENV host null
ENV port null
ENV initial_dataset_size 0
ENV add_count 0
ENV get_count 0
ENV find_count 0
ENV fetch_count 0
ENV count_count 0
ENV remove_count 0

# Install software dependencies.
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    apt-utils \
    automake \
    bison \
    flex \
    g++ \
    git \
    gnupg2 \
    libboost-all-dev \
    libevent-dev \
    libssl-dev \
    libtool \
    lsb-core \
    make \
    pkg-config \
    wget \
    unzip

# Install Thrift 0.13.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libthrift-0.13.0=0.13.0-2build2 \
  libthrift-dev=0.13.0-2build2

# Copy cxxopts 2.2.1.
RUN cd /tmp \
  && wget https://github.com/jarro2783/cxxopts/archive/v2.2.1.zip \
  && unzip v2.2.1.zip \
  && cp cxxopts-2.2.1/include/cxxopts.hpp /usr/local/include

# Copy cppbench 0.1.1
RUN cd /tmp \
  && wget https://github.com/rodrigoalveslima/cppbench/archive/refs/tags/v0.1.1.zip \
  && unzip v0.1.1.zip \
  && cp cppbench-0.1.1/include/cppbench.h /usr/local/include

# Copy service client libraries.
COPY include include

# Copy source code.
COPY src src

# Compile source code.
RUN cd src && make

# Create directory for results.
RUN mkdir -p /var/log/microbench_uniquepair

# Run microbenchmark.
CMD ["/bin/bash", "-c", "./bin/microbench_uniquepair --host $host --port $port --initial_dataset_size $initial_dataset_size --output_dirpath /var/log/microbench_uniquepair --add_count $add_count --get_count $get_count --find_count $find_count --fetch_count $fetch_count --count_count $count_count --remove_count $remove_count"]
