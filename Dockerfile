FROM grantslape/qt4.7:latest
# Sub project to build
ARG BUILDDIR=assignmenti2
ENV BUILDDIR=${BUILDDIR}

# Application Code
COPY app/ /tmp/app
WORKDIR /tmp/app/${BUILDDIR}
RUN qmake -project && qmake && make
# Assumes executable is same name as build directory
ENTRYPOINT /tmp/app/${BUILDDIR}/${BUILDDIR}
