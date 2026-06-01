FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    libssl-dev libusb-1.0-0-dev libudev-dev \
    libv4l-dev pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/IntelRealSense/librealsense.git \
      --depth 1 --branch v2.55.1 /opt/librealsense \
    && cmake -S /opt/librealsense -B /opt/librealsense/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DFORCE_RSUSB_BACKEND=OFF \
      -DBUILD_EXAMPLES=OFF \
      -DBUILD_GRAPHICAL_EXAMPLES=OFF \
      -DBUILD_PYTHON_BINDINGS=OFF \
      -DBUILD_PCAP=OFF \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
    && cmake --build /opt/librealsense/build --parallel $(nproc) \
    && cmake --install /opt/librealsense/build \
    && rm -rf /opt/librealsense

RUN ldconfig

WORKDIR /app

COPY msgs/                            /app/msgs/
COPY middleware/                      /app/middleware/
COPY nodes/realsense_driver/          /app/node/
COPY config/realsense_intrinsics.yaml /app/config/realsense_intrinsics.yaml

RUN cmake -S /app/node -B /app/node/build \
      -DCMAKE_BUILD_TYPE=Release \
    && cmake --build /app/node/build --parallel $(nproc)

CMD ["/app/node/build/realsense_driver"]
