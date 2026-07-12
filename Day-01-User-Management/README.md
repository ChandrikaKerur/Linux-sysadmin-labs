# Day 1: User & Group Management

## Objective
To learn the fundamental Linux commands for creating, modifying, and deleting users and groups.

## Commands Used
- `sudo groupadd developers` - Created a new group called 'developers'.
- `sudo useradd -m -G developers dev1` - Created a user 'dev1' with a home directory and added them to the 'developers' group.
- `sudo passwd dev1` - Set a password for the user 'dev1'.
- `sudo userdel -r dev2` - Deleted the user 'dev2' and their home directory.

## Screenshots
*[You will add your screenshots here after your next lab session]*

## Key Takeaways
- Users are created with `useradd`.
- Groups help manage permissions for multiple users at once.
- The `-r` flag with `userdel` is crucial to remove the user's home directory and avoid leaving orphaned files.

## Challenges Faced
*[You will add any issues you ran into here, like a "Permission Denied" error, and how you fixed them]*
