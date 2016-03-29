[![Stories in Ready](https://badge.waffle.io/home-run/subtle-cosmic-moose.svg?label=ready&title=Ready)](http://waffle.io/home-run/subtle-cosmic-moose) 

~/run (HOME RUN)
An application for planning a baseball fan's dream vacation.
--------
###Git flow and branching scheme
1. **Always** branch from ``develop``.
2. Branch naming scheme is defined as such:
    - ``<issue number>-brief-description``
    - For example, [issue #1 is to create a README file](https://waffle.io/home-run/subtle-cosmic-moose/cards/56fa022814437c0e00ba6c1e), so my branch name is ``1-readme``.
3. Include a '#' followed by the issue number in every commit.
    - For example, commits to this branch will look like this: ``[#1] Added stuff to readme.``
4. Never work on a branch without an associated issue. If you don't see the issue on waffle, create one.
5. Always push a branch immediately after creating it. This is to correctly update issues on waffle, and also to let other teammates know what you're working on.
6. Pull-requests must be reviewed by all members of the team before they are approved for merge.
7. Delete the feature branch once a pull-request is merged.

###A mini command-line git tutorial (for our purposes for this project)
0. Clone the repo.
    - ``git clone https://github.com/home-run/subtle-cosmic-moose.git``
    - ``cd subtle-cosmic-moose``
1. Switch to branch ``develop``.
    - ``git checkout develop``
2. Make sure to do a ``git pull`` before branching, so you always have up-to-date code.
3. Create/switch to your branch. (This one command does both.) 
    - ``git checkout -b 66-a-brief-description``
4. Push the newly created branch.
    - ``git push -u origin 66-a-brief-description``
5. Start coding!
6. Add your changes to the staging area to prepare for a commit.
    - ``git add my_new_file.cpp`` for files that don't exist on the repo yet.
    - ``git add -u`` for files that already exist on the repo that have been updated.
7. Make a commit. Make sure to include '#' followed by your issue number somewhere in the commit message.
    - ``git commit -m "[66] Mashed keys until it compiled. Don't bother testing it. It's fine, I swear."``
8. Push your changes.
    - If you used the command in **step 4**, this is simply ``git push`` (The ``-u`` flag sets the upstream so you don't have to explicitly set it for every push).
    - Otherwise, the command is ``git push origin 66-a-brief-description``
9. Drink more coffee. :coffee:

###A Brief Doxygen Style Guide
**note:** *ALL code must be doxygen commented.* **If your code isn't commented, it will not be approved for merge.**

**In QT, typing**
``/** + return`` **above a declaration will produce a doxygen comment block.**

Full commenting manual can be found [here](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html).

#### Things to note about Doxygen comments
* Comments can come before the code item.
* For class members and parameters they may also come after them.
* They may be either brief (one line) or detailed or both.
* Put the reference documentation type comments (class and method descriptions) **in the .h file** and *not* in (or, at least, in addition to) the .cpp files. 

#### Brief comment before
Add an extra "/"


```
/// This method does something
void DoSomething();
```


#### Detailed comment before
Add an extra "*"


```
/** This is a method that does so
  * much that I must write an epic 
  * novel just to describe how much
  * it truly does. */
void DoNothing();
```


- the intermediate leading "*"s are optional.

#### Brief comment after
Add an extra "/<"


```
void DoSomething(); ///< This method does something
```


### Detailed comment after
Add an extra "*<"


```
void DoNothing(); /**< This is a method that does so
  * much that I must write an epic 
  * novel just to describe how much
  * it truly does. */
```


- the intermediate leading "*"s are optional.

#### Example .h file
Below is a full example.


```
/**
 * \class ExampleClass
 *
 * \brief Provide an example
 *
 * This class is meant as an example.  It is not useful by itself
 * rather its usefulness is only a function of how much it helps
 * the reader.  It is in a sense defined by the person who reads it
 * and otherwise does not exist in any real form. 
 *
 * \note Attempts at zen rarely work.
 *
 * \author (last to touch it) $Author: bv $
 *
 * \version $Revision: 1.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: bv@bnl.gov
 *
 * Created on: Wed Apr 13 18:39:37 2005
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */

#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H

class ExampleClass
{

public:

    /// Create an ExampleClass
    ExampleClass();

    /// Create an ExampleClass with lot's of intial values
    ExampleClass(int a, float b);

    ~ExampleClass();

    /// This method does something
    void DoSomething();

    /** This is a method that does so
      * much that I must write an epic 
      * novel just to describe how much
      * it truly does. */
    void DoNothing();

    /** \brief A useful method.
      * \param level an integer setting how useful to be
      * \return Output that is extra useful
      * 
      * This method does unbelievably useful things.  
      * And returns exceptionally useful results.
      * Use it everyday with good health.
      */
    void* VeryUsefulMethod(bool level);

private:

    const char* fQuestion; ///< the question
    int fAnswer;           ///< the answer 

};                              // end of class ExampleClass

#endif  // EXAMPLECLASS_H
```

