## Usage

```
usage: runner.py [-h] [--timeout TIMEOUT] [--verbose] [--nosym] [--overlap] [--single]
                 graph_file cl_file ml_file k gamma {basic,bnc}

positional arguments:
  graph_file         file containing the edges
  cl_file            file containing the can-not-link constraints
  ml_file            file containing the must-link constraints
  k                  number of clusters
  gamma              balance coefficient
  {basic,bnc}        mip model to be used

optional arguments:
  -h, --help         show this help message and exit
  --timeout TIMEOUT  set a time limit
  --verbose          print detailed output
  --nosym            disable symmetry breaking
  --overlap          allow overlap between clusters
  --single           add at most one cut per cluster
```
