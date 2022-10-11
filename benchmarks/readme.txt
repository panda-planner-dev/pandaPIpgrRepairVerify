In this directory you find two domains. They contain three subdirectories for each of the domains: the first includes the planning domain, the second the problem files (100 problems for each domain), and the third contains the entire solution sequence for each problem. Problem and solution files are numbered so that they can be matched. You get the plan recognition problems by generating an instance with no observation, a single observation, two observations, and so on, until the whole solution sequence has been observed. The directoroes contain the fully observable case, so no observations are "missed".

The domains contain the artificial top-level task that is decomposed into the actual goal (as described in the paper). You might have to ignore (or delete) these for your approach.

In the Monroe domain you can find the actual goal tasks under the comment "original top-level-tasks".

As given in the paper (at the beginning of the evaluation section), in the kitchen domain you may have more than one goal: the top level tasks of a single problem may be:
(1) every combination of starter, main dish, and dessert
(2) every combination of starter and main dish
(3) every combination main dish and dessert
(4) just a main dish

The main dishes imply several top level tasks (e.g. cooking rice, trout, and beans). You can find these combinations in the domain (look for the methods main-1 to main-30).

If you have multiple goals, their subtasks may be interleaved.
