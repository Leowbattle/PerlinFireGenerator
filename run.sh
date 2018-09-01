gcc main.c
./a.out
ffmpeg -r 30 -i %03d.ppm -pix_fmt yuv420p output.gif
ffmpeg -r 30 -i %03d.ppm -pix_fmt yuv420p output.apng
rm *.ppm
