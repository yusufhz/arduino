#define pin_fb 2
#define pin_ud 3
#define pin_rl 4
#define pin_jp 9

Servo frontback;
Servo updown;
Servo rightleft;
Servo jepit;

int min_fb = 80;
int mak_fb = 160;
int min_ud = 20;
int mak_ud = 110;
int min_rl = 0;
int mak_rl = 180;
int mid_rl = 95;
int min_jp = 50;
int mak_jp = 90;

bool move_fb = 1;
bool move_ud = 1;
bool move_rl = 1;
bool move_jp = 1;
