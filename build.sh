exec > /dev/null 2>&1
echo Installing Tools
sudo apt install make libjson-glib-dev autoconf libgtk-3-dev
echo Building . . .
autoreconf -i
./config
make
