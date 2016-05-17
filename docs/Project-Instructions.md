# Take Me Out the Ballgame

>A list of all major league baseball stadiums resides at http://en.wikipedia.org/wiki/List_of_Major_League_Baseball_stadiums.  A list of all the major league baseball teams reside at http://mlb.com.  Your software team is to write a program that stores this data in a suitable data structure.  (map, vector, list, heap, BST, tree, etc.) Your application will allow baseball fans to plan their dream vacation.

The initial souvenir list is a follows:

a.  Baseball cap            $23.99
b.  Baseball bat            $45.39
c.  Team pennant            $15.99
d.  Autographed baseball    $19.99
e.  Team jersey             $85.99

Requirements:

1.  Write at least 10 agile stories (including description, tasks, test scenarios, and story points) before any software development.
2.  You should create a list of the major league stadiums by name in alphabetical order.
3.  You should create a list of major league stadiums sorted by team name.
4.  You should create a list of American League stadiums sorted by team name.
5.  You should create a list of National League stadiums sorted by team name.
6.  You should create a list of stadiums that have a grass surface sorted by team name.
7.  You should create a list of stadiums in chronological order by date opened
8.  You should create a list of stadiums sorted by seating capacity.
9.  You should create a list of stadiums sorted by park typology.

Planning a vacation:

1.  Design trips to visit each major league stadium travelling the shortest distance starting at Dodger stadium using Dijkstra’s algorithm (note: each trip begins at Dodger stadium).
2.  Provide the capability for a baseball fan to plan his/her dream vacation by allowing a baseball fan to choose their starting stadium and all the other stadiums they would like to visit.   Determine the order the stadiums will be visited. Use Dijkstra’s algorithm to calculate the shortest distance for this dream vacation.
3.  Determine the minimum spanning tree (MST) connecting all the major league stadiums using Prim’s or Kruskal’s algorithm. Calculate the associated mileage.
4.  Provide the capability to track souvenirs purchased by the baseball fans on their trips and the corresponding costs. 
5.  Output the total revenue for each stadium including a grand total for all the stadiums.
6.  Provide the ability to modify stadium information if a team moves into a new stadium. (administrator only) (Atlanta Braves are planning to move to a new stadium in 2017).
7.  Provide the ability to add a new team and corresponding stadium if major league baseball decides to add new teams. (administrator only)
8.  You should be able to randomly access any baseball stadium. 
9.  You should be able to modify (add/delete/change) the souvenirs list and their prices. (administrator only) 

Please let me know your partners by March 28nd (three points will be deducted from your score if you do not meet this deadline). All projects are due by May 16th.   No late projects will be accepted.  Your team must demonstrate your project to me before it will be graded.   Each teammate must identify their accomplishments on the project. Not all team members will necessarily earn the same score.

1.  Design a very readable, easy to use interface to demonstrate your program.  
2.  Use a map to store the stadiums or the souvenirs. 
3.  Contingency handling should include addressing invalid input. 
4.  Write at least 10 agile stories (including description, tasks, test scenarios, and story points) before any software is developed.  The team must follow the Scrum process (the Scrum master must document all meetings and the product owner must document the backlog).
5.  Submit a UML class diagram, at least three use cases, and at least three state diagrams with your project.
6.  Submit a test plan.
7.  All changes must be persistent between executions. 
8.  Submit a paragraph discussing the Big-Oh of your project. Identify all the data structures used. 
9.  Each team must use a version control system, graphical user interface tool, automated documentation tool, and an Agile management tool. (GITHUB, DOXYGEN, WAFFIO.IO, QT, etc.)




The assignment will be graded using the following scale:

Description | Value
----------- | --------
First checkpoint    |   4
Second checkpoint   |   4
Meet requirements   |   13
Coding Style        |   2
Use of multiple C++ data structures (1 point per data structure)   | 3
User interface      |   2
Contingency handling |   2
Test Plan           |   3
UML + DOXYGEN       |   3
Adherence to Scrum  |   2
Identification of Big Oh |  2
__Total__  | 40


__Schedule__:
First checkpoint – April 18th – 5 points
Second checkpoint – May 2nd – 5 points
Final checkpoint – May 16th – 30 points

__Stadiums Data Format__
The information is in the following format:
- Stadium Name
- Team Name
- Street Address
- City, State, Zip
- Box Office #
- Date Opened
- Seating Capacity
- Surface


# League Information
## AMERICAN LEAGUE TEAMS:
-----------------------------

Angels Stadium of Anaheim
Los Angeles Angels of Anaheim
2000 E Gene Autry Way, 
Anaheim, CA 92806
(714)940-2000
Opened – April 19, 1966
Capacity – 45,957
Grass

    
Comerica Park
Detroit Tigers
2100 Woodward Ave, 
Detroit, MI 48201
(313) 962-4000 
Opened – April 11, 2000
Capacity – 41,547
Grass


Fenway Park
Boston Red Sox
4 Yawkey Way, 
Boston, MA 02215
(877) 733-7699 
Opened – April 20, 1912
Capacity – 37,673  
Grass


Globe Life Park in Arlington
Texas Rangers
1000 Ballpark Way,
Arlington, TX 76011
(817) 273-5222 
Opened – April 1, 1994
Capacity – 48,114
Grass


Kauffman Stadium
Kansas City Royals
1 Royal Way
Kansas City, MO 64129
(816) 921-8000
Opened – April 10, 1973
Capacity – 37,903 
Grass


Minute Maid Park
Houston Astros
501 Crawford St,
Houston, TX 77002
(713) 259-8000
Opened - March 30, 2000
Capacity – 421,574
Grass

 

O.co Coliseum
Oakland Athletics
7000 Coliseum Way
Oakland, CA 94621
(510) 569-2121
Opened - September 18, 1966
Capacity – 35,067
Grass



Oriole Park at Camden Yards
Baltimore Orioles
333 West Camden Street
Baltimore, MD 21201
(410) 685-9800
Opened - April 6, 1992
Capacity – 45,971
Grass



Progressive Field
Cleveland Indians
2401 Ontario Street
Cleveland, OH 44115
(216) 420-4487
Opened - April 2, 1994
Capacity – 37,675
Grass



Rogers Centre
Toronto Blue Jays
1 Blue Jays Way
Toronto, Ontario, Canada M5V1J3
+1 416-341-1000
Opened - June 3, 1989
Capacity - 49,282
Astro turf


SafeCo Field
Seattle Mariners
1516 First Avenue South
Seattle, WA 98134
(206) 346-4000
Opened - July 15, 1999
Capacity - 47,574
Grass



Target Field
Minnesota Twins
353 N 5th St
Minneapolis, MN 55403
(800) 338-9467
Opened - April 12, 2010
Capacity - 39,021
Grass

Tropicana Field
Tampa Bay Rays
1 Tropicana Dr
St. Petersburg, FL 33705
(727) 825-3137
Opened - March 3, 1990
Capacity - 31,042 
Astro turf


US Cellular Field
Chicago White Sox
333 West 35th Street
Chicago, IL 60616
(312) 674-1000
Opened - April 18, 1991
Capacity - 40,615
Grass


Yankee Stadium
New York Yankees
1 E 161st St
South Bronx, NY 10451
(718) 293-4300
Opened - April 16, 2009
Capacity – 49,642
Grass



NATIONAL LEAGUE TEAMS:
--------------------------------

AT&T Park
San Francisco Giants
24 Willie Mays Plaza
San Francisco, CA 94107
(415) 972-2000
Opened - April 11, 2000
Capacity - 41,915
Grass


Busch Stadium
St. Louis Cardinals
700 Clark Street
St. Louis, MO 63102
(314) 345-9600
Opened - April 10, 2006
Capacity – 43,975
Grass


Chase Field
Arizona Diamondbacks
401 East Jefferson Street
Phoenix, AZ 85004
(602) 462-6500
Opened - March 31, 1998
Capacity - 48,519
Grass


Citi Field
New York Mets
126th St. & Roosevelt Ave.
Queens, NY 11368
(718) 507-6387
Opened - April 13, 2009
Capacity - 41,922
Grass


Citizens Bank Park
Philadelphia Phillies
1 Citizens Bank Way
Philadelphia, PA 19148
(215) 463-1000
Opened - April 3, 2004
Capacity - 43,651
Grass


Coors Field
Colorado Rockies
2001 Blake St
Denver, CO 80205
(303) 292-0200
Opened - April 26, 1995
Capacity - 50,398
Grass



Dodger Stadium
Los Angeles Dodgers
1000 Elysian Park Avenue
Los Angeles, CA 90090
(323) 224-1507
Opened - April 10, 1962
Capacity - 56,000


Great America Ball Park
Cincinnati Reds
100 Joe Nuxhall Way
Cincinnati, OH 45202
(513) 381-7337
Opened - March 31, 2003
Capacity - 42,319
Grass



Marlins Park
Miami Marlins
501 Marlins Way
Miami, FL 33125
(305)480-1300
Opened - April 4, 2012
Capacity – 36,742
Grass


Miller Park
Milwaukee Brewers
1 Brewers Way
Milwaukee, WI 53214
(414) 902-4400
Opened - April 6, 2001
Capacity - 41,900
Grass


Nationals Park
Washington Nationals
1500 S Capitol St SE
Washington, DC 20003
(202) 675-6287
Opened - March 30, 2008
Capacity - 41,888
Grass


Petco Park
San Diego Padres
19 Tony Gwynn Drive
San Diego, CA 92101
(619) 795-5000
Opened - April 8, 2004
Capacity – 41,164
Grass



PNC Park
Pittsburgh Pirates
115 Federal St
Pittsburgh, PA 15212
(412) 321-2827
March 31, 2001
Capacity - 38,362
Grass

Turner Field 
Atlanta Braves
755 Hank Aaron Drive
Atlanta, GA 30315
(404) 522-7630
Opened - March 29, 1997
Capacity - 49,586
Grass


Wrigley Field
Chicago Cubs
1060 West Addison Street
Chicago, IL 60613
(773) 404-2827
Opened - April 23, 1914
Capacity - 42,495
Grass
