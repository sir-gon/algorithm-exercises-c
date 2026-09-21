FROM ubuntu:26.04 AS init

ENV WORKDIR=/app
WORKDIR ${WORKDIR}
ENV VCPKG_ROOT=/opt/vcpkg

RUN apt-get -y update && \
  apt-get -y install --no-install-recommends --no-install-suggests \
    "ca-certificates=20260601~26.04.1" \
    "make=4.4.1-3" && \
  rm -rf /var/lib/apt/lists/*

FROM init AS builder
ARG GENERATE_ASM=0
ENV GENERATE_ASM=${GENERATE_ASM}

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# build tools
RUN apt-get update && \
  apt-get -y install --no-install-recommends --no-install-suggests \
    "curl=8.18.0-1ubuntu2.5" \
    "gpg=2.4.8-4ubuntu3.1" \
    "lsb-release=12.1-2build1" \
  && apt-get -y install --no-install-recommends --no-install-suggests \
    "build-essential=12.12ubuntu2.26.04.2" \
    "g++=4:15.2.0-5ubuntu1" \
    "gcc=4:15.2.0-5ubuntu1" \
    "make=4.4.1-3" \
    "pkg-config=2.5.1-4" \
  # CMAKE from Kitware repository
  && curl --proto "=https" -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
  | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg \
  && echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu $(lsb_release -cs) main" \
  > /etc/apt/sources.list.d/kitware.list \
  && apt-get -y autoremove curl lsb-release gpg \
  && apt-get update \
  && apt-get install -y --no-install-recommends "cmake=4.2.3-2ubuntu2" "cmake-data=4.2.3-2ubuntu2" \
  ## clean up
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && make --version \
  && gcc --version \
  && g++ --version \
  && cmake --version

# vcpkg Package Manager
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
ENV VCPKG_VERSION=2026.07.29
ENV VCPKG_ROOT=/opt/vcpkg

# vcpkg Package Manager
RUN apt-get -y update && \
  apt-get -y install --no-install-recommends --no-install-suggests \
    "curl=8.18.0-1ubuntu2.5" \
  && apt-get -y install --no-install-recommends --no-install-suggests \
    "git=1:2.53.0-1ubuntu1" "ninja-build=1.13.2-1" "unzip=6.0-29ubuntu1" "zip=3.0-15ubuntu3" \
  && rm -rf /var/lib/apt/lists/* \
  && mkdir /opt/vcpkg \
  && git clone --branch "${VCPKG_VERSION}" https://github.com/microsoft/vcpkg "${VCPKG_ROOT}" \
  && /opt/vcpkg/bootstrap-vcpkg.sh \
  && apt-get -y autoremove curl \
  && ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg && \
  rm -rf /var/lib/apt/lists/* && \
  vcpkg version

# sources
COPY ./src ${WORKDIR}/src
COPY ./vcpkg.json ${WORKDIR}/vcpkg.json
COPY ./CMakeLists.txt ${WORKDIR}/CMakeLists.txt
COPY ./CMakePresets.json ${WORKDIR}/CMakePresets.json
COPY ./Makefile ${WORKDIR}/

# dependencies
RUN make dependencies

LABEL vcpkg=enabled

# build
RUN ls -alhR && \
  mkdir build && \
  make build && \
  ls -alhR

CMD ["make", "build"]

FROM builder AS development

# CMD []

FROM init AS lint

# Instala sólo lo mínimo necesario para linting (cmake, clang-format, cppcheck)
RUN apt-get update && \
  apt-get -y install --no-install-recommends --no-install-suggests \
    "clang-format=1:21.1.6-71" "cmake=4.2.3-2ubuntu2" "cmake-data=4.2.3-2ubuntu2" "cppcheck=2.19.0-3" \
  && rm -rf /var/lib/apt/lists/*

# Tooling test
RUN clang-format --version && \
  cppcheck --version && \
  cmake --version

# Copia sólo lo necesario para ejecutar las comprobaciones
COPY ./src ${WORKDIR}/src
COPY ./Makefile ${WORKDIR}/
RUN mkdir -p "${WORKDIR}"/build
COPY --from=builder ${WORKDIR}/build/compile_commands.json ${WORKDIR}/build/compile_commands.json

CMD ["make", "lint-no-deps"]

FROM development AS testing

RUN apt-get -y update && \
  apt-get -y install --no-install-recommends --no-install-suggests "lcov=2.4-3" && \
  rm -rf /var/lib/apt/lists/*

COPY --from=builder ${WORKDIR}/build ${WORKDIR}/

CMD ["make", "test"]

FROM ubuntu:26.04 AS production

ENV LOG_LEVEL=INFO
ENV BRUTEFORCE=false
ENV WORKDIR=/app
WORKDIR ${WORKDIR}

COPY --from=builder ${WORKDIR}/build/src/lib/exercises/*.a ${WORKDIR}/

RUN useradd --uid 1000 --user-group --system --create-home --no-log-init app
USER 1000

RUN ls -alhR

CMD ["make", "run"]
