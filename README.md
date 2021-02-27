This repository is for my solution to the Interval Scheduling problem. 
I found this problem particularly interesting because there are many ways to solve it!
It was quite an interesting experience visualizing the data that was being presented by the problem,
and thinking of ways to organize into something to work with.

Through my different commits I ended up with three different approaches to this problem.
My first two attempts were trying to organize the schedules into a data structure that I am familiar with,
and then working with it to get the solution. Both of these attempts failed because I was trying to organize
the entire data set and work through it, which in this situation was inefficient.

My final solution took a different approach, when I decided to sort the data based on end times instead of
start times it became obvious what needed to be done to find the optimal solution. By taking the first
workshop based on end time, I was able to cut down the data set by quite a bit. Any workshop that started
before the ending time of the selected one can be ignored since it overlaps the selected one.

The final solution ended up being quite simple once I figured out this optimization for the data set!
