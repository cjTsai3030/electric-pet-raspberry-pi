package iodd;

import java.io.*;
import java.net.*;
import com.sun.net.httpserver.*;
import java.util.*;

public class  httpServer {
	
public static void httpServer() throws Exception{
	HttpServer server = HttpServer.create(new InetSocketAddress(9487), 0);
	server.createContext("/test", new MyHandler());
	server.start();
}

static class MyHandler implements HttpHandler {
	
@Override
public void handle(HttpExchange he) throws IOException {
	if (he.getRequestMethod().equalsIgnoreCase("POST")) {
		System.out.println("POST!!");
	try {
		Headers requestHeaders = he.getRequestHeaders();
		Set<Map.Entry<String, List<String>>> entries = requestHeaders.entrySet();

		int contentLength = Integer.parseInt(requestHeaders.getFirst("Content-length"));
		System.out.println(""+requestHeaders.getFirst("Content-length"));

		InputStream is = he.getRequestBody();
		byte[] data = new byte[contentLength];
		int length = is.read(data);
		Headers responseHeaders = he.getResponseHeaders();
		he.sendResponseHeaders(HttpURLConnection.HTTP_OK, contentLength);
		OutputStream os = he.getResponseBody();
		os.write(data);
		he.close();
	} catch (NumberFormatException | IOException e) {}
	}
}
}
}
