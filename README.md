Michael Catalanotti
CSC 343
Assignment 6
4/1/25

Explain why Windows, Linux, and Solaris implement multiple locking mechanisms. Describe the circumstances under which they use spinlocks, mutex locks, semaphores, adaptive mutex locks, and condition variables. In each case, explain why the mechanism is needed.

Locking mechanisms were created by OS companies like Windows and Linux to optimize performance and security in concurrent processing. 

Spinlocks are used in kernel mode to avoid overhead caused by context switching and used when a thread can not be put to sleep. This protects resources from prematurely being accessed.
Mutex locks (mutual exclusion) are used for ensuring only one thread accesses a critical section at a time. Unlike spinlocks, mutexes put threads to sleep if the lock is unavailable, reducing CPU waste.
Semaphores facilitate synchronization amongst threads and processes, essentially, they are used to limit access to shared resources and send messages amongst threads/processes when a resource is available
Adaptive mutex locks implement spinlocks to control access to resources amongst threads. When a thread has a mutex, only the owner can release the lock. In effect, this reduces system overhead, if a thread sends an interrupt, the OS will check is the mutex is locked before releasing resources. If the thread is running, it will repeatedly check until the thread is free, otherwise if inactive, the OS will context switch. 
Condition variables, used with mutexes, are variables that optimize thread coordination by using conditionals to check whether or not a thread can proceed. Namely, these are often seen with producer/consumer relationships. 

Explain why spinlocks are not appropriate for single-processor systems yet are often used in multiprocessor systems.
In single processor systems (SPS), only one thread can execute at a time. With spinlocks, when a thread is attempting to acquire a spinlock in use, the thread will go into a loop of waiting to check if the lock is acquirable. In effect, using spinlocks in SPS would greatly decrease processing performance. Alternatively, spinlocks can be used reliably in multiprocessor systems–with more processors available, spinlocks can be released by another processor and the thread can continue on to processing. 

In Section 6.4, we mentioned that disabling interrupts frequently can affect the system’s clock. Explain why this can occur and how such effects can be minimized.
		
		The system clock of an OS accounts for timekeeping and synchronisation across the system. To maintain time, the system clock receives timer interrupts that will update the clock. Consequently, disabling interrupts will inevitably slow down the system clock and cause the system to lag behind on time. Spinlocks and mutexes are two approaches to reduce improper system clock synchronization. Generally, spinlocks are used for a short duration–instead of putting a thread to sleep, it allows the thread to continually check spinlock availability… because they do not disable interrupts, this is a good technique to minimize variation in the clocks pace. Similarly, mutexes can be used to block and sleep threads, preventing the disabling of interrupts. Traditionally, shorter processes benefit from using spinlocks, where mutexes are more efficient in longer processes. 
