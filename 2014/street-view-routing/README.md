# street view routing (2014 final)

## Problem statements

* [View problem](https://storage.googleapis.com/coding-competitions.appspot.com/HC/2014/hashcode2014_final_task.pdf)
* [Download input file](https://storage.googleapis.com/coding-competitions.appspot.com/HC/2014/paris_54000.txt)

## Solution 

* Very simple greedy approach: just take the highest scored edge respecting the time constraint.
* Scoring
   - once visit an edge, the length of the edge becomes 0. On the next visit, the length will be decremented by 1. e.g. 30 -> 0 -> -1 -> -2.
   - score: score = length^3 / cost

## Achieve Score

907271
