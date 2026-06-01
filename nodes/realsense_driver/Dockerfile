FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    curl ca-certificates gnupg build-essential cmake pkg-config \
    && mkdir -p /etc/apt/keyrings \
    && curl -sSf https://librealsense.intel.com/Debian/librealsense.pgp \
       | gpg --dearmor \
       | tee /etc/apt/keyrings/librealsense.gpg > /dev/null \
    && echo "deb [signed-by=/etc/apt/keyrings/librealsense.gpg] https://librealsense.intel.com/Debian/apt-repo jammy main" \
       > /etc/apt/sources.list.d/librealsense.list \
    && apt-get update && apt-get install -y \
       librealsense2-dev \
       librealsense2-utils \
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