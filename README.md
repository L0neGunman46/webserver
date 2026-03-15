## WebServer

Webserver stores and delivers webcontent over the internet, HTTP server focuses on HTTP requests and responses.

Working of a webserver:


Web Browser (res)<--->(req) Internet (res) <-----> (req) Web server


- Client Request:  User enters a URL
- DNS Resolution: Browser Contacts the DNS server to obtain the IP address of the requested domain
- Connecting to the web browser:  Using the obtained IP address establish a connection to the web server
- Processing the request:  Web server recieves the request and processes it.
- Serving the response:  requested files are sent to the clients browser by the web server.
- Rendering the webPage:  Based on the data recieved the browser reners the HTML files.

eg of types:
1.  Apache web server - advanced routing muti OS support
2. Nginx web server - high traffic efficiently, static server content, reverse proxy and load balancer.
3. Microsoft(IIS) - Internet information services , support ASP.net PHP and web tech
4. Lightspeed - had built in ddos protection. PHP support
5. Apache Tomcat - Supports Java Servlets 
6. NodeJs
7. Lighttpd: optimised for low memory usage and high speed performance, async event handling.


Web Servers and Their Use Cases
Choosing the right web server depends on what you need for your website or application. Here’s a simple guide to help you decide:

Apache: Reliable and customizable for general-purpose websites.
Nginx: High-performance server for heavy traffic.
IIS: Best for Windows and ASP.NET applications.
LiteSpeed: Faster, secure alternative to Apache for PHP/WordPress.
Apache Tomcat: Ideal for Java Servlets and JSP applications.
Node.js: Suited for real-time apps using JavaScript.
Lighttpd: Lightweight server for low-resource systems.
OpenLiteSpeed: Free, high-performance LiteSpeed alternative.
Jigsaw: Used for testing and researching web standards.
Sun Java System Web Server: For legacy Java apps (now discontinued


## Running the webserver
clang main.c -o main
./main

server initiates in port 8080

### routes
/home
/about

-- if any other route it redirects to no found page
