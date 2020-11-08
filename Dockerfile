FROM ubuntu:18.04

RUN apt-get update

RUN apt-get install --no-install-recommends -y g++ doxygen graphviz valgrind cppcheck libgtest-dev make cmake && rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/gtest && cmake . && make && cp *.a /usr/lib && ln -s /usr/lib/libgtest.a /usr/local/lib/libgtest.a && ln -s /usr/lib/libgtest_main.a /usr/local/lib/libgtest_main.a