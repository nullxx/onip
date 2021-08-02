FROM alpine:3.11.2

# Install dependencies
RUN apk add build-base curl-dev json-c-dev

WORKDIR /app

# Copy source
COPY src /app/src
COPY Makefile /app/Makefile

# Init build environment
RUN make init
# Build the app
RUN make build
# Install the app
RUN make install

# Run the app
CMD [ "onip" ]