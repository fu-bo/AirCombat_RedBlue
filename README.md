# AirCombat Red & Blue

A cute air combat game. The main mechanism: "red" and "blue" vanish when meeting each other.

It is a C++ programming exercise as it is written from scratch using only OpenGL and there is no advanced data structure involved.

The librararies yssimplesound and fssimplewindow are from Dr. Soji Yamakawa at http://ysflight.in.coocan.jp/.

<a href="https://youtu.be/-Ko-MaB1-nA"><img src="./thumbnail/aircombat_redblue_thumbnail.png" alt="cla" width="233" height="300" border="50"/></a>
<a href="https://youtu.be/-Ko-MaB1-nA"><img src="./thumbnail/aircombat_redblue_thumbnail1.png" alt="cla" width="233" height="300" border="50"/></a>
<a href="https://youtu.be/-Ko-MaB1-nA"><img src="./thumbnail/aircombat_redblue_thumbnail2.png" alt="cla" width="233" height="300" border="50"/></a>

# Instructions for the Game
'esc':    exit

'up':     up

'down':   down

'left':   left

'right':  right

'space':  shoot

'a':      big shoot

# Build and Run the Project
## In MAC OS
If you have CMake,
```bash
mkdir build
cp -r data build
cd build
cmake ..
make
mkdir -p game.app/Contents/MacOS
mv game_main game.app/Contents/MacOS/exe
./game.app/Contents/MacOS/exe
```

If you do not have CMake, you can also do
``` bash
mkdir build
cp -r data build
cp -r include/ build
cp -r src/ build
cp fssimplewindow/macosx/* build
cp yssimplesound/yssimplesound.cpp build
cp yssimplesound/yssimplesound.h build
cp yssimplesound/macosx/* build
cd build
clang -c fssimplewindowobjc.m
clang -c yssimplesound_macosx_objc.m
mkdir -p game.app/Contents/MacOS
g++ -std=c++11 yssimplesound.cpp yssimplesound_macosx_cpp.cpp yssimplesound_macosx_objc.o fssimplewindowcpp.cpp fssimplewindowobjc.o Bullet.cpp ColorFunction.cpp ColorQuad.cpp Common.cpp ColorCircle.cpp ColorObj.cpp Colored.cpp StringPaser.cpp main.cpp -framework Cocoa -framework OpenGL -o game.app/Contents/MacOS/exe
./game.app/Contents/MacOS/exe
```
## In Linux
You can build in linux as follows. But the audio might not function normally. And the aircrafts do not have outlines.
```bash
mkdir build
cp -r data build
cd build
cmake ..
make
./game_main
```

# Audio Files Attribution
All the audio files used in this project are are copyright free under "Personal Use" or "Attribution 3.0".

1. Click-SoundBible.com-1387633738			    http://soundbible.com/783-Click.html		    Attribution 3.0
2. Click2-Sebastian-759472264.wav			    http://soundbible.com/1705-Click2.html		    Attribution 3.0
3. Bomb 2-SoundBible.com-953367492.wav		    http://soundbible.com/476-Bomb-2.html		    Personal Use Only
4. Water Splash-SoundBible.com-800223477.wav	http://soundbible.com/1460-Water-Splash.html	Attribution 3.0
5. Upper Cut-SoundBible.com-1272257235.wav		http://soundbible.com/993-Upper-Cut.html	    Attribution 3.0
6. Ta Da-SoundBible.com-1884170640			    http://soundbible.com/1003-Ta-Da.html		    Attribution 3.0
