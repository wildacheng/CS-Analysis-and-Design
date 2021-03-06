# CS-Analysis-and-Design

#What was the problem you were solving in the projects for this course?
The academic advisors in the Computer Science department at ABCU needed an application that the department advisors could use to help talk with students. They needed a program that could read a CSV course data file, load the data into a data structure, print an alphanumeric list of all the courses, and print the course title and the prerequisities for any individual course. 

#How did you approach the problem? Consider why data structures are important to understand.
When approaching this problem, I first went over the requirements that would affect which data structure I might use. The two main problems were printing an alphanumeric list of all the courses, and searching for a specific course to print its information. Utilizing a vector would easily solve the task of sorting the course numbers alphanumerically with C++ built in sorting method, but the look up speed in terms of Big O is O(n). This could become an issue as the numbers of courses increases. In comparison to a hash table, although sorting the courses may require more space than a vector, the look up speed is constant even as the number of courses increases. Data structures are important to understand when developing a program because the run-time and memory of the data structures affects how fast or slow a program runs and the amount of space/memory it takes up.


#How did you overcome any roadblocks you encountered while going through the activities or project?
Whenever I encountered a roadblock while going through the activities, I would follow a series of steps to solve it. First I would go over the issue, reread any helpful sections, and if I need further understanding on a topic, I will search it on the internet. 

#How has your work on this project expanded your approach to designing software and developing programs?
My approach to designing and developing software has improved because now I take into consideration which data structures might be best suited for the task. 

#How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
My work on this project has encouraged me to continue writing in industry standard best practices. For example, displaying error messages when user input does not fall within parameters, using in-line comments, and appropriate naming conventions. Following these guidelines will ensure the program is readable and maintainable.
