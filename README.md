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
