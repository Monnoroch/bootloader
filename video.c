const unsigned char* SCREEN_ADDR = (unsigned char*) (0xB8000);

const unsigned int SCREEN_WIDTH = 80;
const unsigned int SCREEN_HEIGHT = 25;

const unsigned int INDEX_REGISTER = 0x3D4;
const unsigned int DATA_REGISTER = 0x3D5;


void clrscr() {
	unsigned char* vidmem = (unsigned char*) SCREEN_ADDR;
	const long size = SCREEN_WIDTH * SCREEN_HEIGHT;
	long loop;

	for(loop = 0; loop < size; loop++) {
		*vidmem++ = 0;
		*vidmem++ = 0xF;
	}
	out(INDEX_REGISTER, 14);
	out(DATA_REGISTER, 0);
	out(INDEX_REGISTER, 15);
	out(DATA_REGISTER, 0);
}

void print(const char* _message) {
	unsigned char* vidmem = (unsigned char*) SCREEN_ADDR;
	unsigned short offset;
	unsigned long i;

	out(INDEX_REGISTER, 14);
	offset = in(DATA_REGISTER) << 8;
	out(INDEX_REGISTER, 15);
	offset |= in(DATA_REGISTER);

	vidmem += offset * 2;
	i = 0;
	while(_message[i] != 0) {
		*vidmem = _message[i++];
		vidmem += 2;
	}
	offset += i;
	out(DATA_REGISTER, (unsigned char) (offset));
	out(INDEX_REGISTER, 14);
	out(DATA_REGISTER, (unsigned char) (offset >> 8));
}