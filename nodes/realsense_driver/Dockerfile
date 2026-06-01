FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    software-properties-common curl ca-certificates \
    && curl -sSf https://librealsense.intel.com/Debian/librealsense.pgp \
       | apt-key add - \
    && add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo jammy main" \
    && apt-get update && apt-get install -y \
       librealsense2-dev \
       librealsense2-utils \
       build-essential cmake pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY msgs/                            /app/msgs/
COPY middleware/                      /app/middleware/
COPY nodes/realsense_driver/          /app/node/
COPY config/realsense_intrinsics.yaml /app/config/realsense_intrinsics.yaml

RUN cmake -S /app/node -B /app/node/build \
      -DCMAKE_BUILD_TYPE=Release \
    && cmake --build /app/node/build --parallel $(nproc)

CMD ["/app/node/build/realsense_driver"]