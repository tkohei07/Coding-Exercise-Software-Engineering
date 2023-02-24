# Assignment #1 (Point Tracking Program)

 
Description: Create a program that tracks points earned and spent by users. The program reads transactions from a CSV file, spends points based on specific rules, and returns updated payer balances. 

- Enviroment

C++17 compiler (e.g. g++), make 

OS: Linux 

- Usage

To use the program locally, make sure that you have g++ and make installed on your machine. Then, navigate to the directory where the source code is located and run the following commands: 

>make 

>./main [amount of points to spend] [name of CSV file] 

Make sure that the CSV file is in the same directory as the main executable. The program will return the updated payer balances in the command-line. 
To use the program with Docker navigate to the directory where the source code and Dockerfile are located and run the following commands: 

>docker build -t [image-name] . 

>docker run -it -v $(pwd):/app [image-name] bash 

Then, navigate to the directory where the source code is located and run the following commands: 

>make 

>./main [amount of points to spend] [name of CSV file] 
