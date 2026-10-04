# Flash Memory Wear-Leveling Simulator

## 1. Introduction

This project is a Linux-based Flash Memory Wear-Leveling Simulator developed using C.

The system simulates flash memory blocks and distributes write operations among the blocks to reduce uneven wear.

A Linux character device driver is also implemented to demonstrate communication between the user-space application and the Linux kernel.

## 2. Objectives

- Simulate flash memory blocks.
- Implement wear-leveling logic.
- Select the least-used block for writing.
- Track block write counts.
- Communicate with a Linux device driver.
- Store and log write operations.
- Demonstrate layered software architecture.

## 3. Technologies Used

- C
- Linux
- GCC
- Linux Kernel Module
- Character Device Driver
- Makefile
- Linux File System

## 4. System Architecture

User
↓
main.c
↓
Wear-Leveling Module
↓
Flash Management Module
↓
Linux Character Device Driver
↓
/dev/flash_wl

## 5. Wear-Leveling Algorithm

1. Initialize all flash blocks.
2. Receive data from the user.
3. Check the write count of each block.
4. Find the block with the minimum write count.
5. Select that block.
6. Send data to the Linux device driver.
7. Write the data to the selected block.
8. Increase the block's write count.
9. Display the updated block status.

## 6. Project Modules

### main.c
Provides the user interface and menu.

### wear_leveling.c
Contains the wear-leveling algorithm and selects the least-used block.

### flash.c
Manages flash blocks, write operations, storage and logging.

### flash_wl_driver.c
Linux character device driver that creates `/dev/flash_wl` and receives data from the application.

## 7. Software Architecture

The project follows a layered architecture:

User Interface Layer
↓
Application Logic Layer
↓
Flash Management Layer
↓
Device Driver Layer
↓
Linux Kernel

## 8. Output

The simulator displays:

- Selected block
- Write count
- Block validity
- Driver communication status

Example:

Wear leveling selected Block 0
Data sent to Linux device driver
Data written to Block 0

## 9. Advantages

- Reduces uneven distribution of writes.
- Demonstrates basic flash wear-leveling concepts.
- Demonstrates Linux device-driver communication.
- Uses modular C programming.
- Runs completely on Linux.

## 10. Conclusion

The project demonstrates a basic flash memory wear-leveling system using C and Linux.

The system distributes write operations among flash blocks and communicates with a Linux character device driver through `/dev/flash_wl`.
