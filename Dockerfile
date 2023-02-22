FROM ubuntu:20.04 AS build
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y git python3-h5py python3-ipython python3-pint python3-sphinx python3-matplotlib python3-dev python3-numpy build-essential gcc libhdf5-openmpi-dev python-is-python3

ENV PYTHONEXE=python3
ENV HDF5_ROOT_DIR=/usr/lib/x86_64-linux-gnu/hdf5/openmpi

RUN mkdir /smilei
COPY . /smilei/
WORKDIR /smilei

RUN make

FROM ubuntu:20.04 AS prod
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y git python3-h5py python3-ipython python3-pint python3-sphinx python3-matplotlib python3-dev python3-numpy build-essential gcc libhdf5-openmpi-dev python-is-python3

RUN mkdir /smilei-bin
COPY --from=build /smilei/build/* /smilei-bin

ENV OMP_NUM_THREADS=8
ENV OMP_SCHEDULE=dynamic
ENV OMP_PROC_BIND=true

RUN mkdir /smilei-prod
WORKDIR /smilei-prod

RUN useradd -ms /bin/bash smilei
USER smilei

ENTRYPOINT ["mpirun", "/smilei-bin/smilei"]
