
g++ -c avatar.cpp main.cpp -DDX_GCC_COMPILE --exec-charset=cp932

@cd _network

g++ -c network.cpp netfunc.cpp -DDX_GCC_COMPILE -O2 --exec-charset=cp932

@cd ..

@cd fileRW

g++ -c readSetupfile.cpp -DDX_GCC_COMPILE -O2 --exec-charset=cp932

@cd ..

g++ avatar.o main.o _network/network.o _network/netfunc.o fileRW/readSetupfile.o -O2 -static -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt

@cd network

@del host.o
@del client.o
@del network.o

@cd ..

@cd fileRW

@del readSetupfile.o

@cd ..

@del main.o
@del avatar.o
