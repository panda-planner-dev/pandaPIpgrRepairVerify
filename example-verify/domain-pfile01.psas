;; #state features
11
+at[package_0,city_loc_1]
+at[package_1,city_loc_1]
+at[truck_0,city_loc_2]
+capacity[truck_0,capacity_1]
+at[truck_0,city_loc_1]
+at[truck_0,city_loc_0]
+in[package_0,truck_0]
+capacity[truck_0,capacity_0]
+in[package_1,truck_0]
+at[package_0,city_loc_0]
+at[package_1,city_loc_2]

;; Mutex Groups
11
0 0 +at[package_0,city_loc_1]
1 1 +at[package_1,city_loc_1]
2 2 +at[truck_0,city_loc_2]
3 3 +capacity[truck_0,capacity_1]
4 4 +at[truck_0,city_loc_1]
5 5 +at[truck_0,city_loc_0]
6 6 +in[package_0,truck_0]
7 7 +capacity[truck_0,capacity_0]
8 8 +in[package_1,truck_0]
9 9 +at[package_0,city_loc_0]
10 10 +at[package_1,city_loc_2]

;; further strict Mutex Groups
0

;; further non strict Mutex Groups
0

;; known invariants
0

;; Actions
13
1
8 2 7 -1
0 3  0 10  -1
0 7  0 8  -1
1
1 3 4 -1
0 7  0 8  -1
0 3  0 1  -1
1
2 -1
0 4  -1
0 2  -1
1
5 -1
0 4  -1
0 5  -1
1
4 -1
-1
-1
1
4 -1
0 5  -1
0 4  -1
1
5 -1
-1
-1
1
4 -1
0 2  -1
0 4  -1
1
2 -1
-1
-1
1
10 3 2 -1
0 7  0 8  -1
0 3  0 10  -1
1
5 6 7 -1
0 3  0 9  -1
0 7  0 6  -1
1
0 3 4 -1
0 7  0 6  -1
0 3  0 0  -1
1
9 3 5 -1
0 7  0 6  -1
0 3  0 9  -1

;; initial state
3 2 0 1 -1

;; goal
-1

;; tasks (primitive and abstract)
19
0 drop[truck_0,city_loc_2,package_1,capacity_0,capacity_1]
0 pick_up[truck_0,city_loc_1,package_1,capacity_0,capacity_1]
0 drive[truck_0,city_loc_2,city_loc_1]
0 drive[truck_0,city_loc_0,city_loc_1]
0 noop[truck_0,city_loc_1]
0 drive[truck_0,city_loc_1,city_loc_0]
0 noop[truck_0,city_loc_0]
0 drive[truck_0,city_loc_1,city_loc_2]
0 noop[truck_0,city_loc_2]
0 pick_up[truck_0,city_loc_2,package_1,capacity_0,capacity_1]
0 drop[truck_0,city_loc_0,package_0,capacity_0,capacity_1]
0 pick_up[truck_0,city_loc_1,package_0,capacity_0,capacity_1]
0 pick_up[truck_0,city_loc_0,package_0,capacity_0,capacity_1]
1 __top[]
1 m_deliver_ordering_0_splitted_1[truck_0,package_1]
1 get_to[truck_0,city_loc_1]
1 get_to[truck_0,city_loc_0]
1 get_to[truck_0,city_loc_2]
1 m_deliver_ordering_0_splitted_1[truck_0,package_0]

;; initial abstract task
13

;; methods
16
<<<<__top_method;deliver[package_1,city_loc_2];m_deliver_ordering_0;1;0,-1,-2,-3>;unload[truck_0,city_loc_2,package_1];m_unload_ordering_0;3;0,1,2,-1>;deliver[package_0,city_loc_0];m_deliver_ordering_0;0;-1,-2,-3,1,2,3>;unload[truck_0,city_loc_0,package_0];m_unload_ordering_0;2;0,1,-1,3,4,5>
13
18 16 10 14 17 0 -1
2 5 2 3 2 4 3 5 3 4 4 5 0 5 0 2 0 3 0 4 0 1 1 5 1 2 1 3 1 4 -1
<_splitting_method_m_deliver_ordering_0_splitted_1;load[truck_0,city_loc_1,package_1];m_load_ordering_0;1;0,-1>
14
15 1 -1
0 1 -1
m_drive_to_ordering_0
15
2 -1
-1
m_drive_to_ordering_0
15
3 -1
-1
m_i_am_there_ordering_0
15
4 -1
-1
m_drive_to_via_ordering_0
15
16 3 -1
0 1 -1
m_drive_to_ordering_0
16
5 -1
-1
m_i_am_there_ordering_0
16
6 -1
-1
m_drive_to_via_ordering_0
16
15 5 -1
0 1 -1
m_drive_to_via_ordering_0
15
17 2 -1
0 1 -1
m_drive_to_ordering_0
17
7 -1
-1
m_i_am_there_ordering_0
17
8 -1
-1
m_drive_to_via_ordering_0
17
15 7 -1
0 1 -1
<_splitting_method_m_deliver_ordering_0_splitted_1;load[truck_0,city_loc_2,package_1];m_load_ordering_0;1;0,-1>
14
17 9 -1
0 1 -1
<_splitting_method_m_deliver_ordering_0_splitted_1;load[truck_0,city_loc_1,package_0];m_load_ordering_0;1;0,-1>
18
15 11 -1
0 1 -1
<_splitting_method_m_deliver_ordering_0_splitted_1;load[truck_0,city_loc_0,package_0];m_load_ordering_0;1;0,-1>
18
16 12 -1
0 1 -1
