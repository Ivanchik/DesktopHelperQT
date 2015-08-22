# Minimal docker container to build project
# Image: rabits/qt-android:5.4

FROM windows10
MAINTAINER Ivan <bikeev-ivan@yandex.ru>

ENV QT_PATH /opt/Qt

# Install updates & requirements:
#  * git, openssh-client - for Drone
#  * curl, p7zip - to download & unpack Qt bundle
#  * make, default-jdk, ant - basic build requirements
#  * libsm6, libice6, libxext6, libxrender1, libfontconfig1 - dependencies of Qt bundle run-file
RUN apt-get -qq update && apt-get -qq dist-upgrade && apt-get install -qq -y --no-install-recommends \
    git \
    openssh-client \
    make \
    default-jdk \
    ant \
    ca-certificates \
    curl \
    p7zip \
    libsm6 \
    libice6 \
    libxext6 \
    libxrender1 \
    libfontconfig1 \
    && apt-get -qq clean

# Download & unpack Qt 5.4 toolchains & clean
RUN mkdir -p /tmp/qt \
    && curl -Lo /tmp/qt/installer.run 'http://download.qt-project.org/official_releases/qt/5.4/5.4.0/qt-opensource-linux-x64-android-5.4.0.run' \
    && chmod 755 /tmp/qt/installer.run && /tmp/qt/installer.run --dump-binary-data -o /tmp/qt/data \
    && mkdir $QT_PATH && cd $QT_PATH \
    && 7zr x /tmp/qt/data/qt.54.android_armv7/5.4.0-1qt5_essentials.7z > /dev/null \
    && 7zr x /tmp/qt/data/qt.54.android_armv7/5.4.0-1qt5_addons.7z > /dev/null \
    && /tmp/qt/installer.run --runoperation QtPatch linux $QT_ANDROID qt5 \
    && rm -rf /tmp/qt

# Reconfigure locale
RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales

USER user
WORKDIR /home/user
