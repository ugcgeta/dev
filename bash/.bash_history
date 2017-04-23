sudo apt-get update
sudo apt-get upgrade
sudo reboot
sudo apt-get update; sudo apt-get install granatier frozen-bubble supertux tuxpaint tuxtype 
sudo shutdown -h now
usbls
lsusb
reboot
sudo reboot
cd projects/
ls
cd GPIOTest/
ls
gcc gpio.cpp 
ls
a.out
./a.out
sudo ./a.out
su
su root
sudo
sudo shutdown -h now
gpio readall
sudo raspi-config
usbls
lsusb
sudo reboot
gpio readall
sudo raspi-config
gpio_alt -p 13 -f 0
gpio_alt -p 18 -f 5
gpio readall
ls
ls -l
ls -a
git
git clone https://github.com/ugcgeta/dev
ls
cd dev
ls
mkdir vim
cd vim
"#####dein.vim縺ｮ險ｭ螳・####
if &compatible
  set nocompatible
endif
set runtimepath+=/home/pi/.vim/dein/.//repos/github.com/Shougo/dein.vim

"if dein#load_state(expand('~/.vim/dein'))
"endif

"譛ｪ繧､繝ｳ繧ｹ繝医・繝ｫ繧堤｢ｺ隱・if dein#check_install()
endif
filetype plugin indent on
set nocompatible
set number
set backspace=indent,eol,start
set autoindent
set smartindent
set tabstop=4
set shiftwidth=4
set ignorecase          " 螟ｧ譁・ｭ怜ｰ乗枚蟄励ｒ蛹ｺ蛻･縺励↑縺・set smartcase           " 讀懃ｴ｢譁・ｭ励↓螟ｧ譁・ｭ励′縺ゅｋ蝣ｴ蜷医・螟ｧ譁・ｭ怜ｰ乗枚蟄励ｒ蛹ｺ蛻･
set incsearch           " 繧､繝ｳ繧ｯ繝ｪ繝｡繝ｳ繧ｿ繝ｫ繧ｵ繝ｼ繝・set hlsearch            " 讀懃ｴ｢繝槭ャ繝√ユ繧ｭ繧ｹ繝医ｒ繝上う繝ｩ繧､繝・(2013-07-03 14:30 菫ｮ豁｣・・
" 繝舌ャ繧ｯ繧ｹ繝ｩ繝・す繝･繧・け繧ｨ繧ｹ繝√Ι繝ｳ繧堤憾豕√↓蜷医ｏ縺幄・蜍慕噪縺ｫ繧ｨ繧ｹ繧ｱ繝ｼ繝・cnoremap <expr> / getcmdtype() == '/' ? '\/' : '/'
cnoremap <expr> ? getcmdtype() == '?' ? '\?' : '?'

set shiftround          " '<'繧・>'縺ｧ繧､繝ｳ繝・Φ繝医☆繧矩圀縺ｫ'shiftwidth'縺ｮ蛟肴焚縺ｫ荳ｸ繧√ｋ
set infercase           " 陬懷ｮ梧凾縺ｫ螟ｧ譁・ｭ怜ｰ乗枚蟄励ｒ蛹ｺ蛻･縺励↑縺・"set virtualedit=all     " 繧ｫ繝ｼ繧ｽ繝ｫ繧呈枚蟄励′蟄伜惠縺励↑縺・Κ蛻・〒繧ょ虚縺代ｋ繧医≧縺ｫ縺吶ｋ
set hidden              " 繝舌ャ繝輔ぃ繧帝哩縺倥ｋ莉｣繧上ｊ縺ｫ髫�縺呻ｼ・ndo螻･豁ｴ繧呈ｮ九☆縺溘ａ・・set switchbuf=useopen   " 譁ｰ縺励￥髢九￥莉｣繧上ｊ縺ｫ縺吶〒縺ｫ髢九＞縺ｦ縺ゅｋ繝舌ャ繝輔ぃ繧帝幕縺・set showmatch           " 蟇ｾ蠢懊☆繧区峡蠑ｧ縺ｪ縺ｩ繧偵ワ繧､繝ｩ繧､繝郁｡ｨ遉ｺ縺吶ｋ
set matchtime=3         " 蟇ｾ蠢懈峡蠑ｧ縺ｮ繝上う繝ｩ繧､繝郁｡ｨ遉ｺ繧・遘偵↓縺吶ｋ

" 蟇ｾ蠢懈峡蠑ｧ縺ｫ'<'縺ｨ'>'縺ｮ繝壹い繧定ｿｽ蜉�
set matchpairs& matchpairs+=<:>

" 繝舌ャ繧ｯ繧ｹ繝壹・繧ｹ縺ｧ縺ｪ繧薙〒繧よｶ医○繧九ｈ縺・↓縺吶ｋ
set backspace=indent,eol,start

" 繧ｯ繝ｪ繝・・繝懊・繝峨ｒ繝・ヵ繧ｩ繝ｫ繝医・繝ｬ繧ｸ繧ｹ繧ｿ縺ｨ縺励※謖・ｮ壹ょｾ後↓YankRing繧剃ｽｿ縺・・縺ｧ
" 'unnamedplus'縺悟ｭ伜惠縺励※縺・ｋ縺九←縺・°縺ｧ險ｭ螳壹ｒ蛻・￠繧句ｿ・ｦ√′縺ゅｋ
if has('unnamedplus')
    " set clipboard& clipboard+=unnamedplus " 2013-07-03 14:30 unnamed 霑ｽ蜉�
    set clipboard& clipboard+=unnamedplus,unnamed 
else
    " set clipboard& clipboard+=unnamed,autoselect 2013-06-24 10:00 autoselect 蜑企勁
    set clipboard& clipboard+=unnamed
endif

" Swap繝輔ぃ繧､繝ｫ・檻ackup繝輔ぃ繧､繝ｫ・溷燕譎ゆｻ｣逧・☆縺・" 縺ｪ縺ｮ縺ｧ蜈ｨ縺ｦ辟｡蜉ｹ蛹悶☆繧・set nowritebackup
set nobackup
set noswapfile

set list                " 荳榊庄隕匁枚蟄励・蜿ｯ隕門喧
set number              " 陦檎分蜿ｷ縺ｮ陦ｨ遉ｺ
set wrap                " 髟ｷ縺・ユ繧ｭ繧ｹ繝医・謚倥ｊ霑斐＠
set textwidth=0         " 閾ｪ蜍慕噪縺ｫ謾ｹ陦後′蜈･繧九・繧堤┌蜉ｹ蛹・set colorcolumn=80      " 縺昴・莉｣繧上ｊ80譁・ｭ礼岼縺ｫ繝ｩ繧､繝ｳ繧貞・繧後ｋ

" 蜑肴凾莉｣逧・せ繧ｯ繝ｪ繝ｼ繝ｳ繝吶Ν繧堤┌蜉ｹ蛹・set t_vb=
set novisualbell

" 繝・ヵ繧ｩ繝ｫ繝井ｸ榊庄隕匁枚蟄励・鄒弱＠縺上↑縺・・縺ｧUnicode縺ｧ邯ｺ鮗励↓
set listchars=tab:>.,trail:-,extends:>,precedes:<,nbsp:%,eol:/

" 蜈･蜉帙Δ繝ｼ繝我ｸｭ縺ｫ邏�譌ｩ縺祝j縺ｨ蜈･蜉帙＠縺溷�ｴ蜷医・ESC縺ｨ縺ｿ縺ｪ縺・inoremap jj <Esc>

" 繧ｫ繝ｼ繧ｽ繝ｫ荳九・蜊倩ｪ槭ｒ * 縺ｧ讀懃ｴ｢
vnoremap <silent> * "vy/\V<C-r>=substitute(escape(@v, '\/'), "\n", '\\n', 'g')<CR><CR>

ls
ls la
ls -a
cd ../
ls
git add vim
git commit vim 
git config --global user.email "ugcgeta@gmail.com"
git config --global user.name "ugcgeta"
git commit vim 
git commit vim -m"add"
git push
git_remote_-v
git remote -v
cd ../
pwd
git remote -v
cd dev
git remote -v
git-credential-store
ls -a
vi .git/
vi .git
vi .git/config 
ls
cd vim
ls
ln -s .vimrc ~/
vi .vimrc 
ls ~/.vimrc
ls ~/.vimrc 
ls ~/.
ls -a~/.
ls -a ~/.
cd ~/
ls -l
ls -l -a
vi .vimrc 
rm -rf .vimrc 
ln -s ~/dev/vim/.vimrc ~/
ls -l -a
cd dev/
ls
cd vim
vi .vimrc 
vim
vi
vim
vi --version
ls /bin/vi
ls /bin/
ls /bin/vi*
who vi
which vi
/usr/bin/vi*
ls /usr/bin/vi*
sudo apt-get install vim
vim -version
vim --version
vim .vimrc 
cd ../python/
ls
cd oled_SSD1306/
ls
vi oled.py 
vi --version
vi
vim
which vi
ls -l user/bin/vi
ls -l /user/bin/vi
ls -l /usr/bin/vi
ls -l /etc/alternatives/vi
ls
cd ../../
git add
git commit -m"vim OK"
git add ./vim/.vimrc
git commit -m"vim OK"
git push
ls
sudo shutdown -h now
cd dev/python/oled_SSD1306/
ls
sudo python3 oled.py 
sudo apt-get update
sudo apt-get upgrade
sudo python3 oled.py 
sudo python oled.py 
sudo pip install wiringpi2
sudo reboot
s
sudo pip install wiringpi2
sudo pip3 install wiringpi2
cd dev/python/oled_SSD1306/
sudo python3 oled.py 
sudo vi /boot/config.txt 
sudo reboot
cd dev/python/oled_SSD1306/
sudo python3 oled.py 
vi oled.py 
sudo python3 oled.py 
vi oled.py 
sudo python3 oled.py 
vi oled.py 
sudo python3 oled.py 
ls
vi putchar.py
ci ~/.bashrc
vi ~/.bashrc
vi ~/.bash_aliases
alias spython='sudo python3'
spython putchar.py
vi putchar.py
ls
vi shinonome16x16FontList.py 
ls
git commit -m"wiringpi"
rm -rf __pycache__
git add
git add oled.py putchar.py __pycache__
git commit -m"wiringpi"
git push
ls
vi shinonome16x16FontList.py 
vi putchar.py
rm -rf putchar.py_org 
vi putchar.py
vi ../tempGraph/tempGraph.py 
vi putchar.py 
spython putchar.py 
vi putchar.py 
cd ../
ls
cd am2320_i2c_test/
ls
rm -rf __pycache__
vi am2320.py 
git add __pycache__ am2320.py
cd ../
ls
cd bmp180
ls
vi bmp180.py 
cd ../
ls
cd oled_SSD1306/
ls
rm -rf __pycache__
sudo rm -rf __pycache__
export PYTHONDONTWRITEBYTECODE=1
vi ~/.bashrc 
cd ../
ls
cd pwm_test/
ls
vi led_pwm.py 
vi pwm.py 
ls
rm -rf pwm_org.py
git add pwm_org.py pwm.py led_pwm.py
cd ../
ls
cd sendMail/
ls
vi sendMail.py 
cd ../
ls
cd tempGraph/
ls
rm -rf __pycache__/
git add __pycache__
vi tempGraph.py 
git add tempGraph.py 
cd ../
ls
git commit -m"wiring2"
git push
ls
cd tempGraph/
spython tempGraph.py 
sudo python3 setup.py install
cd ~/
ls
mkdir temp
cd temp
git pull https://github.com/adafruit/Adafruit_Python_BMP
git clone https://github.com/adafruit/Adafruit_Python_BMP
ls
cd Adafruit_Python_BMP/
ls
sudo python3 setup.py install
cd ~/dev/python/tempGraph/
ls
spython tempGraph.py 
sudo shutdown -h now
cd dev/python/
ls
mkdir watch
cd watch/
cp ../tempGraph/*.py ./
ls
ls -l
rm -rf am2320.py bmp180.py oled.py shinonome16x16FontList.py
ln -s ../am2320_i2c_test/am2320.py 
ln -s ../bmp180/bmp180.py 
ln -s ../oled_SSD1306/oled.py 
ln -s ../oled_SSD1306/shinonome16x16FontList.py 
ls -l
mv tempGraph.py watch.py
vi watch.py 
spython watch.py 
vi watch.py 
spython watch.py 
vi watch.py 
spython watch.py 
vi watch.py 
spython watch.py 
vi watch.py 
spython watch.py 
ls
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
spython oled.py 
vi oled.py 
ls
rm -rf __pycache__/
sudo rm -rf __pycache__
ls
cd ../
git add watch
git commit-m""
git commit -m""
git commit -m" "
git commit -m"add watch "
git push
cd watch/
ls
audo shutdown -h now
sudo shutdown -h now
