FROM fedora:44

RUN dnf -y install \
    sudo \
    git \
    gcc \
    gcc-c++ \
    make \
    cmake \
    ninja-build \
    extra-cmake-modules \
    kf6-kirigami-devel \
    kf6-ki18n-devel \
    kf6-kcoreaddons-devel \
    kf6-kiconthemes-devel \
    kf6-qqc2-desktop-style \
    qt6-qtbase-devel \
    qt6-qtdeclarative-devel \
    && dnf clean all

RUN useradd -m -s /bin/bash vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/vscode

USER vscode