# fs-cpp
a simple file system that can create, delete, read and write a file

  **Output**
  <p align="center">
<img src="https://cloud.githubusercontent.com/assets/3256544/15572473/b83f9ffe-22f5-11e6-95e3-b86f9303ebb1.png" width="680">
</p>

  **Results**

In this driver.cpp program I demonstrated some of the functions on the file system, I started out with writing a file and writing to a file, then I showed what’s in the file by calling it `cat` (like in Linux) by changing all the ASCII codes to characters, after, I listed the files in the directory by calling it `ls` (like in Linux), later I printed the clusters using the first cluster address. I repeated this process for all 4 files. We have 1024 Bytes max, which means when we try to add a file that is greater than the free space it doesn’t create it, I showed that when adding file4, we see that the write function returned false and showed “can’t make file” and when I `ls` the directory, it doesn’t show. Then I deleted file2 and `ls` the directory to show it deleted it. I used the GCC GNU compiler to test and simulate this project.
