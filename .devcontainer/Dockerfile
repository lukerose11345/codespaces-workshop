FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# Install clang-format
RUN apt-get update && apt-get install -y \
    clang-format \
    && rm -rf /var/lib/apt/lists/*
