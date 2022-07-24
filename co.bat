@rem g++ n.cpp -mwindows --exec-charset=cp932
@rem g++ charactor.o main.o -Wl,-subsystem,windows -static -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt

g++ -c main.cpp avatar.cpp iniread.cpp -DDX_GCC_COMPILE -std=c++1z --exec-charset=cp932

@rem g++ character.o main.o IPserver.o -Wl,-subsystem,windows -static -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt
g++ main.o avatar.o iniread.o -static -std=c++1z -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt

@del main.o 
@del avatar.o
@del iniread.o
