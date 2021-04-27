# VerificationAsPlanning
This tool allows for determining whether a given sequence of actions is a solution to an HTN planning problem.
This involves (a) determing whether the sequence is executable in the initial state and reaches the goal state and (b) determining whether the sequence can be derived from the problems intial plan by applying decompositions.


To this end, VerificationAsPlanning translates the sequence of actions and the HTN planning problem into a new HTN planning problem: the verfication problem.
The sequence is a solution, if the verfication problem is solvable.

## Compiling VerificationAsPlanning
To compile VerificationAsPlanning run the following commands

```
mkdir build
cd build
cmake ..
make
```

This will create a binary called `verificationAsPlanning`

## Input Format
VerificationAsPlanning reads the sequence of actions from a file.
Each line of the file shall contain one of the actions.
Each action shall be enclosed by normal braces `(` and `)`.
Within these braces, no spaces shall occur.
After the opening brace, the name of the action shall be given.
This is followed by a square opening brace `[`.
Then follow the arguments of the action, separated by commas.
Then follows a closing square brace `]` and the overall closing brace `)`.
The plan for a transport-style problem might look like this:

```
(drive[truck_0,city_loc_2,city_loc_1])
(pick_up[truck_0,city_loc_1,package_0,capacity_0,capacity_1])
(drive[truck_0,city_loc_1,city_loc_0])
(drop[truck_0,city_loc_0,package_0,capacity_0,capacity_1])
(drive[truck_0,city_loc_0,city_loc_1])
(pick_up[truck_0,city_loc_1,package_1,capacity_0,capacity_1])
(drive[truck_0,city_loc_1,city_loc_2])
(drop[truck_0,city_loc_2,package_1,capacity_0,capacity_1])
```

## Using VerificationAsPlanning
Running VerificationAsPlanning requires the full stack of the pandaPI planner to be installe
You need to obtain [parser](https://github.com/panda-planner-dev/pandaPIparser), [grounder](https://github.com/panda-planner-dev/pandaPIgrounder), and [engine](https://github.com/panda-planner-dev/pandaPIengine).

For running the verification, you have to do the following -- assuming that the domain file in HDDL is called domain.hddl, the problem file problem.hddl, and the plan plan.txt

```
.../pandaPIparser domain.hddl problem.hddl probem.htn
.../pandaPIgrounder -DE problem.htn problem.sas
./build/verificationAsPlanning problem.sas plan.txt
.../pandaPIengine plan.txt.verify --suboptimal --gValue=none
```

If the planner returns `Proven unsolvable`, the given sequence is not a plan, if it finds a solution, the found plan is a witness for the decomposition of the given action sequence (when artificial decomposition are removed).


## Pre-Compiled Singularity Container
A pre-compiled version of the verifier (including the necessary parser, grounder, and search engine) is [available](https://gki.informatik.uni-freiburg.de/~behnkeg/panda-verify.sif).
To run it, create a new (temporary) directory.
Put your domain file and your problem file into this directory.
Further create a file in this directory containing your plan.
You further need singularity (version 3.5 or above).
To run the verifier go to the created directory and run the following command (substituting file names are approriate):

```
singularity run -H $(pwd) -C ../../panda-verify.sif domain.hddl pfile01.hddl plan.txt 1800 8000 42
```

(1800 is the timelimit in seconds, 8000 the memory limit -- which is ignored by the verifier, and 42 the random seed).
