
# HTN Prefix Encoding

This repository contains code to solve the following problems by compiling them to HTN planning problems:
* Plan and Goal Recognition (PGR) – i.e., the task to identify the goal and next steps of an observed agent based on a sequence of actions the agent has executed. In our case, we use HTN models to describe the agents' behavior.
* Plan Repair in the context of HTN planning – i.e., the task to find a new solution that fulfill certain properties given the execution of a first solution failed.
* Verification of HTN plans – i.e., the task to decide whether or not a given sequence of actions is a solution for a given HTN planning problem.

More technically, the implemented transformation restricts the set of solutions to an HTN planning problem to the subset of solutions that start with a certain prefix (or – in case of partially observable PGR – includes a certain prefix).

The different approaches have been presented in the following publications, which provide a more detailed description of the respective problems and how they are solved. If you use the code, please cite the respective paper:

    @inproceedings{Hoeller22verify,
      author    = {Daniel H{\"{o}}ller and Julia Wichlacz and Pascal Bercher and Gregor Behnke},
      title     = {Compiling {HTN} Plan Verification Problems into {HTN} Planning Problems},
      booktitle = {Proceedings of the 32nd International Conference on Automated Planning and Scheduling (ICAPS)},
      publisher = {{AAAI} Press},
      pages     = {145-150},
      year      = {2022}
    }

    @inproceedings{Hoeller20repair,
      author    = {Daniel H{\"{o}}ller and Pascal Bercher and Gregor Behnke and Susanne Biundo},
      title     = {{HTN} Plan Repair via Model Transformation},
      booktitle = {Proceedings of the 43rd German Conference on Artificial Intelligence (KI)},
      publisher = {Springer},
      pages     = {88--101},
      year      = {2020}
    }

    @inproceedings{Hoeller18pgr,
      author    = {Daniel H{\"{o}}ller and Gregor Behnke and Pascal Bercher and Susanne Biundo},
      title     = {Plan and Goal Recognition as {HTN} Planning},
      booktitle = {Proceedings of the 30th IEEE International Conference on Tools with Artificial Intelligence (ICTAI)},
      publisher = {IEEE Computer Society},
      pages     = {466--473},
      year      = {2018}
    }


## How to use the code

The general process is the same for solving all these problems:
* The HTN model needs to be grounded using the PANDA grounder
* You need to provide a second file with the prefix to enforce (i.e., the observed actions of the agent, the plan to repair, or the solution to verify)
* The transformation creates a new problem file using the format used by PANDA to represent its input
* This file must be passed to a planner that supports this format as its input (e.g., a planner from the PANDA framework)

All components of the PANDA system can be found under the following adress:
[git repository of the PANDA framwork](https://panda-planner-dev.github.io/)

Make sure to compile the following software components:
* the PANDA parser
* the PANDA grounder
* some planner, e.g. one from the PANDA framework. Both the progression-based and the SAT-based planners might be promissing (depending on your model)
* the code in this repository

A script on how to use these components is given in the repository ("example-pgr/pgr.sh").

## How to use the PGR benchmarks

There are two benchmark sets for plan and goal recognition given in the repository. The "Kitchen" domain was created by us. It is described in the ICTAI'18 paper given above. The second one is the "Monroe" domain. It was **not** created by us, we just translated it into the HDDL format. Please make sure to **give proper credit** to the original authors.

    @inproceedings{Blaylock05,
      author    = {Nate Blaylock and James F. Allen},
      title     = {Generating Artificial Corpora for Plan Recognition},
      booktitle = {Proceedings of the 10th International Conference on User Modeling ({UM})},
      publisher = {Springer},
      pages     = {179--188},
      year      = {2005}
    }

The benchmark directories have three subdirectories, one with the domain, one with the problems, and one with the solutions.

### Add generic top level task
If you open one of the problem files, you will find a line starting with "(:htn :tasks" (here the first of the Monroe domain):

    ;; (:htn :tasks (tlt)) ;; generic tlt
    (:htn :tasks (clear-road-wreck pittsford-plaza airport)) ;; org. tlt

This defines the initial task of the HTN planning problem. As you can see, it is set to the task that shall be recognized. As first step, you need to replace them with the generic initial task, e.g.:

    (:htn :tasks (tlt)) ;; generic tlt
    ;; (:htn :tasks (clear-road-wreck pittsford-plaza airport)) ;; org. tlt

### Delete observations
If you want to do your evaluate in the partically observable setting, delete some of the observations.

### Run Recognition
Adapt the script ("example-pgr/pgr.sh") to your needs and start it. The new problems are written next to the solution file that is provided.

### Extract Results
The planner decomposes the intial task into the top level task (the "goal" of the agent). The PANDA preprocessing incorporates several transformations that make the results less human readable. You can undo them using the PANDA parser:

./pandaPIparser -c log-of-planner-run.txt human-readable.plan

In the file "human.readable.plan", you will find something like the following:

    ...
    root 198
    ...
    198 tlt  -> m-tlt-clear-road-wreck 1916
    ...
    1916 clear-road-wreck pittsford-plaza airport -> m-clear-road-wreck 202 1915 1753
    ...

These lines provide you with the top level task choosen by the planner. Read it the following way:
* The task with id 198 is the initial (root) task.
* This task is named "tlt" (as we provided in the last step). The task is decomposed using the method "m-tlt-clear-road-wreck" into the task with the id 1916
* The task with id 1916 is "clear-road-wreck pittsford-plaza airport"

# Usage of the code
If you use our code, I would be happy to know about it. So far, it has been used in the TOAD system:
 1. Daniel Höller. Translating Totally Ordered HTN Planning Problems to Classical Planning Problems Using Regular Approximation of Context-Free Languages. In: Proceedings of the 31st International Conference on Automated Planning and Scheduling (ICAPS). AAAI Press, 2021.
