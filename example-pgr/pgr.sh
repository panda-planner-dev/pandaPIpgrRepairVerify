#!/bin/bash
# make sure that the following executables are present:
# -
if [[ $# -ne 3 ]]
then
  echo "usage: <script> domain.hddl problem.hddl <plan-file>"
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

  # determine number of plan steps
  steps=$(grep -o "([^()]*)" $3 | wc -l)

  for i in $(seq 0 $steps)
  do
    ./htnPrefixEncoding "pgrfo" "$(basename "$1" .hddl)-$(basename "$2" .hddl).psas" "$3" $i
#     ./pproFF1800 "$3".pgr |tee "$3".log
#      if you are interested in a human-readable plan, uncomment the following:
#     ./pandaPIparser -c "$3".log "$3".plan
  done

  status=$?
  if [ $status -ne 0 ]; then
    echo "encoding failed."
    exit 103
  fi
fi
