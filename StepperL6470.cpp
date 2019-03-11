#include <StepperL6470.h>
#include <arduino.h>
#include <SPI.h>

void L6470::setparam_abspos(long val) { this->transfer(0x01, 3, val); }
void L6470::setparam_elpos(long val) { this->transfer(0x02, 2, val); }
void L6470::setparam_mark(long val) { this->transfer(0x03, 3, val); }
void L6470::setparam_acc(long val) { this->transfer(0x05, 2, val); }
void L6470::setparam_dec(long val) { this->transfer(0x06, 2, val); }
void L6470::setparam_maxspeed(long val) { this->transfer(0x07, 2, val); }
void L6470::setparam_minspeed(long val) { this->transfer(0x08, 2, val); }
void L6470::setparam_fsspd(long val) { this->transfer(0x15, 2, val); }
void L6470::setparam_kvalhold(long val) { this->transfer(0x09, 1, val); }
void L6470::setparam_kvalrun(long val) { this->transfer(0x0a, 1, val); }
void L6470::setparam_kvalacc(long val) { this->transfer(0x0b, 1, val); }
void L6470::setparam_kvaldec(long val) { this->transfer(0x0c, 1, val); }
void L6470::setparam_intspd(long val) { this->transfer(0x0d, 2, val); }
void L6470::setparam_stslp(long val) { this->transfer(0x0e, 1, val); }
void L6470::setparam_fnslpacc(long val) { this->transfer(0x0f, 1, val); }
void L6470::setparam_fnslpdec(long val) { this->transfer(0x10, 1, val); }
void L6470::setparam_ktherm(long val) { this->transfer(0x11, 1, val); }
void L6470::setparam_ocdth(long val) { this->transfer(0x13, 1, val); }
void L6470::setparam_stallth(long val) { this->transfer(0x14, 1, val); }
void L6470::setparam_stepmood(long val) { this->transfer(0x16, 1, val); }
void L6470::setparam_alareen(long val) { this->transfer(0x17, 1, val); }
void L6470::setparam_config(long val) { this->transfer(0x18, 2, val); }

long L6470::getparam_abspos() { return this->get_param(0x01, 3); }
long L6470::getparam_elpos() { return this->get_param(0x02, 2); }
long L6470::getparam_mark() { return this->get_param(0x03, 3); }
long L6470::getparam_speed() { return this->get_param(0x04, 3); }
long L6470::getparam_acc() { return this->get_param(0x05, 2); }
long L6470::getparam_dec() { return this->get_param(0x06, 2); }
long L6470::getparam_maxspeed() { return this->get_param(0x07, 2); }
long L6470::getparam_minspeed() { return this->get_param(0x08, 2); }
long L6470::getparam_fsspd() { return this->get_param(0x15, 2); }
long L6470::getparam_kvalhold() { return this->get_param(0x09, 1); }
long L6470::getparam_kvalrun() { return this->get_param(0x0a, 1); }
long L6470::getparam_kvalacc() { return this->get_param(0x0b, 1); }
long L6470::getparam_kvaldec() { return this->get_param(0x0c, 1); }
long L6470::getparam_intspd() { return this->get_param(0x0d, 2); }
long L6470::getparam_stslp() { return this->get_param(0x0e, 1); }
long L6470::getparam_fnslpacc() { return this->get_param(0x0f, 1); }
long L6470::getparam_fnslpdec() { return this->get_param(0x10, 1); }
long L6470::getparam_ktherm() { return this->get_param(0x11, 1); }
long L6470::getparam_adcout() { return this->get_param(0x12, 1); }
long L6470::getparam_ocdth() { return this->get_param(0x13, 1); }
long L6470::getparam_stallth() { return this->get_param(0x14, 1); }
long L6470::getparam_stepmood() { return this->get_param(0x16, 1); }
long L6470::getparam_alareen() { return this->get_param(0x17, 1); }
long L6470::getparam_config() { return this->get_param(0x18, 2); }
long L6470::getparam_status() { return this->get_param(0x19, 2); }


L6470::L6470(const int ss_pin, const int mosi_pin, const int miso_pin, const int sck_pin,
             const int busy_pin, const int alarm_pin, const int reset_pin) {
  _ss_pin = ss_pin;
  _mosi_pin = mosi_pin;
  _miso_pin = miso_pin;
  _sck_pin = sck_pin;
  _busy_pin = busy_pin;
  _alarm_pin = alarm_pin;
  _reset_pin = reset_pin;
}

void L6470::init() {
    pinMode(_ss_pin, OUTPUT);
	pinMode(_mosi_pin, OUTPUT);
	pinMode(_miso_pin, INPUT);
	pinMode(_sck_pin, OUTPUT);
	pinMode(_alarm_pin, INPUT);
	pinMode(_reset_pin, OUTPUT);

	digitalWrite(_ss_pin, HIGH);
	//	
	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV16);
	SPI.setBitOrder(MSBFIRST);

    digitalWrite(_reset_pin, HIGH);
	delay(10);
	digitalWrite(_reset_pin, LOW);
	delay(10);
	digitalWrite(_reset_pin, HIGH);
	delay(10);

	this->reset_device();
	this->reset_device();
}

void L6470::run(int dia, long spd)
{
    if (dia == 1)
        this->transfer(0x51, 3, spd);
    else
        this->transfer(0x50, 3, spd);
}

void L6470::stepclock(int dia)
{
    if (dia == 1)
        this->transfer(0x59, 0, 0);
    else
        this->transfer(0x58, 0, 0);
}

void L6470::move(int dia, long n_step)
{
    if (dia == 1)
        this->transfer(0x41, 3, n_step);
    else
        this->transfer(0x40, 3, n_step);
}

void L6470::go_to(long pos)
{
    this->transfer(0x60, 3, pos);
}

// FIXME: dia=1で動かすと、回転し続ける。 
void L6470::go_to_dia(int dia, int pos)
{
    if (dia == 1)
        this->transfer(0x69, 3, pos);
    else
        this->transfer(0x68, 3, pos);
}

void L6470::go_until(int act, int dia, long spd)
{
    if (act == 1)
        if (dia == 1)
            this->transfer(0x8b, 3, spd);
        else
            this->transfer(0x8a, 3, spd);
    else if (dia == 1)
        this->transfer(0x83, 3, spd);
    else
        this->transfer(0x82, 3, spd);
}

void L6470::release_sw(int act, int dia)
{
    if (act == 1)
        if (dia == 1)
            this->transfer(0x9b, 0, 0);
        else
            this->transfer(0x9a, 0, 0);
    else if (dia == 1)
        this->transfer(0x93, 0, 0);
    else
        this->transfer(0x92, 0, 0);
}

void L6470::go_home()
{
    this->transfer(0x70, 0, 0);
}

void L6470::go_mark()
{
    this->transfer(0x78, 0, 0);
}

void L6470::reset_pos()
{
    this->transfer(0xd8, 0, 0);
}

void L6470::reset_device()
{
    this->send_u(0x00); //nop命令
    this->send_u(0x00);
    this->send_u(0x00);
    this->send_u(0x00);
    this->send_u(0xc0);
}

void L6470::softstop()
{
    this->transfer(0xb0, 0, 0);
}

void L6470::hardstop()
{
    this->transfer(0xb8, 0, 0);
}

void L6470::softhiz()
{
    this->transfer(0xa0, 0, 0);
}

void L6470::hardhiz()
{
    this->transfer(0xa8, 0, 0);
}

long L6470::get_status()
{
    long val = 0;
    this->send_u(0xd0);
    for (int i = 0; i <= 1; i++)
    {
        val = val << 8;
        digitalWrite(PIN_SPI_SS, LOW);
        val = val | SPI.transfer(0x00);
        digitalWrite(PIN_SPI_SS, HIGH);
    }
    return val;
}

void L6470::transfer(int add, int bytes, long val)
{
    int data[3];
    this->send(add);
    for (int i = 0; i <= bytes - 1; i++)
    {
        data[i] = val & 0xff;
        val = val >> 8;
    }
    if (bytes == 3)
    {
        this->send(data[2]);
    }
    if (bytes >= 2)
    {
        this->send(data[1]);
    }
    if (bytes >= 1)
    {
        this->send(data[0]);
    }
}

void L6470::send(unsigned char add_or_val)
{
    while (!digitalRead(_busy_pin))
    {
    } //BESYが解除されるまで待機

    digitalWrite(PIN_SPI_SS, LOW);
    SPI.transfer(add_or_val);
    digitalWrite(PIN_SPI_SS, HIGH);
}

//busyを確認せず送信
void L6470::send_u(unsigned char add_or_val)
{                                   
    digitalWrite(PIN_SPI_SS, LOW);
    SPI.transfer(add_or_val);
    digitalWrite(PIN_SPI_SS, HIGH);
}

void L6470::busy_delay(long time)
{ 
    //BESYが解除されるまで待機
    while (!digitalRead(_busy_pin))
    {
    }
    delay(time);
}

long L6470::get_param(int add, int bytes)
{
    long val = 0;
    int send_add = add | 0x20;
    this->send_u(send_add);
    for (int i = 0; i <= bytes - 1; i++)
    {
        val = val << 8;
        digitalWrite(PIN_SPI_SS, LOW);
        val = val | SPI.transfer(0x00);
        digitalWrite(PIN_SPI_SS, HIGH);
    }
    return val;
}