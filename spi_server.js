var sys = require('sys');
var exec = require('child_process').exec;
var net = require('net');

// For the exec callback:
var puts = function(error, stdout, stderr) {sys.puts(stdout) };



var server = net.createServer(function (socket) {
//  socket.write("Echo server\r\n");
//  socket.pipe(socket);

  socket.setEncoding('utf8');

	// when the client connects...
  socket.on('connect', function () {
    console.log('Client connected from: ' + socket.remoteAddress);
    //socket.end();
  });

	// when the client sends us data...
  socket.on('data', function (data) {
    console.log("Client sent data: " + data);
		//console.log(data);
		exec('sudo ./spi_led_spit '+data+'', puts)
  });

	// when the client disconnects...
  socket.on('end', function () {
    console.log('Client disconnected.');
    socket.end();
  });

});

server.listen(3333, "0.0.0.0");
console.log('SPI LED Server running at http://0.0.0.0:3333/');