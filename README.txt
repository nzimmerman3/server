Team: Hard Reboot
Authors: Marvin Cirignano, Joshua McInerney, Nicholas Zimmerman, Irfan Sattar


CMakeLists.txt: configures the web server to be built and tested by the cmake framework

docker_config: the config file that is used in deployment on Google cloud in our web server

Misc: .dockerignore and .gitignore


Subdirectories:
	cmake: associated with cmake framework used to help build and test source code efficiently. 

	docker:
		base.Dockerfile: This file is used to configure the base image on google cloud

		cloudbuild.yaml: Specifies the build, test, and deployment processes to the Google cloud server

		coverage.Dockerfile: This file is used to configure the coverage image to provide a coverage report for the tests

		Dockerfile: This file is used to configure the image for our web server�s main deployment

	include:
		config_parser.h: We define our NginxConfig and NginxConfigStatements classes here

		logger.h: Sets up the logging capabilities along with creating a global logger to be used throughout the project

		request_router.h: Declares the request_router class, which instantiates the handlers that we need and routes requests to the appropriate handlers

		server.h: Declares the server class, which is the core of our web server. Requests are sent directly to this server to be processed for a response. Keeps track of the port number and a request router object to which requests will be sent

		session.h: Declares our session class, which specifies connection-specific object. Each connection will have its own session, the process of which the server maintains

		server_status_singleton.h: Declares the server_status_singleton class, which is used to provide global status handling

		response_generator.h: Declares our response_generator class, which is used to formulate client replies

	src:
		config_parser.cc: This file implements the functions needed to parse the config file and extract the configurations needed to start up the server. Uses tokenization and string parsing to extract this information.

		logger.cc: Sets up the Boost logger sinks (to a file and to standard output) along with the corresponding formatting for all logging output

		request_router.cc: Defines and implements the request_router class, which instantiates the handlers that we need and route requests to the appropriate handlers

		server_main.cc: Our main function for our executable, in which the config file is parsed for information that is passed to a server start-up function

		server.cc: Defines the server class. Implements a function (startAccept) to accept connections from clients, and another function (handleAccept) to serve the requests that are passed to the server. Will use its request router to do so.

		session.cc: Defines the session class, which is instantiated for each connection. It handles requests by parsing them and sending them to a request_router if they are valid

		response_generator.cc: Defines the response generator class, which is used to formulate replies to clients. Includes the definitions of buffering and stock response functions

		server_status_singleton.cc: Defines the server_status_singleton class, providing functions that allow the updates and retrieval of status information

	libraries:
		include:
			echo_request_handler.hpp: Defines the handler for echo requests and declares the handler function, inherits from the request_handler class

			header.hpp: Defines the header class. Headers will be attached to every HTTP request and response

			mime_types.hpp: Header class for our mime_type namespace, which will be used to specify file types for static file fetching

			request_handler.hpp: Defines the interface for all of the handler classes in our web server, specifically the echo and static handlers

			request_parser.hpp: Declares the request_parser class, which goes through each request, determines its validity, and extracts

			request.hpp: Defines the request object, containing a method, URI, and other HTTP info

			response.hpp: Defines the response object, which contains a status, HTTP header, and body

			static_request_handler.hpp: Defines the handler for static requests and declares the handler function, inherits from the request_handler class. Stores the current root directory and has a url decoding function

			404_request_handler.hpp: Declares the 404 handler, which services bad requests with 404 responses

			status_request_handler.hpp: Declares the handler for status requests, including handler and past request information

		src:
			echo_request_handler.cpp: Defines the echo request handle_request function. If it is a valid request, just echoes back the request body in the response body

			mime_types.cpp: Defines the mime_type namespace, which contains a method that maps each file extension type to its corresponding mime type, so that static files can be served correctly

			request_parser.cpp: Defines the request_parser class, which goes through each request and determines its validity

			response.cpp: Specifies namespaces for the response object, such as status strings, buffer responses, and stock replies

			static_request_handler.cpp: Defines the handler for static requests. If it is a valid request, it serves the requested static file by modifying a response object in its handle_request function with the file included

			404_request_handler.cpp: Defines the handler for bad requests. If the longest matching prefix is just �/�, then the 404 handler is invoked, and a typical 404 response is sent back

			status_request_handler.cpp: Defines the handler for status requests. If it is a valid request, formulates an HTTP response object with status information included. Status information includes what handlers exist and their URIs, and the requests received/status codes sent back.


	static: just contains our static files that we serve from our web server

	tests:
		boost-http:
			request_parser_test.cc: Contains unit tests to check whether valid and invalid requests are identified properly

		config_parser:
			config_parser_test.cc: Contains unit tests to check whether a config is valid, and if so if we are extracting valid information from	this config files

			Misc: Different sample config files used for the purposes of testing. Notable is �new_format_config�, which was used to test the new API development

		handlers:
			404_request_handler_test.cc: Contains a simple unit test that insures the 404 request handler acts appropriately

		request_router:
			request_router_test.cc and config: Contains unit tests to insure that the request_router object responds appropriately to all different kinds of request by routing them to the correct handlers

		integration_tests: 
			echo_integration_test.sh and static_file_integration_test.sh start up the web server with fake config files and makes requests to ensure we get the desired output

		Misc: server_test.cc and session_test.cc
	


How to use the web server
Building:
	To build the main server, execute the following commands from the main project directory
		mkdir build
		cd build
		cmake ..
		make


	To perform the build for the coverage report, execute the following commands from the main project directly:
		mkdir build_coverage
		cd build_coverage
		cmake -DCMAKE_BUILD_TYPE=Coverage ..
		make coverage

		After you have performed these commands, the coverage report should be available in this build_coverage folder in the form of an HTML file


Testing:
	To test the web server, go into the �build� directory after performing the steps above, and run the following command:
		make test

		This will output the results of your test. To see a more verbose output from the tests, execute the following:
		make test ARGS=-V

	The integration tests can also be run separately from the main project folder, by going into the folder, �tests/integration_tests� and running any of the scripts
		

Running:
	First run the build steps specific above. Then to run the server, from the main project source directory, go into �build/bin�. The �server� executable should be in there. Run the following command:
		./server <config_file>
	Replace <config_file> with the path to a config file with the configurations that you want for your server. 

	Now that the server, is running, make any HTTP requests that you want and have specified through your configuration file



How to add a request handler
To add a request handler, first create the source files for the new request handler (new_request_handler.hpp and new_request_handler.cpp) and should implement the request_handler interface in request_handler.hpp.

Make sure each request handler includes a static constructor method with the following signature:

	request_handler* new_request_handler::Init(const std::string& location_path, const NginxConfig& config) 


This new request handler also needs to implement the following function:

	virtual response handle_request(const request& req) = 0;


Then, update request_router.cc to integrate the this new request handler. Add a new if block that corresponds to the creating the new_request_handler:

	if (handlerName == �EchoHandler�) {
		auto smart = std::shared_ptr< http::server::request_handler >( http::server::echo_request_handler::Init(handlerRoot, handlerConfig) );
		handlerMap_[handlerUri] = smart;
	} else if (handlerName == �StaticHandler�) {
		auto smart = std::shared_ptr< http::server::request_handler >( http::server::static_request_handler::Init(handlerRoot, handlerConfig) );
		handlerMap_[handlerUri] = smart;
	} else if (handlerName == �NewHandler�) {
		auto smart = std::shared_ptr< http::server::request_handler >( http::server::new_request_handler::Init(handlerRoot, handlerConfig));
		handlerMap_[handlerUri] = smart;
	} else {
		BOOST_LOG_SEV(slg_, logging::trivial::error) << �Unknown handler type�;
	}

Once this is done, using new handlers will be simple.
		