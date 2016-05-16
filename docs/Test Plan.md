# Test Plan: home-run                                 Date: 05/1/16
>Prepared by: 
Erik karlsson: Product owner
Jesse Mazzella: Scrum Master
Daniel Phan
Sepehr Raissian

### TABLE OF CONTENTS
--------
Section | Name
------- | ------
1.0 | INTRODUCTION
1.1 | Organization 
2.0 | OBJECTIVES AND TASKS
2.1 | Objectives
2.2 | Tasks
3.0 | SCOPE
3.1 | General
3.2 | Tactics of Verification & Validation
4.0 | Testing
4.1 | General
4.2 | Tools
4.3 | Unit Testing
5.0 | Hardware Requirements
6.0 | Environment Requirements
6.1 | Roles
6.2 | Workstation
7.0 | Test Schedule



## 1.0 INTRODUCTION
This program is a friendly user interface application that allows baseball fans to plan their dream vacation to major league baseball stadiums. Baseball fans can purchase souvenir’s along the trip. The application also has administrator account. The program is intended to run smoothly/efficient and data be consistence.

###1.1 Organization
__Stage 1__: Planning and Requirement Analysis.
__Stage 2__: Defining Requirements.
__Stage 3__: Designing the product architecture.
__Stage 4__: Building or Developing the Product. 
__Stage 5__: Testing the Product.
__Stage 6__: Deployment in the Market and Maintenance.

### 2.0 OBJECTIVES AND TASKS
#### 2.1 Objectives
1. Admin has its own private account with root privilege.
2. Admin can modify the stadium attributes.
3. Admin can add new teams and their corresponding stadiums.
4. Admin can add,remove and change available souvenirs and their prices.
5. Propagate stadiums in a plan trip view
6. Stores the distances between stadiums in a data base.
7. Baseball fans can track their souvenir purchases and view the total cost when planning a trip.
8. Baseball fans can plan a trip with the shortest distance starting at Dodger stadium and visiting     every other stadiums.
9. Baseball fans can view the total revenue of each stadiums on a trip plus the grand total for all     stadiums.
10. Baseball fans can plan a trip to all major stadiums with the shortest route.
11. Baseball fans can plan a custom trip.
12. Baseball fans can view the information of any particular baseball stadiums.
13. Baseball fans view a sorted list of stadiums.
14. Provides the ability to view stadiums sorted by park typology.

### 2.2 Tasks
####__[Story #]__ - Description

__[#2]__ - Changes are persistent between executions of the program.

__[#2]__ - Stadium attributes can only be modified to valid data.

__[#2]__ - Confirmation is required before any modification is made to the persistent database.

__[#12]__ - Somewhere in the program the fan has the ability to view all related data for the baseball stadiums.

__[#12]__ - Baseball fan can view souvenirs for each stadium, including item name and price.

__[#12]__ - Verify that tables are not editable.

__[#12]__ - Verify last column stretches to end of table.

__[#13]__ - Major League stadiums

__[#13]__ - sorted by stadium name

__[#13]__ - sorted by team name

__[#13]__ - American League stadiums

__[#13]__ - sorted by team name

__[#13]__ - National League stadiums

__[#13]__ - sorted by team name

__[#13]__ - All stadiums with a grass surface

__[#13]__ - sorted by team name

__[#13]__ - All stadiums

__[#13]__ - sorted chronologically by date opened

__[#13]__ - sorted by seating capacity

__[#13]__ - sorted by park typology 

__[#13]__ - Verify strings are sorted alphabetically

__[#13]__ - If displaying in tables, make sure tables are not editable.

__[#1]__ - Admin can log in by entering a password

__[#1]__ - Upon successful login, admin-only functions are activated. 

__[#1]__ - This can be an admin-only area of the UI or admin functions can integrate with normal UI (i.e: secret buttons appear, features change) 

__[#1]__ - Verify bad passwords do not grant admin access.

__[#1]__ - Test limit of characters in text box for password login.

__[#5]__ - Display check box feature.

__[#5]__ - Display stadium name.

__[#5]__ - display team name.

__[#5]__ - Added stadiums should appear in order the list.

__[#5]__ - Removed stadiums should not appear in the list.

__[#5]__ - user should have an option to use which typology to be sorted.

__[#5]__ - no duplicate stadiums should exist.

__[#5]__ - change of typology  should only be accessible to administrator.

__[#6]__ - Data to be persistent.

__[#6]__ - Data Saves between executions.

__[#6]__ - Data can be accessible to baseball fans undirected method.

__[#6]__ - Data can only be directive accessible to the administrator.

__[#6]__ - Stores the data/distances in a a from of vertex form corresponding to their ID’s.

__[#6]__ - If a stadium is removed from the stadium list, its corresponding distances should also be removed.

__[#7]__ - Fan can purchase souvenirs at each stadium on their trip

__[#7]__ - Fan can view purchases and grand total at end of trip planning

__[#7]__ - Verify that total amount spent is correct at the end of the trip planning.

__[#7]__ - Verify that total amount spent at each stadium is correct.

__[#3]__ - Admin can log in and access add stadium function or window

__[#3]__ - Changes to database are persistent between executions

__[#3]__ - Admin is presented with confirmation dialog before stadium is added or deleted

__[#3]__ - Alterations to data are only performed once a button is pushed (save changes)

__[#3]__ - Verify all data is valid

__[#3]__ - Verify that text fields have a character cap (i.e. user cannot enter in 25015 characters and set that as the stadium name. Field lengths must have reasonable values)

### 3.0 SCOPE

1. General
    1. Performance
    2. Persistence
    3. Data structure
    4. Efficiency
    5. Functionality
    6. Interface
    7. Delegate UI design

3.2 Tactics of Verification & Validation


__Verification__

__Validation__

1
>Are you building it right?

>Are you building the right thing?

2
>Ensures that the software system meets all the functionality.

>Ensures that the functionalities meet the intended behavior.

3
>Verification takes place first and includes the checking for documentation, code, etc.

>Validation occurs after verification and mainly involves the checking of the overall product.

4
>Done by developers.

>Done by testers.

5
>It has static activities, as it includes collecting reviews, walkthroughs, and inspections to verify a software.

>It has dynamic activities, as it includes executing the software against the requirements.

6
>t is an objective process and no subjective decision should be needed to verify a software.

>It is a subjective process and involves subjective decisions on how well a software works.

### 4.0 TESTING
#### 4.1 General
1. Performance: Analysis of big-O notation
    
2. Persistence:
    a. Data is saved to Sqlite database and is retrieval between executions. 
3. Data structure:
    a. Dijkstra's algorithm to compute shortest distance.
    b. Prim's algorithm for MST.
    c. Splay tree to retrieve the same data. 
    d. Heap to retrieve the smallest desirable data.
4. Efficiency:
    Appropriately use the correct data structure for maximum efficiency.  
5. Functionality:
    a. Source code works and corresponds correctly.
    b. Classes, Methods/Functions, variables are named properly and meaningful corresponding to     their desired functionality.
6. Interface:
    a. Buttons do what is intended for.
    b. Buttons designed for baseball fans should only be presentable to them.
    c. Buttons designed for administrator should only be presentable to them.
    d. Tables are formated correctly and words don’t overlap each other.
7. Delegate UI design
    a. Buttons are labeled correctly for their intended use.
    b. Buttons are sized appropriately and proportion to the current page.
    c. Color schemes are chosen carefully so widgets/buttons/backgrounds are clearly presentable.
    d. Use of too many unrelated colors are discouraged.
    

#### 4.2 Tools

1. Continuous Integration
2. QT Debugger
3. trarvis

#### 4.3 Unit testing

1. Admin has its own private account with root privilege.

    a. Upon successful login, admin-only functions are activated. 
    This can be an admin-only area of the UI or admin functions can integrate with normal UI (i.e: secret buttons appear, features change) 

    b. Verify bad passwords do not grant admin access.

    c. Test limit of characters in text box for password login.
    
    * Error handling:
        * user-name and password should be captured with string
    * Security:
        
        * Preventing brute force by applying limited redo password trial.
        
        * SQL injection free by using prepare statements.

        * Encrypted password.

2. Admin can modify the stadium attributes.

    a. Changes are persistent between executions of the program.
        
        Modified attributes such as stadium name,turf type, capacity.

    b. Stadium attributes can only be modified to valid data.
        
        Irreverent data cannot be processed, such as inserting numbers to turf type.

    c. Confirmation is required before any modification is made to the persistent database.

3. Admin can add new teams and their corresponding stadiums.

    a. Admin can log in and access add stadium function or window

    b. Changes to database are persistent between executions

    c. Admin is presented with confirmation dialog before stadium is added or deleted

    d. Alterations to data are only performed once a button is pushed (save changes)

    e. Verify all data is valid

    f. Verify that text fields have a character cap (i.e. user cannot enter in 25015 characters and set that as the stadium name. Field lengths must have reasonable values)

4. Admin can add,remove and change available souvenirs and their prices.
    
    a. Upon successful login admin is granted access to special functions or a special area of the program and can perform admin duties 
    
    b. Admin can view list of souvenirs per stadium
    
    c. Admin can add, remove or change item names and prices.
    
    d. Before performing any action a confirmation dialog is presented to the admin to protect against accidental deletions or additions. 
    
    e. Changes to the data are persistent between executions.

5. Propagate stadiums in a plan trip view

    a. Display check box feature.

    b. Display stadium name.

    c. display team name.

    d. Added stadiums should appear in order the list.

    e. Removed stadiums should not appear in the list.

    f. user should have an option to use which typology to be sorted.

    g. no duplicate stadiums should exist.

    h. change of typology  should only be accessible to administrator.

6. Stores the distances between stadiums in a data base.

    a. Data to be persistent.

    b. Data Saves between executions.

    c. Data can be accessible to baseball fans undirected method.

    d. Data can only be directive accessible to the administrator.

    e. Stores the data/distances in a a from of vertex form corresponding to their ID’s.

    f. If a stadium is removed from the stadium list, its corresponding distances should also be removed.

7. Baseball fans can track their souvenir purchases and view the total cost when planning a trip.

    a. Fan can purchase souvenirs at each stadium on their trip

    b. Fan can view purchases and grand total at end of trip planning
    
    c. Verify that total amount spent is correct at the end of the trip planning.
    
    d. Verify that total amount spent at each stadium is correct.
8. Baseball fans can plan a trip with the shortest distance starting at Dodger stadium and  visiting every other stadiums.
    
    a. Choses the shortest path after Dodger stadium.

9. Baseball fans can view the total revenue of each stadiums on a trip plus the grand total     for all stadiums.
    
    a. Individual revenue is persistently updated and retrievable.
    
    b. Total grand total revenue is retrievable and calculated upon request.

10. Baseball fans can plan a trip to all major stadiums with the shortest route.
    
    a. Using MST, baseball fan are given the shortest route to the surrounding stadiums based on the current location.

11. Baseball fans can plan a custom trip.
    
    a. Custom trip should only be applicable to the current existing stadiums in the data           base.
    
    b. Other executions such as purchasing souvenir’s should accessible and persistent.
    
    c. Baseball fans can change their custom trip at any given time.

12. Baseball fans can view the information of any particular baseball stadiums.
    
    a. Somewhere in the program the fan has the ability to view all related data for the            baseball stadiums.
    
    b. Baseball fan can view souvenirs for each stadium, including item name and price.
    
    c. Verify that tables are not editable.
    
    d. Verify last column stretches to end of table.

13. Baseball fans view a sorted list of stadiums.
    
    a. Major League stadiums 
    
    b. Sorted by stadium name 
    
    c. Sorted by team name
    
    d. American League stadiums
    
    e. Sorted by team name 
    
    f. National League stadiums 
    
    g. Sorted by team name 
    
    h. All stadiums with a grass surface 
    
    i. Sorted by team name 
    
    j. All stadiums 
    
    k. sorted chronologically by date opened 
    
    l. sorted by seating capacity 
    
    m. sorted by park typology 
    
    n. Verify strings are sorted alphabetically
    
    o. If displaying in tables, make sure tables are not editable.

14. Provides the ability to view stadiums sorted by park typology.

    a. Properly listed the stadiums sorted in a formated table.

    b. Table isn’t editable.

### 5.0 HARDWARE REQUIREMENTS
Computers:
__Jesse__: i5 Processor, 8 GB Ram

__Erik__: i7 Processor, 16 GB Ram

__Daniel__: i5 Processor, 8 GB Ram

__Sepehr__: i5 Processor, 8 GB Ram

### 6.0 ENVIRONMENT REQUIREMENTS

__Jesse__: Arch Linux

__Erik__: Mac OSX

__Daniel__: Windows 10

__Sepehr__: Linux(Ubuntu)

### 6.1 Roles

__Jesse__: GUI Interface windows and data base.

__Daniel__: GUI Interface design and functionality.

__Erik__: Data Structures implementation and data structures.

__Sepehr__: Testing suit and data structures

### 6.2 Workstation

QT
Github
Waffle
Slack
Doxygen

### 7.0 TEST SCHEDULE
Sprint 1 –  April 8th – April 18th :

* Data and Database Integrity Testing

* Data Structures Testing

Sprint 2 –  April 18th – May 2nd :

* Data and Database Integrity Testing

* Load Testing

* Data Structures  Testing

* GUI Interface Testing

Sprint 3 –  May 2nd  - May 16th :

* Data and Database Integrity Testing

* User Interface Testing

* Function Testing

* Data and Database Integrity Testing

* Load Testing

* GUI Testing
