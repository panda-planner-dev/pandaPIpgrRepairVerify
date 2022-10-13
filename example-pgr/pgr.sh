#!/bin/bash
#
# make sure that the following executables are present:
# ./pandaPIparser – the is the parser from the PANDA framework
# ./pandaPIgrounder – the grounder from the PANDA framework
# ./htnPrefixEncoding – the code from this repository
# ./pplanner – some planner supporting the PANDA intermediate file format as input.
#
if [[ $# -ne 3 ]]
then
  echo "usage: pgr.sh domain.hddl problem.hddl planfile.txt"
else
  ./pandaPIparser $1 $2 temp.parsed
  if [ ! -f temp.parsed ]; then
    echo "Parsing failed."
    exit 101
  fi

  ./pandaPIgrounder -q temp.parsed "$(basename "$1" .hddl)-$(basename "$2" .hddl).psas"
  rm temp.parsed
  if [ ! -f "$(basename "$1" .hddl)-$(basename "$2" .hddl).psas" ]; then
    echo "Grounding failed."
    exit 10
  fi

  # determine number of plan steps in the solution
  steps=$(grep -o "([^()]*)" $3 | wc -l)

  for i in $(seq 0 $steps)
  do
    ./htnPrefixEncoding "pgrfo" "$(basename "$1" .hddl)-$(basename "$2" .hddl).psas" "$3" "$i"
    if (( i < steps )); then
      if (( i < 10 )); then
        pgrprob="$3-00$i.pgr"
      elif (( i < 100 )); then
        pgrprob="$3-0$i.pgr"
      else
        pgrprob="$3-$i.pgr"
      fi
    else
      pgrprob="$3-full.pgr"
    fi
    echo "$pgrprob"
    ./pplanner "$pgrprob" | tee "$3".log
#      if you are interested in a human-readable plan, uncomment the following:
#     ./pandaPIparser -c "$3".log "$pgrprob".plan
  done

  status=$?
  if [ $status -ne 0 ]; then
    echo "encoding failed."
    exit 103
  fi
fi
