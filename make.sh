gcc -Wall -o square `pkg-config raylib --cflags --libs` ./tilemap/tilemap.c ./player/player.c  ./render/render.c ./misc/dialog/dialog.c