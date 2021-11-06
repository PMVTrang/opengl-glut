# Cài đặt OpenGL trên win 10

> Copy from teacher's material. Don't know the exact source. Will add if find out.<br>
Only for DevC.<br>
I hate DevC.<br>
Will try to make it to VSCode or Clion later se ho tempo.


These steps will install the free compiler Dev c++ and the free graphics library OpenGL on Windows 8 64 bit OS. If you have 32bit, I believe you add the glut32.dll to the system32 folder.
<br>
Dưới đây là các bước để cài đặt IDE DevC cùng với thư viện đồ họa OpenGL trên Window 64bits.

Link download Dev c++: http://www.mediafire.com/download/jvca73gqgg0l783/Setup_DEVC+++5.4.1.rar

Link download glutming: http://chortle.ccsu.edu/Bloodshed/glutming.zip

## Install DevC
Use the exact version in the link above to avoid any troublesome problem because i just follow the tutorial i dont know anything huihuihui.<br>
Giải nén cái file DevC kia rồi install. Dùng cái bản trên kia cho chắc ăn, hình như hồi bắt đầu setup có mấy người dùng devc bản khác xong không cài được loạn xị ngầu lên.

## Unzip glutming 
Giải nén glutming.

Copy files ... into ...:
- glut.h -> Dev-Cpp\MinGW32\include\GL
- libglut32.a -> Dev-Cpp\MinGW32\lib
- glut32.dll -> C:\Windows\SysWOW64

copy vào linker của DevC
`-lglu32 -lglut32 -lopengl32`

## Run test program
If a window shows up with some shapes on it -> ok.
