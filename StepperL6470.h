#ifndef _L6470_H_
#define _L6470_H_

class L6470 {

    public:
    L6470(const int ss_pin, const int mosi_pin, const int miso_pin, const int sck_pin, 
          const int busy_pin, const int alarm_pin, const int reset_pin); 
    void init();

    /* 
    レジスタ操作　
    [R]:読み取り専用
    [WR]:いつでも書き換え可
    [WH]:書き込みは出力がハイインピーダンスの時のみ可
    [WS]:書き換えはモータが停止している時のみ可
    */
    // 書き込み
    void setparam_abspos(long val); //[R, WS]現在座標default 0x000000 (22bit) 
    void setparam_elpos(long val); //[R, WS]コイル励磁の電気的位置default 0x000 (2+7bit)
    void setparam_mark(long val); //[R, WR]マーク座標default 0x000000 (22bit)
    void setparam_acc(long val); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    void setparam_dec(long val); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
    void setparam_maxspeed(long val); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
    void setparam_minspeed(long val); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val+[step/s])
    void setparam_fsspd(long val); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
    void setparam_kvalhold(long val); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
    void setparam_kvalrun(long val); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
    void setparam_kvalacc(long val); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
    void setparam_kvaldec(long val); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
    void setparam_intspd(long val); //[R, WH]逆起電力補償切替点速度default 0x0408 (14bit) (0.238*val[step/s])
    void setparam_stslp(long val); //[R, WH]逆起電力補償低速時勾配default 0x19 (8bit) (0.000015*val[% s/step])
    void setparam_fnslpacc(long val); //[R, WH]逆起電力補償高速時加速勾配default 0x29 (8bit) (0.000015*val[% s/step])
    void setparam_fnslpdec(long val); //[R, WH]逆起電力補償高速時減速勾配default 0x29 (8bit) (0.000015*val[% s/step])
    void setparam_ktherm(long val); //[R, WR]不明default 0x0 (4bit) (0.03125*val+1)
    void setparam_ocdth(long val); //[R, WR]過電流しきい値default 0x8 (4bit) (375*val+375[mA])
    void setparam_stallth(long val); //[R, WR]失速電流しきい値？default 0x40 (7bit) (31.25*val+31.25[mA])
    void setparam_stepmood(long val); //[R, WH]ステップモードdefault 0x07 (1+3+1+3bit)
    void setparam_alareen(long val); //[R, WS]有効アラームdefault 0xff (1+1+1+1+1+1+1+1bit)
    void setparam_config(long val); //[R, WH]各種設定default 0x2e88 (3+3+2+1+1+1+1+1+3bit)

    // 読み取り
    long getparam_abspos();
    long getparam_elpos();
    long getparam_mark();
    long getparam_speed();
    long getparam_acc();
    long getparam_dec();
    long getparam_maxspeed();
    long getparam_minspeed();
    long getparam_fsspd();
    long getparam_kvalhold();
    long getparam_kvalrun();
    long getparam_kvalacc();
    long getparam_kvaldec();
    long getparam_intspd();
    long getparam_stslp();
    long getparam_fnslpacc();
    long getparam_fnslpdec();
    long getparam_ktherm();
    long getparam_adcout();
    long getparam_ocdth();
    long getparam_stallth();
    long getparam_stepmood();
    long getparam_alareen();
    long getparam_config();
    long getparam_status();

    /*
    コントロール
    dia   1:正転 0:逆転,
    spd  (20bit)(0.015*spd[step/s])
    pos  (22bit)
    n_step (22bit)
    act   1:絶対座標をマーク  0:絶対座標リセット
    mssec ミリ秒
    val 各レジスタに書き込む値
    */
    void run(int dia, long spd); //指定方向に連続回転
    void stepclock(int dia); //指定方向にstepピンのクロックで回転
    void move(int dia, long n_step); //指定方向に指定数ステップする 
    void go_to(long pos); //指定座標に最短でいける回転方向で移動
    void go_to_dia(int dia, int pos); //回転方向を指定して指定座標に移動
    void go_until(int act, int dia, long spd); //指定した回転方向に指定した速度で回転し、スイッチのONで急停止と座標処理
    void release_sw(int act, int dia); //スイッチがOFFに戻るまで最低速度で回転し、停止と座標処理
    void go_home(); //座標原点に移動
    void go_mark(); //マーク座標に移動
    void reset_pos(); //絶対座標リセット
    void reset_device(); //L6470リセット
    void softstop(); //回転停止、保持トルクあり
    void hardstop(); //回転急停止、保持トルクあり
    void softhiz(); //回転停止、保持トルクなし
    void hardhiz(); //回転急停止、保持トルクなし
    long get_status(); //statusレジスタの値を返す (this->get_param_status();と同じ)
    void busy_delay(long time); //busyフラグがHIGHになってから、指定ミリ秒待つ。

    void transfer(int add, int bytes, long val);
    void send(unsigned char add_or_val);
    void send_u(unsigned char add_or_val);
    long get_param(int add, int bytes);

    private:
    int _ss_pin;
    int _mosi_pin;
    int _miso_pin;
    int _sck_pin;
    int _busy_pin;
    int _alarm_pin;
    int _reset_pin;
};

#endif

