# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Define base configuration.
FROM ubuntu:20.04
MAINTAINER ral@gatech.edu
WORKDIR /usr/local/

# Declare environment variables.
ENV server true
ENV host 0.0.0.0
ENV port 9094
ENV max_calls 0
ENV max_duration 0

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

# Copy cppbench 0.1.2
RUN cd /tmp \
  && wget https://github.com/rodrigoalveslima/cppbench/archive/refs/tags/v0.1.2.zip \
  && unzip v0.1.2.zip \
  && cp cppbench-0.1.2/include/cppbench.h /usr/local/include

# Copy service client libraries.
COPY include include

# Copy source code.
COPY src src

# Compile source code.
RUN cd src && make

# Create directory for results.
RUN mkdir -p /var/log/uniquepair_baseline_server

# Run microbenchmark.
CMD ["/bin/bash", "-c", "./bin/uniquepair_baseline_server --server $server --host $host --port $port --output_dirpath /var/log/uniquepair_baseline_server --max_calls $max_calls --max_duration $max_duration"]
