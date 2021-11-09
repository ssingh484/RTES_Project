import argparse
import datetime
import os
import re
import subprocess
import threading
import time
import tarfile

import jinja2
import yaml

DIRNAME = ""
SYS_CONF = {}


def nodes_with_monitor(monitor_name_pat):
  """Run func for nodes with the specified monitor (regex supported)."""
  def func_wrapper_outer(func):
    def func_wrapper_inner(*args, **kwargs):
      for node_hostname, node_conf in SYS_CONF.items():
        for monitor_name in node_conf.get("monitors", {}):
          if re.match(monitor_name_pat, monitor_name):
            break
        else:
          continue
        func(node_hostname, node_conf)
    return func_wrapper_inner
  return func_wrapper_outer

def compress(path, tar_name):
    with tarfile.open(tar_name, "w:gz") as tar_handle:
        for root, dirs, files in os.walk(path):
            for file in files:
                tar_handle.add(os.path.join(root, file))

@nodes_with_monitor("perf record")
def compile_perf_data(node_hostname, node_conf):
  for monitor_name, monitor_conf in node_conf["monitors"].items():
      if "perf" in monitor_name:
          my_tar = tarfile.open("{}.tar.gz".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) ) )
          my_tar.extractall("{}".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) ) )
          my_tar.close()
          # os.remove("{}.tar.gz".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) ) )
          # WORK HERE USING FLAMEGRAPH TOOLS - check this all works via touch below this
          # partA = subprocess.call(["perl", "stackcollapse-perf.pl", "{input}/perf.out > {input}/perf.folded".format(input = os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') )) ], shell=True )
          partA = subprocess.call("perl stackcollapse-perf.pl {input}/perf.out > {input}/perf.folded".format(input = os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') )), shell=True )
          print(f"PART 1 DONE for node {node_hostname}\n\n")
          if partA == 0:
            subprocess.call("perl flamegraph.pl {input}/perf.folded > {input}/{host}.svg".format(input = os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ), host = node_hostname), shell=True )
          else:
            print(f"FAILED TO MAKE SVG ON {node_hostname}")
          # from pathlib import Path
          # Path("{}/TEST.txt".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) )).touch()
          # compress("{}".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) ), "{}.tar.gz".format(os.path.join(DIRNAME, "logs", node_hostname, monitor_name.replace(' ', '_') ) ) )
      else:
          pass


def run(dirname):
  # Parse command-line arguments.
  if dirname == None:
      print("PLEASE GIVE THE EXPERIMENT DIRECTORY")
      return
  global DIRNAME
  DIRNAME = dirname
  # Load system configuration.
  global SYS_CONF
  with open(os.path.join(DIRNAME, "conf", "system.yml")) as system_conf_file:
    SYS_CONF = yaml.load(system_conf_file, Loader=yaml.Loader)

  # print(DIRNAME, "   ", SYS_CONF)
  compile_perf_data()


if __name__ == "__main__":

  parser = argparse.ArgumentParser(description="Parse perf logs to make svg files")
  parser.add_argument("--dirname", required=True, action="store",
      type=str, help="Path to the BuzzBlogBenchmark_XXX file")
  args = parser.parse_args()
  run(args.dirname)
