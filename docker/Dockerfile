### Build/test container ###
# Define builder stage
FROM hr-web-server:base as builder

# Share work directory
COPY . /usr/src/project
WORKDIR /usr/src/project/build

# Build and test
RUN cmake ..
RUN make
RUN ctest --output-on_failure


### Deploy container ###
# Define deploy stage
FROM ubuntu:bionic as deploy

# Copy server output binary to "."
COPY --from=builder /usr/src/project/build/bin/server .
COPY --from=builder /usr/src/project/docker_config .

# Copy static files to "."
COPY --from=builder /usr/src/project/static/static_1 ./static_1
COPY --from=builder /usr/src/project/static/static_2 ./static_2
COPY --from=builder /usr/src/project/static/meme_images ./meme_images
# Expose some port(s)
EXPOSE 80

# Use ENTRYPOINT to specify the binary name
# TODO(!): Update with real server name
ENTRYPOINT ["./server"]

# Use CMD to specify arguments to ENTRYPOINT
# TODO(!): Update with real server args
CMD ["docker_config"]
