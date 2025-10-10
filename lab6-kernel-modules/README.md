# Exercise 1: personalized greetings
Write a Linux kernel module which accepts a string as an input parameter from the command line, containing the name of a person, and prints a message greeting that person.

> **_WARNING:_** when printing to the kernel log terminate the message with \n, otherwise it can happen that it is kept in the buffer and is printed only when you remove the module 

## Requirements
    1) Use the standard init\_module and cleanup\_module functions
    2) Give permission 0644 to the input variables
	3) Document the input parameter, explaining what the module expects
	4) Use GPL as the license for your module 
	5) Create your own Makefile to compile the kernel module

> **_SUGGESTION:_** create a flexible Makefile, so that you can reuse it. Use variables. In make you can customize the value of a variable from the commmand line with make VAR=xxx


# Exercise 2: permissions and parameters
Write a Linux kernel module which periodically prints an integer number. The number must be read from the command line and assigned to a variable.

> **_IMPORTANT:_**  if the module executes a loop you will not be able to remove it. To stop it you will need to reboot Linux. Either you run a loop for a limited amount of cycles or you use an additional command line parameter to conditionally stop the execution. Let's suppose this is called flag. You can initialize flag = 1 and run the loop as while(flag). In the next steps you will see how to modify the parameter at run-time. When you want to stop the execution you can set flag = 0 and the program will exit.

> **_NOTE:_** when the module is loaded and start executing you will not be able to interact with the terminal. Open another one and run the next commands there.

Now let's try to modify the parameter at run-time:

    1) go to /sys/module/ex2/parameters and open the file which correspond to the variable assigned to the command line parameter
    2) Change the numerical value with another one
    3) Check the output of dmesg. Did it change?
    4) What happens if you change the type of the parameter, using a string for example?
	5) What happens if you try to rmmod the module while it is running?
Now try to change the permissions of your variable: instead of giving read/write permissions to the user with 0644, give read-only access using 0444. What happens if you try to repeat steps 1 to 3?

## Requirements
	1) To decide the period of the print use msleep(milliseconds), from <linux/delay.h>, where milliseconds is the amount of milliseconds you want the module to sleep.

# Exercise 3
Write a Linux kernel module which:

    1) takes an array of integers from the command line
    2) compute the sum of the array
    3) returns the obtained sum only when it is removed with rmmod

## Requirements

    1) Raplace init_module and cleanup_module with custom names


# Exercise 4
Write a Linux kernel module to reverse an input string.

> **_WARNING:_** declaring the string as char *str in C creates a string literal, which goes in read-only memory and cannot be modified. However, module_param wants the string declared as a pointer to char (char *str). Find your solution passing a char *str to module_param, but still being able to reverse the string. 

## Requirements
    1) Divide the code into four separated files:
        - init.c for the module initialization
        - exit.c for the module cleanup
        - string_rev.c for the string reverse function
        - string_rev.h to declare the string reverse function
	2) Create a Makefile to compile all the source files
