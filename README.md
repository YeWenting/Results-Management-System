# Results-Management-System
This is my work of "C++ Course Design II" in BUPT.

**There is a makefile in the code folder for non-xcode user**

To develop this system, I designed three esstial classes, called "Person", "Course" and "System". On the purpose of encapsulation and security, I implemented "System" class with singleton pattern, by smart pointer rather than normal pointer, which is concise and effective.

To realize the network function with multi-clients, I have tried many ways. In the end I chooose the simplest way, using the "Linux" API "select" to manage different client/socket. I decoupled the many functions in the C/S model. To avoid the important infomation being stolen, many effort has been paid. 

*For more details about the program, you can download the report, which is a ".pdf" file at the root dictionary:)*
