#!/bin/bash

echo "Using the branch-and-cut method:"
./runner.py ../../data/toy/graph2.csv ../../data/toy/graph2_cannot_links.csv ../../data/toy/graph2_must_links.csv 3 0.6 bnc --verbose




