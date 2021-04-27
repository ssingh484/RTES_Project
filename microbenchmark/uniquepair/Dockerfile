# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Define base configuration.
FROM ubuntu:20.04
MAINTAINER ral@gatech.edu
WORKDIR /usr/local/

# Declare environment variables.
ENV host null
ENV port null
ENV n_worker_threads null
ENV add_max_rate 0
ENV add_duration_sec 0
ENV add_ramp_up_time_sec 0
ENV add_ramp_down_time_sec 0
ENV get_max_rate 0
ENV get_duration_sec 0
ENV get_ramp_up_time_sec 0
ENV get_ramp_down_time_sec 0
ENV find_max_rate 0
ENV find_duration_sec 0
ENV find_ramp_up_time_sec 0
ENV find_ramp_down_time_sec 0
ENV fetch_max_rate 0
ENV fetch_duration_sec 0
ENV fetch_ramp_up_time_sec 0
ENV fetch_ramp_down_time_sec 0
ENV count_max_rate 0
ENV count_duration_sec 0
ENV count_ramp_up_time_sec 0
ENV count_ramp_down_time_sec 0
ENV remove_max_rate 0
ENV remove_duration_sec 0
ENV remove_ramp_up_time_sec 0
ENV remove_ramp_down_time_sec 0

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

# Copy cppmicrobench 0.1.
RUN cd /tmp \
  && wget https://github.com/rodrigoalveslima/cppmicrobench/archive/refs/tags/v0,1.zip \
  && unzip v0,1.zip \
  && cp cppmicrobench-0-1/include/cppmicrobench.h /usr/local/include

# Copy service client libraries.
COPY include include

# Copy source code.
COPY src src

# Compile source code.
RUN cd src && make

# Create directory for results.
RUN mkdir -p /var/log/microbench_uniquepair

# Run microbenchmark.
CMD ["/bin/bash", "-c", "./bin/microbench_uniquepair --host $host --port $port --output_dirpath /var/log/microbench_uniquepair --n_worker_threads $n_worker_threads --add_max_rate $add_max_rate --add_duration_sec $add_duration_sec --add_ramp_up_time_sec $add_ramp_up_time_sec --add_ramp_down_time_sec $add_ramp_down_time_sec --get_max_rate $get_max_rate --get_duration_sec $get_duration_sec --get_ramp_up_time_sec $get_ramp_up_time_sec --get_ramp_down_time_sec $get_ramp_down_time_sec --find_max_rate $find_max_rate --find_duration_sec $find_duration_sec --find_ramp_up_time_sec $find_ramp_up_time_sec --find_ramp_down_time_sec $find_ramp_down_time_sec --fetch_max_rate $fetch_max_rate --fetch_duration_sec $fetch_duration_sec --fetch_ramp_up_time_sec $fetch_ramp_up_time_sec --fetch_ramp_down_time_sec $fetch_ramp_down_time_sec --count_max_rate $count_max_rate --count_duration_sec $count_duration_sec --count_ramp_up_time_sec $count_ramp_up_time_sec --count_ramp_down_time_sec $count_ramp_down_time_sec --remove_max_rate $remove_max_rate --remove_duration_sec $remove_duration_sec --remove_ramp_up_time_sec $remove_ramp_up_time_sec --remove_ramp_down_time_sec $remove_ramp_down_time_sec"]
