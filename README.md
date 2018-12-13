# TSP-Variant
This project is inspired by a programming problem I solved recently, the problem can be formulated as follows:
Given n sales persons, and m points on the 2D-plane, each salesman starts from the origin point (0,0) then visit some points (or no points) then come back to the origin such that every point is visited exactly once. Find some assignment of points for salesmen such that the maximum travelled Euclidean distance among all sales persons is minimal.
The program first solves the TSP problem for all subset of points, using the classical DP solution. Then we use another DP to try to assign the next sales person some subset of the non-visited points.
The overall complexity of this solution is O(2^2m * m^2) which gives m an upper bound of about 10 to run in reasonable time.
