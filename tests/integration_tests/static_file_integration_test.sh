#!/bin/bash

# Create a temporary config (only configures the port for now)
mkdir .temporary/
TEMPORARY_CONFIG=".temporary/temporary_config"
echo "
port 8080;
location \"/testing\" StaticHandler {
	root /usr/src/project/static/static_1;
}
" > "$TEMPORARY_CONFIG"

#static /testing //usr/src/project/static_1;


# Run the webserver with a temporary config (in the background)
./server "$TEMPORARY_CONFIG" &
SERVER_ID=$!

sleep 5s

#Tests that the server is up and running
if ps | grep -q "server";
then
	echo "Server start up succeeded"
else
	echo "Server failed to start up"
	rm -rf .temporary/
	kill "$SERVER_ID"
	exit 1
fi



# Send a GET request to the server
echo "Testing static file retrieval from server with GET request"
curl "http://localhost:8080/testing/index.html" -isS -o response.out


# Test that the response from the web server is valid
if grep -q "Hello World" response.out;
then
	echo "Expected output received from the web server"
else
	echo "Unexpected output received from web server"
	rm response.out
	rm -rf .temporary/
	kill "$SERVER_ID"
	exit 1
fi


#Our integration tests have passed if we reach here: clean-up code
rm response.out
rm -rf .temporary/
kill "$SERVER_ID"
