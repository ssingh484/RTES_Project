#!/bin/bash

# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Process command-line arguments.
set -u
while [[ $# > 1 ]]; do
  case $1 in
    --type )
      type=$2
      ;;
    --username )
      username=$2
      ;;
    --private_ssh_key_path )
      private_ssh_key_path=$2
      ;;
    --node_0 )
      node_0=$2
      ;;
    --node_1 )
      node_1=$2
      ;;
    --node_2 )
      node_2=$2
      ;;
    --node_3 )
      node_3=$2
      ;;
    * )
      echo "Invalid argument: $1"
      exit 1
  esac
  shift
  shift
done

# Copy the SSH private key to node-0.
scp -o StrictHostKeyChecking=no ${private_ssh_key_path} ${username}@${node_0}:.ssh/id_rsa

if [ $type = microbench ]; then
  node_2=empty
  node_3=empty
fi

# Log into node-0.
ssh -o StrictHostKeyChecking=no ${username}@${node_0} "
  # Install Docker.
  sudo apt-get update
  sudo apt-get -y install apt-transport-https ca-certificates curl gnupg-agent \
      software-properties-common
  curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
  sudo add-apt-repository \"deb [arch=amd64] https://download.docker.com/linux/ubuntu \$(lsb_release -cs) stable\"
  sudo apt-get update
  sudo apt-get install -y docker-ce docker-ce-cli containerd.io

  # Clone this repository to get the experiment configuration files.
  ssh-keygen -F github.com || ssh-keyscan github.com >> ~/.ssh/known_hosts
  git clone git@github.com:rodrigoalveslima/BuzzBlogBenchmark.git
  mv BuzzBlogBenchmark/controller/conf/* .
  rm -rf BuzzBlogBenchmark

  # Set up configuration files.
  if [ $type = microbench ]; then
    mv system_microbench.yml system.yml
    rm system_loadgen.yml
    rm workload.yml
    sed -i \"s/{{username}}/${username}/g\" system.yml
    sed -i \"s/{{node-0}}/${node_0}/g\" system.yml
    sed -i \"s/{{node-1}}/${node_1}/g\" system.yml
  else
    mv system_loadgen.yml system.yml
    rm system_microbench.yml
    sed -i \"s/{{username}}/${username}/g\" system.yml
    sed -i \"s/{{node-0}}/${node_0}/g\" system.yml
    sed -i \"s/{{node-1}}/${node_1}/g\" system.yml
    sed -i \"s/{{node-2}}/${node_2}/g\" system.yml
    sed -i \"s/{{node-3}}/${node_3}/g\" system.yml
  fi
"
