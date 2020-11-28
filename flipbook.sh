input_file=$1
output_file=$2
make clean && make
./flipbook $input_file
rm -f $output_file
cat frame*.png | ffmpeg -f image2pipe -framerate 5 -i - -c:v libx264 -vf format=yuv420p -r 25 -movflags +faststart $output_file
rm -f frame*.png
