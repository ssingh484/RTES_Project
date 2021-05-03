# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Define base configuration.
FROM ubuntu:20.04
MAINTAINER ral@gatech.edu
WORKDIR /usr/local/

# Declare environment variables.
ENV account_host null
ENV account_port null
ENV follow_host null
ENV follow_port null
ENV initial_dataset_size 0
ENV max_calls 1000000
ENV max_duration 7200

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
RUN mkdir -p /var/log/microbench_follow

# Run microbenchmark.
CMD ["/bin/bash", "-c", "./bin/microbench_follow --account_host $account_host --account_port $account_port --follow_host $follow_host --follow_port $follow_port --initial_dataset_size $initial_dataset_size --output_dirpath /var/log/microbench_follow --max_calls $max_calls --max_duration $max_duration"]
