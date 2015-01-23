# clear
rm *.bin *.img *.o

# compile
nasm boot.asm -f bin -o boot.bin
gcc -m32 -ffreestanding -c main.c -o main.o
gcc -m32 -static -nostartfiles -c video.c -o video.o
gcc -m32 -static -nostartfiles -c ports.c -o ports.o

# link
ld -melf_i386 -N -Ttext 0x01000 -e0x01000 -o kernel.o main.o video.o ports.o

# magic
objcopy -R .note -R .comment -S -O binary kernel.o kernel.bin

# combine
BOOT_SIZE=$(stat -c %s boot.bin)
KERNEL_SIZE=$(stat -c %s kernel.bin)
SUM_SIZE=$(($BOOT_SIZE + $KERNEL_SIZE))
DUMMY_SIZE=$(./dummy_size.py $SUM_SIZE)
head -c $DUMMY_SIZE < /dev/zero > tmp

cat boot.bin kernel.bin tmp > kernel.img
rm tmp
