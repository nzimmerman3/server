#!/bin/bash

# Integration Test works by intiating two connections with server
# and sending echo requests; first connection's request is not
# fully sent until a few seconds later to allow for second
# connection's request to be sent and processed first; this is
# the expected behavior

echo "Setting up multi-threading test..."

# Create config file for server
mkdir .temporary/
TEMPORARY_CONFIG=".temporary/temporary_config"
echo "
port 8080;
location \"/echo\" EchoHandler {

}

location \"/echo2\" EchoHandler {

}" > "$TEMPORARY_CONFIG"

# Run the webserver with a temporary config (in the background)
./server "$TEMPORARY_CONFIG" &
SERVER_PID=$!

# Give some time for server to be fully set up
# and waiting for connections
sleep 2

echo "Starting test..."

# Intiate two connections and send two requests
# -i 2 on the first connection delays the transmission of each line of the message
# which results in an incomplete request being sent to the server over connection 1
echo "Initiating communication to server using two clients..."
printf "GET /echo HTTP/1.1\r\n\r\n" | nc localhost 8080 -w 5 -i 2 > client_output_1 &
printf "GET /echo2 HTTP/1.1\r\n\r\n" | nc localhost 8080 -w 5 > client_output_2 &

sleep 1

log_client_output () {
    let i=1
    while (($i<$@)); do
        echo "Current client $i output..."
        cat "client_output_$i"
    done
}

exit_code=0

log_client_output 1 2
# Check if client two received its output before client one got any output
if grep -q "GET /echo2 HTTP/1.1" client_output_2 && [[ ! -s client_output_1 ]];
then
    echo "Server responded to client 2 before client 1 completed request..."
else
    echo "Server did not respond to client 2 before client 1..."
    echo "Test failed..."
    exit_code=1
fi

sleep 10

# Check that client one eventually gets its output once nc finishes sending message
log_client_output 1
if grep -q "GET /echo HTTP/1.1" client_output_1;
then
    echo "Client 1 response received correctly..."
else
    echo "Incorrect response for client 1..."
    echo "Test failed..."
    exit_code=1
fi

# Clean up and exit with appropriate exit code
rm -rf .temporary/
rm client_output_1 client_output_2
kill "$SERVER_PID"
exit $exit_code